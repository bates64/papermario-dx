#include "dx/overlay.h"
#include "functions.h"
#include "nu/nusys.h"

#define MOD_MAGIC   0x4D4F4400 // "MOD\0"
#define MOD_VERSION 2
#define LINK_ADDR   0x80000000

#define MAX_OVERLAYS 24

typedef struct {
    char name[64];
    u32 romStart;
    u32 romEnd;
    u32 flags;
    u32 debugRomStart;
    u32 debugRomEnd;
} ModuleEntry;

_Static_assert(sizeof(ModuleEntry) == 84, "ModuleEntry size must match overlay.py");

typedef struct {
    u32 magic;
    u32 version;
    u32 text_offset, text_size;
    u32 data_offset, data_size;
    u32 bss_size;
    u32 r32_offset, r32_count;
    u32 r26_offset, r26_count;
    u32 hi16_offset, hi16_count;
    u32 lo16_offset, lo16_count;
    u32 ctor_offset, ctor_count;
    u32 dtor_offset, dtor_count;
    u32 export_offset, export_count;
    u32 strtab_offset, strtab_size;
} ModuleHeader;

typedef struct {
    u32 offset;
    u32 name_offset;
} ModuleExport;

struct Overlay {
    char name[64];
    OverlayType type;
    u8* blob;
    u8* base;
    u8* bss;
    ModuleHeader* hdr;
    u32 debugRomStart;
    u32 debugRomEnd;
    b32 loaded;
};

/// ROM addresses of overlay directories, keyed by type.
/// Written by `tools/build/overlay.py`.
volatile u32 ovlDirectoryRomAddr[OVL_NUM_TYPES] = {};

static Overlay overlays[MAX_OVERLAYS];

static const ModuleExport* mod_exports(const Overlay* mod) {
    return (const ModuleExport*)(mod->blob + mod->hdr->export_offset);
}

static const char* mod_strtab(const Overlay* mod) {
    return (const char*)(mod->blob + mod->hdr->strtab_offset);
}

static void apply_relocs(Overlay* mod) {
    u32 load = (u32)mod->base;
    u32 delta = load - LINK_ADDR;
    ModuleHeader* hdr = mod->hdr;

    const u32* r32 = (const u32*)(mod->blob + hdr->r32_offset);
    for (u32 idx = 0; idx < hdr->r32_count; idx++) {
        *(u32*)(load + r32[idx]) += delta;
    }

    const u32* r26 = (const u32*)(mod->blob + hdr->r26_offset);
    for (u32 idx = 0; idx < hdr->r26_count; idx++) {
        u32* loc = (u32*)(load + r26[idx]);
        u32 target = (((*loc & 0x03FFFFFFu) << 2) + delta);
        *loc = (*loc & 0xFC000000u) | ((target & 0x0FFFFFFCu) >> 2);
    }

    ASSERT_MSG(hdr->hi16_count == hdr->lo16_count, "HI16/LO16 count mismatch");
    const u32* hi16 = (const u32*)(mod->blob + hdr->hi16_offset);
    const u32* lo16 = (const u32*)(mod->blob + hdr->lo16_offset);
    for (u32 idx = 0; idx < hdr->hi16_count; idx++) {
        u32* hi_loc = (u32*)(load + hi16[idx]);
        u32* lo_loc = (u32*)(load + lo16[idx]);

        u16 hi_val = (u16)(*hi_loc & 0xFFFFu);
        s16 lo_val = (s16)(*lo_loc & 0xFFFFu);

        u32 addr = (((u32)hi_val) << 16) + (u32)(s32)lo_val + delta;

        u16 new_hi = (u16)(addr >> 16);
        if (addr & 0x8000u) new_hi++;
        *hi_loc = (*hi_loc & 0xFFFF0000u) | new_hi;

        *lo_loc = (*lo_loc & 0xFFFF0000u) | (u16)addr;
    }
}

static void run_table(Overlay* mod, u32 offset, u32 count) {
    u32* table = (u32*)(mod->blob + offset);
    s32 delta = (u32)mod->base - LINK_ADDR;

    for (u32 i = 0; i < count; i++) {
        void (*fn)(void) = (void (*)(void))(table[i] + delta);
        fn();
    }
}

static b32 find_in_directory(OverlayType type, const char* name, ModuleEntry* out) {
    u32 dirAddr = ovlDirectoryRomAddr[type];
    if (dirAddr == 0) return false;

    ALIGNED(16) u32 header[2];
    nuPiReadRom(dirAddr, header, sizeof(header));
    u32 count = header[1];

    ALIGNED(16) ModuleEntry entry;
    u32 entriesAddr = dirAddr + sizeof(header);
    for (u32 i = 0; i < count; i++) {
        nuPiReadRom(entriesAddr + i * sizeof(ModuleEntry), &entry, sizeof(ModuleEntry));
        if (strcmp(entry.name, name) == 0) {
            *out = entry;
            return true;
        }
    }
    return false;
}

