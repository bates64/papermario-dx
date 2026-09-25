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
///   [text+data: loadSize]
///   [exports | strtab (4-padded) | dtors]
///   [r32 | r26 | hi16 (offset,addr) | lo16 | ctors]
typedef struct {
    u32 magic;
    u32 loadSize;     // text + data
    u32 textSize;
    u32 bssSize;
    u32 exportCount;
    u32 strtabSize;   // unpadded; 4-padded in file
    u32 dtorCount;
    u32 r32Count;
    u32 r26Count;
    u32 hi16Count;    // entries: (offset, original_addr)
    u32 lo16Count;    // standalone offsets
    u32 ctorCount;
} OverlayHeader;

_Static_assert(sizeof(OverlayHeader) == 48, "OverlayHeader size must match overlay.py");

typedef struct {
    u32 offset;
    u32 nameOffset;
} OverlayExport;

struct Overlay {
    char name[64]; ///< "" means empty slot.
    OverlayType type;
    u8* base; ///< Where the text/data/bss/meta is.
    u32 textSize;
    u32 loadSize; ///< text + data
    OverlayExport* exports;
    u32 exportCount;
    const char* strtab;
    u32* dtors;
    u32 dtorCount;
    u32 debugRomStart;
    u32 debugRomEnd;
};

/// ROM addresses of overlay directories, keyed by type.
/// Written by `tools/build/overlay.py`.
volatile u32 ovlDirectoryRomAddr[OVL_NUM_TYPES] = {};

static Overlay overlays[MAX_OVERLAYS];

/// Called after an overlay is loaded or unloaded, so a debugger can break here.
static __attribute__((noinline)) void ovl_debug_changed(void) {
    __asm__ volatile("nop");
}

static u32 link_addr(OverlayType type) {
    switch (type) {
        case OVL_MAP: return 0x80240000;
        default: return RELOCATABLE_LINK_ADDR;
    }
}

