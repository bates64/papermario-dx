#include "dx/overlay.h"
#include "functions.h"

#define MOD_MAGIC   0x4D4F4400 // "MOD\0"

/// The original descriptor budget remains available to maps and actors. Effect
/// descriptors are reserved separately so actor loads cannot consume pool
/// bookkeeping while effect slots are still available.
#define MAX_GENERAL_OVERLAYS 24
#define EFFECT_OVERLAY_DESCRIPTOR_START MAX_GENERAL_OVERLAYS
#define MAX_OVERLAYS (MAX_GENERAL_OVERLAYS + EFFECT_OVERLAY_SLOT_COUNT)

#define RELOCATABLE_LINK_ADDR 0x80000000
#define MAP_OVERLAY_ADDR 0x80240000

extern u8 gEffectOverlayBuffer[EFFECT_OVERLAY_SLOT_COUNT][EFFECT_OVERLAY_SLOT_SIZE];

typedef enum OverlayStorageMode {
    OVL_STORAGE_FIXED       = 0,
    OVL_STORAGE_POOL        = 1,
    OVL_STORAGE_RELOCATABLE = 2,
} OverlayStorageMode;

typedef struct OverlayStorage {
    /* 0x00 */ OverlayStorageMode mode;
    /* 0x04 */ u8* base;
    /* 0x08 */ u32 slotSize;
    /* 0x0C */ s32 slotCount;
    /* 0x10 */ s32 descStart;
    /* 0x14 */ s32 descCount;
} OverlayStorage; // size = 0x18

static const OverlayStorage overlayStorage[OVL_NUM_TYPES] = {
    [OVL_ACTOR] = {
        .mode = OVL_STORAGE_RELOCATABLE,
        .base = (u8*)RELOCATABLE_LINK_ADDR,
        .slotSize = 0,
        .slotCount = 0,
        .descStart = 0,
        .descCount = MAX_GENERAL_OVERLAYS,
    },
    [OVL_MAP] = {
        .mode = OVL_STORAGE_FIXED,
        .base = (u8*)MAP_OVERLAY_ADDR,
        .slotSize = 0,
        .slotCount = 1,
        .descStart = 0,
        .descCount = MAX_GENERAL_OVERLAYS,
    },
    [OVL_EFFECT] = {
        .mode = OVL_STORAGE_POOL,
        .base = (u8*)gEffectOverlayBuffer,
        .slotSize = EFFECT_OVERLAY_SLOT_SIZE,
        .slotCount = EFFECT_OVERLAY_SLOT_COUNT,
        .descStart = EFFECT_OVERLAY_DESCRIPTOR_START,
        .descCount = EFFECT_OVERLAY_SLOT_COUNT,
    },
};

#if DX_DEBUG_OVERLAY_LOADS && (DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE))
static const char* get_type_name(OverlayType type) {
    switch (type) {
        case OVL_ACTOR:
            return "actor";
        case OVL_MAP:
            return "map";
        case OVL_EFFECT:
            return "fx";
        default:
            return "invalid";
    }
}

static const char* get_storage_name(OverlayStorageMode mode) {
    switch (mode) {
        case OVL_STORAGE_FIXED:
            return "fixed";
        case OVL_STORAGE_POOL:
            return "pool";
        case OVL_STORAGE_RELOCATABLE:
            return "rel";
        default:
            return "invalid";
    }
}
#endif

typedef struct OverlayDirectoryEntry {
    /* 0x00 */ char name[64];
    /* 0x40 */ u32 romStart;
    /* 0x44 */ u32 romEnd;
    /* 0x48 */ u32 debugRomStart;
    /* 0x4C */ u32 debugRomEnd;
} OverlayDirectoryEntry; // size = 0x50

_Static_assert(sizeof(OverlayDirectoryEntry) == 80, "DirectoryEntry size must match overlay.py");

