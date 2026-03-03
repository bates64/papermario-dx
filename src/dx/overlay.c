#include "dx/overlay.h"
#include "functions.h"

#define MOD_MAGIC   0x4D4F4400 // "MOD\0"

/// Maximum number of overlays that can be loaded at once.
#define MAX_OVERLAYS 24

#define RELOCATABLE_LINK_ADDR 0x80000000

typedef struct {
    char name[64];
    u32 romStart;
    u32 romEnd;
    u32 debugRomStart;
    u32 debugRomEnd;
} OverlayDirectoryEntry;

_Static_assert(sizeof(OverlayDirectoryEntry) == 80, "DirectoryEntry size must match overlay.py");

/// File layout (offsets implicit from sizes):
///   [header (padded to 16)]
///   [text+data: load_size]
///   [exports | strtab (4-padded) | dtors]
///   [r32 | r26 | hi16 (offset,addr) | lo16 | ctors]
typedef struct {
    u32 magic;
    u32 load_size;     // text + data
    u32 text_size;
    u32 bss_size;
    u32 export_count;
    u32 strtab_size;   // unpadded; 4-padded in file
    u32 dtor_count;
    u32 r32_count;
    u32 r26_count;
    u32 hi16_count;    // entries: (offset, original_addr)
    u32 lo16_count;    // standalone offsets
    u32 ctor_count;
} OverlayHeader;

_Static_assert(sizeof(OverlayHeader) == 48, "OverlayHeader size must match overlay.py");

typedef struct {
    u32 offset;
    u32 name_offset;
} OverlayExport;

struct Overlay {
    char name[64]; ///< "" means empty slot.
    OverlayType type;
    u8* base; ///< Where the text/data/bss/meta is.
    u32 text_size;
    OverlayExport* exports;
    u32 export_count;
    const char* strtab;
    u32* dtors;
    u32 dtor_count;
    u32 debugRomStart;
    u32 debugRomEnd;
};

/// ROM addresses of overlay directories, keyed by type.
/// Written by `tools/build/overlay.py`.
volatile u32 ovlDirectoryRomAddr[OVL_NUM_TYPES] = {};

static Overlay overlays[MAX_OVERLAYS];

static u32 link_addr(OverlayType type) {
    switch (type) {
        case OVL_MAP: return 0x80240000;
        default: return RELOCATABLE_LINK_ADDR;
    }
}

static void apply_relocs(u8* base, OverlayHeader* hdr, u32 rom) {
    u32 load = (u32)base;
    u32 delta = load - RELOCATABLE_LINK_ADDR;

    if (hdr->r32_count > 0) {
        ALIGNED(8) u32 r32[hdr->r32_count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->r32_count * sizeof(u32)), r32);
        for (u32 i = 0; i < hdr->r32_count; i++) {
            *(u32*)(load + r32[i]) += delta;
        }
    }
    rom += hdr->r32_count * sizeof(u32);

    if (hdr->r26_count > 0) {
        ALIGNED(8) u32 r26[hdr->r26_count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->r26_count * sizeof(u32)), r26);
        for (u32 i = 0; i < hdr->r26_count; i++) {
            u32* loc = (u32*)(load + r26[i]);
            u32 target = (((*loc & 0x03FFFFFFu) << 2) + delta);
            *loc = (*loc & 0xFC000000u) | ((target & 0x0FFFFFFCu) >> 2);
        }
    }
    rom += hdr->r26_count * sizeof(u32);

    if (hdr->hi16_count > 0) {
        ALIGNED(8) u32 hi16[hdr->hi16_count * 2];
        dma_copy((u8*)rom, (u8*)(rom + hdr->hi16_count * 2 * sizeof(u32)), hi16);
        for (u32 i = 0; i < hdr->hi16_count; i++) {
            u32* hi_loc = (u32*)(load + hi16[i * 2]);
            u32 addr = hi16[i * 2 + 1] + delta;
            u16 new_hi = (u16)(addr >> 16);
            if (addr & 0x8000u) new_hi++;
            *hi_loc = (*hi_loc & 0xFFFF0000u) | new_hi;
        }
    }
    rom += hdr->hi16_count * 2 * sizeof(u32);

    if (hdr->lo16_count > 0) {
        ALIGNED(8) u32 lo16[hdr->lo16_count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->lo16_count * sizeof(u32)), lo16);
        for (u32 i = 0; i < hdr->lo16_count; i++) {
            u32* lo_loc = (u32*)(load + lo16[i]);
            *lo_loc = (*lo_loc & 0xFFFF0000u) | (u16)((*lo_loc & 0xFFFF) + (u16)delta);
        }
    }
    rom += hdr->lo16_count * sizeof(u32);
}