static void apply_relocs(u8* base, OverlayHeader* hdr, u32 rom) {
    u32 load = (u32)base;
    u32 delta = load - RELOCATABLE_LINK_ADDR;

    if (hdr->r32Count > 0) {
        ALIGNED(8) u32 r32[hdr->r32Count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->r32Count * sizeof(u32)), r32);
        for (u32 i = 0; i < hdr->r32Count; i++) {
            *(u32*)(load + r32[i]) += delta;
        }
    }
    rom += hdr->r32Count * sizeof(u32);

    if (hdr->r26Count > 0) {
        ALIGNED(8) u32 r26[hdr->r26Count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->r26Count * sizeof(u32)), r26);
        for (u32 i = 0; i < hdr->r26Count; i++) {
            u32* loc = (u32*)(load + r26[i]);
            u32 target = (((*loc & 0x03FFFFFFu) << 2) + delta);
            *loc = (*loc & 0xFC000000u) | ((target & 0x0FFFFFFCu) >> 2);
        }
    }
    rom += hdr->r26Count * sizeof(u32);

    if (hdr->hi16Count > 0) {
        ALIGNED(8) u32 hi16[hdr->hi16Count * 2];
        dma_copy((u8*)rom, (u8*)(rom + hdr->hi16Count * 2 * sizeof(u32)), hi16);
        for (u32 i = 0; i < hdr->hi16Count; i++) {
            u32* hiLoc = (u32*)(load + hi16[i * 2]);
            u32 addr = hi16[i * 2 + 1] + delta;
            u16 newHi = (u16)(addr >> 16);
            if (addr & 0x8000u) newHi++;
            *hiLoc = (*hiLoc & 0xFFFF0000u) | newHi;
        }
    }
    rom += hdr->hi16Count * 2 * sizeof(u32);

    if (hdr->lo16Count > 0) {
        ALIGNED(8) u32 lo16[hdr->lo16Count];
        dma_copy((u8*)rom, (u8*)(rom + hdr->lo16Count * sizeof(u32)), lo16);
        for (u32 i = 0; i < hdr->lo16Count; i++) {
            u32* loLoc = (u32*)(load + lo16[i]);
            *loLoc = (*loLoc & 0xFFFF0000u) | (u16)((*loLoc & 0xFFFF) + (u16)delta);
        }
    }
    rom += hdr->lo16Count * sizeof(u32);
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
    u32 loadOff = (sizeof(OverlayHeader) + 15) & ~15;
    u32 strtabPadded = (hdr.strtabSize + 3) & ~3;
    u32 metaSz = hdr.exportCount * sizeof(OverlayExport) + strtabPadded + hdr.dtorCount * sizeof(u32);
    u32 metaOff = loadOff + hdr.loadSize;
    u32 relocOff = metaOff + metaSz;
    u32 ctorOff = relocOff
                   + hdr.r32Count * sizeof(u32)
                   + hdr.r26Count * sizeof(u32)
                   + hdr.hi16Count * 2 * sizeof(u32)
                   + hdr.lo16Count * sizeof(u32);

    // Allocate: [text+data][bss][exports|strtab|dtors]
    u32 footprint = hdr.loadSize + hdr.bssSize + metaSz;
    ovl->base = (u8*)link_addr(type);
    if ((u32)ovl->base == RELOCATABLE_LINK_ADDR) {
        ovl->base = (u8*)malloc(footprint);
    }

    // DMA text+data
    dma_copy((u8*)(entry.romStart + loadOff),
             (u8*)(entry.romStart + loadOff + hdr.loadSize), ovl->base);

    // Zero BSS
    if (hdr.bssSize > 0) {
        memset(ovl->base + hdr.loadSize, 0, hdr.bssSize);
    }

    // DMA exports+strtab+dtors after BSS
    u8* metaBase = ovl->base + hdr.loadSize + hdr.bssSize;
    if (metaSz > 0) {
        dma_copy((u8*)(entry.romStart + metaOff),
                 (u8*)(entry.romStart + metaOff + metaSz), metaBase);
    }

    // Set up pointers into loaded region
    ovl->textSize = hdr.textSize;
    ovl->loadSize = hdr.loadSize;
    ovl->exportCount = hdr.exportCount;
    ovl->exports = (OverlayExport*)metaBase;
    ovl->strtab = (const char*)(metaBase + hdr.exportCount * sizeof(OverlayExport));
    ovl->dtorCount = hdr.dtorCount;
    ovl->dtors = (u32*)((u8*)ovl->strtab + strtabPadded);

    // Apply relocations
    osWritebackDCache(ovl->base, footprint);
    apply_relocs(ovl->base, &hdr, entry.romStart + relocOff);
    osWritebackDCache(ovl->base, footprint);
    osInvalICache(ovl->base, footprint);

    // Pre-adjust destructors with delta
    u32 delta = (u32)ovl->base - link_addr(type);
    for (u32 i = 0; i < hdr.dtorCount; i++) {
        ovl->dtors[i] += delta;
    }

    printf("ovl_load %s\n", ovl->name);
    ovl_debug_changed();

    // Run constructors
    if (hdr.ctorCount > 0) {
        ALIGNED(8) u32 ctors[hdr.ctorCount];
        dma_copy((u8*)(entry.romStart + ctorOff),
                 (u8*)(entry.romStart + ctorOff + hdr.ctorCount * sizeof(u32)), ctors);
        for (u32 i = 0; i < hdr.ctorCount; i++) {
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
    for (u32 i = 0; i < ovl->dtorCount; i++) {
        void (*fn)(void) = (void (*)(void))ovl->dtors[i];
        fn();
    }

    if ((u32)ovl->base != RELOCATABLE_LINK_ADDR) {
        free(ovl->base);
    }

    memset(ovl, 0, sizeof(*ovl));
    ovl_debug_changed();
}

void ovl_unload_type(OverlayType type) {
    for (s32 i = 0; i < MAX_OVERLAYS; i++) {
        if (overlays[i].type == type) {
            ovl_unload(&overlays[i]);
        }
    }
}

void* ovl_import(const Overlay* ovl, const char* name) {
    for (u32 i = 0; i < ovl->exportCount; i++) {
        if (strcmp(ovl->strtab + ovl->exports[i].nameOffset, name) == 0) {
            return ovl->base + ovl->exports[i].offset;
        }
    }
    return nullptr;
}

static const char* name_for_addr(const Overlay* ovl, u32 addr) {
    u32 off = addr - (u32)ovl->base;

    const char* best = nullptr;
    u32 bestOff = 0;

    for (u32 i = 0; i < ovl->exportCount; i++) {
        if (ovl->exports[i].offset <= off && ovl->exports[i].offset >= bestOff) {
            bestOff = ovl->exports[i].offset;
            best = ovl->strtab + ovl->exports[i].nameOffset;
        }
    }
    return best;
}

static b32 contains(const Overlay* ovl, u32 addr) {
    if (ovl->name[0] == '\0') return false;
    u32 b = (u32)ovl->base;
    return addr >= b && addr < b + ovl->loadSize;
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