/// File layout (offsets implicit from sizes):
///   [header (padded to 16)]
///   [text+data: load_size]
///   [exports | strtab (4-padded) | dtors]
///   [r32 | r26 | hi16 (offset,addr) | lo16 | ctors]
/// Persistent metadata is placed at the next 8-byte boundary in memory so it
/// can be DMA'd directly, though it remains packed immediately after load data
/// in the ROM file.
typedef struct OverlayHeader {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 load_size;     // text + data
    /* 0x08 */ u32 text_size;
    /* 0x0C */ u32 bss_size;
    /* 0x10 */ u32 export_count;
    /* 0x14 */ u32 strtab_size;   // unpadded; 4-padded in file
    /* 0x18 */ u32 dtor_count;
    /* 0x1C */ u32 r32_count;
    /* 0x20 */ u32 r26_count;
    /* 0x24 */ u32 hi16_count;    // entries: (offset, original_addr)
    /* 0x28 */ u32 lo16_count;    // standalone offsets
    /* 0x2C */ u32 ctor_count;
} OverlayHeader; // size = 0x30

_Static_assert(sizeof(OverlayHeader) == 48, "OverlayHeader size must match overlay.py");

typedef struct OverlayExport {
    /* 0x00 */ u32 offset;
    /* 0x04 */ u32 name_offset;
} OverlayExport; // size = 0x08

struct Overlay {
    /* 0x00 */ char name[64]; ///< "" means empty slot.
    /* 0x40 */ OverlayType type;
    /* 0x44 */ u8* base; ///< Where the text/data/bss/meta is.
    /* 0x48 */ u32 text_size;
    /* 0x4C */ u32 load_size; ///< text + data
    /* 0x50 */ OverlayExport* exports;
    /* 0x54 */ u32 export_count;
    /* 0x58 */ const char* strtab;
    /* 0x5C */ u32* dtors;
    /* 0x60 */ u32 dtor_count;
    /* 0x64 */ u32 debugRomStart;
    /* 0x68 */ u32 debugRomEnd;
    /* 0x6C */ s32 storageSlot;
}; // size = 0x70

/// ROM addresses of overlay directories, keyed by type.
/// Written by `tools/build/overlay.py`.
volatile u32 ovlDirectoryRomAddr[OVL_NUM_TYPES] = {};

static Overlay overlays[MAX_OVERLAYS];

static u32 link_addr(OverlayType type) {
    if (overlayStorage[type].mode == OVL_STORAGE_FIXED) {
        return (u32)overlayStorage[type].base;
    }
    return RELOCATABLE_LINK_ADDR;
}