Overlay* ovl_load(const char* name, OverlayType type) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (overlays[i].loaded && strcmp(overlays[i].name, name) == 0) {
            return &overlays[i];
        }
    }

    Overlay* mod = nullptr;
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (!overlays[i].loaded) {
            mod = &overlays[i];
            break;
        }
    }
    ASSERT_MSG(mod != nullptr, "No free overlay slots (max %d)", MAX_OVERLAYS);

    u32 j;
    for (j = 0; j < 63 && name[j] != '\0'; j++) {
        mod->name[j] = name[j];
    }
    mod->name[j] = '\0';

    mod->type = type;
    mod->loaded = true;

    ModuleEntry entry;
    b32 found = find_in_directory(type, name, &entry);
    ASSERT_MSG(found, "Overlay '%s' not found", name);

    u32 romSize = entry.romEnd - entry.romStart;
    void* romData = malloc(romSize);
    nuPiReadRom(entry.romStart, romData, romSize);

    mod->debugRomStart = entry.debugRomStart;
    mod->debugRomEnd = entry.debugRomEnd;

    mod->blob = (u8*)romData;
    mod->hdr = (ModuleHeader*)romData;

    ASSERT_MSG(mod->hdr->magic == MOD_MAGIC, "Invalid overlay %s", name);
    ASSERT_MSG(mod->hdr->version == MOD_VERSION, "Overlay %s has version %lu, expected %lu", name, mod->hdr->version, (u32)MOD_VERSION);

    mod->base = mod->blob + mod->hdr->text_offset;

    mod->bss = nullptr;
    if (mod->hdr->bss_size > 0) {
        mod->bss = (u8*)malloc(mod->hdr->bss_size);
        memset(mod->bss, 0, mod->hdr->bss_size);
    }

    apply_relocs(mod);

    osWritebackDCache(mod->base, mod->hdr->text_size + mod->hdr->data_size);
    osInvalICache(mod->base, mod->hdr->text_size);

    run_table(mod, mod->hdr->ctor_offset, mod->hdr->ctor_count);

    return mod;
}

void ovl_unload(Overlay* mod) {
    if (mod == nullptr || !mod->loaded) return;

    run_table(mod, mod->hdr->dtor_offset, mod->hdr->dtor_count);

    free(mod->bss);
    free(mod->blob);
    mod->blob = nullptr;
    mod->base = nullptr;
    mod->bss = nullptr;
    mod->hdr = nullptr;
    mod->loaded = false;
}

void ovl_unload_type(OverlayType type) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (overlays[i].loaded && overlays[i].type == type) {
            ovl_unload(&overlays[i]);
        }
    }
}

void* ovl_import(const Overlay* mod, const char* name) {
    const ModuleExport* exp = mod_exports(mod);
    const char* str = mod_strtab(mod);

    for (u32 i = 0; i < mod->hdr->export_count; i++) {
        if (strcmp(str + exp[i].name_offset, name) == 0) {
            return mod->base + exp[i].offset;
        }
    }
    return nullptr;
}

static const char* name_for_addr(const Overlay* mod, u32 addr) {
    u32 off = addr - (u32)mod->base;
    const ModuleExport* exp = mod_exports(mod);
    const char* str = mod_strtab(mod);

    const char* best = nullptr;
    u32 best_off = 0;

    for (u32 i = 0; i < mod->hdr->export_count; i++) {
        if (exp[i].offset <= off && exp[i].offset >= best_off) {
            best_off = exp[i].offset;
            best = str + exp[i].name_offset;
        }
    }
    return best;
}

static b32 contains(const Overlay* mod, u32 addr) {
    u32 b = (u32)mod->base;
    return addr >= b && addr < b + mod->hdr->text_size;
}

const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (!overlays[i].loaded) continue;
        Overlay* mod = &overlays[i];

        if (contains(mod, addr)) {
            const char* sym = name_for_addr(mod, addr);
            if (outOverlayName)
                *outOverlayName = mod->name;
            if (outDebugRomStart)
                *outDebugRomStart = mod->debugRomStart;
            if (outDebugRomEnd)
                *outDebugRomEnd = mod->debugRomEnd;
            if (outOverlayBase)
                *outOverlayBase = (u32)mod->base;
            return sym;
        }
    }
    return nullptr;
}