static b32 find_in_directory(OverlayType type, const char* name, OverlayDirectoryEntry* out) {
    u32 dirAddr = ovlDirectoryRomAddr[type];
    if (dirAddr == 0) return false;

    ALIGNED(8) u32 header[2];
    dma_copy((u8*)dirAddr, (u8*)(dirAddr + sizeof(header)), header);
    u32 count = header[1];

    ALIGNED(8) OverlayDirectoryEntry entry;
    u32 entriesAddr = dirAddr + sizeof(header);
    for (u32 i = 0; i < count; i++) {
        u32 entryAddr = entriesAddr + i * sizeof(OverlayDirectoryEntry);
        dma_copy((u8*)entryAddr, (u8*)(entryAddr + sizeof(OverlayDirectoryEntry)), &entry);
        if (strcmp(entry.name, name) == 0) {
            *out = entry;
            return true;
        }
    }
    return false;
}

Overlay* ovl_load(const char* name, OverlayType type) {
    // Find existing and search for free slot as fallback
    Overlay* ovl = nullptr;
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (strcmp(overlays[i].name, name) == 0) {
            return &overlays[i];
        }
        if (overlays[i].name[0] == '\0') {
            ovl = &overlays[i];
        }
    }

    ASSERT_MSG(ovl != nullptr, "Too many overlays loaded (max %d)", MAX_OVERLAYS);

    strcpy(ovl->name, name);
    ovl->type = type;

    OverlayDirectoryEntry entry;
    b32 found = find_in_directory(type, name, &entry);
    ASSERT_MSG(found, "Overlay '%s' not found", name);

    ovl->debugRomStart = entry.debugRomStart;
    ovl->debugRomEnd = entry.debugRomEnd;

    // Read header
    ALIGNED(8) OverlayHeader hdr;
    dma_copy((u8*)entry.romStart, (u8*)(entry.romStart + sizeof(OverlayHeader)), &hdr);
    ASSERT_MSG(hdr.magic == MOD_MAGIC, "Invalid overlay %s", name);

    // Compute file offsets
    u32 load_off = (sizeof(OverlayHeader) + 15) & ~15;
    u32 strtab_padded = (hdr.strtab_size + 3) & ~3;
    u32 meta_sz = hdr.export_count * sizeof(OverlayExport) + strtab_padded + hdr.dtor_count * sizeof(u32);
    u32 meta_off = load_off + hdr.load_size;
    u32 reloc_off = meta_off + meta_sz;
    u32 ctor_off = reloc_off
                   + hdr.r32_count * sizeof(u32)
                   + hdr.r26_count * sizeof(u32)
                   + hdr.hi16_count * 2 * sizeof(u32)
                   + hdr.lo16_count * sizeof(u32);

    // Allocate: [text+data][bss][exports|strtab|dtors]
    u32 footprint = hdr.load_size + hdr.bss_size + meta_sz;
    ovl->base = (u8*)link_addr(type);
    if ((u32)ovl->base == RELOCATABLE_LINK_ADDR) {
        ovl->base = (u8*)malloc(footprint);
    }

    // DMA text+data
    dma_copy((u8*)(entry.romStart + load_off),
             (u8*)(entry.romStart + load_off + hdr.load_size), ovl->base);

    // Zero BSS
    if (hdr.bss_size > 0) {
        memset(ovl->base + hdr.load_size, 0, hdr.bss_size);
    }

    // DMA exports+strtab+dtors after BSS
    u8* meta_base = ovl->base + hdr.load_size + hdr.bss_size;
    if (meta_sz > 0) {
        dma_copy((u8*)(entry.romStart + meta_off),
                 (u8*)(entry.romStart + meta_off + meta_sz), meta_base);
    }

    // Set up pointers into loaded region
    ovl->text_size = hdr.text_size;
    ovl->export_count = hdr.export_count;
    ovl->exports = (OverlayExport*)meta_base;
    ovl->strtab = (const char*)(meta_base + hdr.export_count * sizeof(OverlayExport));
    ovl->dtor_count = hdr.dtor_count;
    ovl->dtors = (u32*)((u8*)ovl->strtab + strtab_padded);

    // Apply relocations
    osWritebackDCache(ovl->base, footprint);
    apply_relocs(ovl->base, &hdr, entry.romStart + reloc_off);
    osWritebackDCache(ovl->base, footprint);
    osInvalICache(ovl->base, footprint);

    // Pre-adjust destructors with delta
    u32 delta = (u32)ovl->base - link_addr(type);
    for (u32 i = 0; i < hdr.dtor_count; i++) {
        ovl->dtors[i] += delta;
    }

    printf("ovl_load %s\n", ovl->name);

    // Run constructors
    if (hdr.ctor_count > 0) {
        ALIGNED(8) u32 ctors[hdr.ctor_count];
        dma_copy((u8*)(entry.romStart + ctor_off),
                 (u8*)(entry.romStart + ctor_off + hdr.ctor_count * sizeof(u32)), ctors);
        for (u32 i = 0; i < hdr.ctor_count; i++) {
            void (*fn)(void) = (void (*)(void))(ctors[i] + delta);
            fn();
        }
    }

    return ovl;
}