static void apply_relocs(u8* base, OverlayHeader* hdr, u32 rom, u32 linkedAt) {
    u32 load = (u32)base;
    u32 delta = load - linkedAt;

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

static u8* allocate_storage(Overlay* ovl, u32 footprint) {
    const OverlayStorage* storage = &overlayStorage[ovl->type];

    ovl->storageSlot = -1;
    switch (storage->mode) {
        case OVL_STORAGE_FIXED:
            for (s32 i = 0; i < MAX_OVERLAYS; i++) {
                ASSERT_MSG(&overlays[i] == ovl || overlays[i].name[0] == '\0' || overlays[i].type != ovl->type,
                           "Fixed overlay storage for type %d is already occupied", ovl->type);
            }
            return storage->base;

        case OVL_STORAGE_POOL:
            ASSERT_MSG(footprint <= storage->slotSize,
                       "Overlay '%s' footprint 0x%X exceeds pool slot size 0x%X",
                       ovl->name, (unsigned int)footprint, (unsigned int)storage->slotSize);
            for (s32 slot = 0; slot < storage->slotCount; slot++) {
                b32 inUse = false;

                for (s32 i = 0; i < MAX_OVERLAYS; i++) {
                    if (overlays[i].name[0] != '\0' && overlays[i].type == ovl->type &&
                        overlays[i].storageSlot == slot) {
                        inUse = true;
                        break;
                    }
                }
                if (!inUse) {
                    ovl->storageSlot = slot;
                    return storage->base + slot * storage->slotSize;
                }
            }
            ASSERT_MSG(false, "No free pool slots for overlay '%s'", ovl->name);
            return nullptr;

        case OVL_STORAGE_RELOCATABLE:
            return (u8*)malloc(footprint);
    }

    PANIC();
    return nullptr;
}

static void free_storage(Overlay* ovl) {
    if (overlayStorage[ovl->type].mode == OVL_STORAGE_RELOCATABLE) {
        free(ovl->base);
    }
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
    if ((u32)type >= OVL_NUM_TYPES) {
        PANIC_MSG("Invalid overlay type %d", type);
        return nullptr;
    }

    const OverlayStorage* storage = &overlayStorage[type];

    // Find an existing overlay and search its descriptor partition for a free
    // slot as fallback.
    Overlay* ovl = nullptr;
    s32 descriptorEnd = storage->descStart + storage->descCount;
    for (s32 i = storage->descStart; i < descriptorEnd; i++) {
        if (overlays[i].type == type && strcmp(overlays[i].name, name) == 0) {
            return &overlays[i];
        }
        if (overlays[i].name[0] == '\0') {
            ovl = &overlays[i];
        }
    }

    ASSERT_MSG(ovl != nullptr, "Too many overlays loaded for type %d (descriptor budget %d)",
               type, (int)storage->descCount);

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

    // Allocate: [text+data][bss][alignment][exports|strtab|dtors]
    u32 meta_mem_off = (hdr.load_size + hdr.bss_size + 7) & ~7;
    u32 footprint = meta_mem_off + meta_sz;
    ovl->base = allocate_storage(ovl, footprint);
    ASSERT_MSG(ovl->base != nullptr, "Could not allocate storage for overlay '%s'", name);

    // DMA text+data
    dma_copy((u8*)(entry.romStart + load_off),
             (u8*)(entry.romStart + load_off + hdr.load_size), ovl->base);

    // Zero BSS
    if (hdr.bss_size > 0) {
        memset(ovl->base + hdr.load_size, 0, hdr.bss_size);
    }

    // DMA exports+strtab+dtors after BSS
    u8* meta_base = ovl->base + meta_mem_off;
    if (meta_sz > 0) {
        dma_copy((u8*)(entry.romStart + meta_off),
                 (u8*)(entry.romStart + meta_off + meta_sz), meta_base);
    }

    // Set up pointers into loaded region
    ovl->text_size = hdr.text_size;
    ovl->load_size = hdr.load_size;
    ovl->export_count = hdr.export_count;
    ovl->exports = (OverlayExport*)meta_base;
    ovl->strtab = (const char*)(meta_base + hdr.export_count * sizeof(OverlayExport));
    ovl->dtor_count = hdr.dtor_count;
    ovl->dtors = (u32*)((u8*)ovl->strtab + strtab_padded);

    // Apply relocations
    osWritebackDCache(ovl->base, footprint);
    apply_relocs(ovl->base, &hdr, entry.romStart + reloc_off, link_addr(type));
    osWritebackDCache(ovl->base, footprint);
    osInvalICache(ovl->base, footprint);

    // Pre-adjust destructors with delta
    u32 delta = (u32)ovl->base - link_addr(type);
    for (u32 i = 0; i < hdr.dtor_count; i++) {
        ovl->dtors[i] += delta;
    }

#if DX_DEBUG_OVERLAY_LOADS && (DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE))
    if (storage->mode == OVL_STORAGE_POOL) {
        debug_printf_always("\\gOVL+\\d %s/%s \\y%.32s\\d @%08X +%X #%d",
                            get_type_name(ovl->type), get_storage_name(storage->mode), ovl->name,
                            (unsigned int)ovl->base, (unsigned int)footprint, ovl->storageSlot);
    } else {
        debug_printf_always("\\gOVL+\\d %s/%s \\y%.32s\\d @%08X +%X",
                            get_type_name(ovl->type), get_storage_name(storage->mode), ovl->name,
                            (unsigned int)ovl->base, (unsigned int)footprint);
    }
#endif

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

#if DX_DEBUG_OVERLAY_LOADS && (DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE))
    if (overlayStorage[ovl->type].mode == OVL_STORAGE_POOL) {
        debug_printf_always("\\rOVL-\\d %s/%s \\y%.32s\\d @%08X #%d",
                            get_type_name(ovl->type), get_storage_name(overlayStorage[ovl->type].mode),
                            ovl->name, (unsigned int)ovl->base, ovl->storageSlot);
    } else {
        debug_printf_always("\\rOVL-\\d %s/%s \\y%.32s\\d @%08X",
                            get_type_name(ovl->type), get_storage_name(overlayStorage[ovl->type].mode),
                            ovl->name, (unsigned int)ovl->base);
    }
#endif

    // Run destructors
    for (u32 i = 0; i < ovl->dtor_count; i++) {
        void (*fn)(void) = (void (*)(void))ovl->dtors[i];
        fn();
    }

    free_storage(ovl);

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
    return addr >= b && addr < b + ovl->load_size;
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
            return sym != nullptr ? sym : "";
        }
    }
    return nullptr;
}