void ovl_unload(Overlay* ovl) {
    if (ovl == nullptr || ovl->name[0] == '\0') return;

    printf("ovl_unload %s\n", ovl->name);

    // Run destructors
    for (u32 i = 0; i < ovl->dtor_count; i++) {
        void (*fn)(void) = (void (*)(void))ovl->dtors[i];
        fn();
    }

    if ((u32)ovl->base != RELOCATABLE_LINK_ADDR) {
        free(ovl->base);
    }

    memset(ovl, 0, sizeof(*ovl));
}

void ovl_unload_type(OverlayType type) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (overlays[i].type == type) {
            ovl_unload(&overlays[i]);
        }
    }
}

void* ovl_import(const Overlay* ovl, const char* name) {
    for (u32 i = 0; i < ovl->export_count; i++) {
        if (strcmp(ovl->strtab + ovl->exports[i].name_offset, name) == 0) {
            return ovl->base + ovl->exports[i].offset;
        }
    }
    return nullptr;
}

static const char* name_for_addr(const Overlay* ovl, u32 addr) {
    u32 off = addr - (u32)ovl->base;

    const char* best = nullptr;
    u32 best_off = 0;

    for (u32 i = 0; i < ovl->export_count; i++) {
        if (ovl->exports[i].offset <= off && ovl->exports[i].offset >= best_off) {
            best_off = ovl->exports[i].offset;
            best = ovl->strtab + ovl->exports[i].name_offset;
        }
    }
    return best;
}

static b32 contains(const Overlay* ovl, u32 addr) {
    if (ovl->name[0] == '\0') return false;
    u32 b = (u32)ovl->base;
    return addr >= b && addr < b + ovl->text_size;
}

const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        Overlay* ovl = &overlays[i];

        if (contains(ovl, addr)) {
            const char* sym = name_for_addr(ovl, addr);
            if (outOverlayName)
                *outOverlayName = ovl->name;
            if (outDebugRomStart)
                *outDebugRomStart = ovl->debugRomStart;
            if (outDebugRomEnd)
                *outDebugRomEnd = ovl->debugRomEnd;
            if (outOverlayBase)
                *outOverlayBase = (u32)ovl->base;
            return sym;
        }
    }
    return nullptr;
}
