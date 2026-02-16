#include "dx/prelude.h"
#include "dx/sync.h"
#include "functions.h"
#include "ld_addrs.h"
#include <string.h>

using dx::sync::Mutex;

b32 _assetsDirty = false;

extern "C" int decompress_lz4_full_fast(const void* inbuf, int insize, void* outbuf);

// Static message queue for async DMA - must persist until DMA completes
static OSMesgQueue sAsyncDmaQueue;
static OSMesg sAsyncDmaMesg;
static OSIoMesg sAsyncDmaIoMesg;
static bool sAsyncDmaQueueInit = false;

namespace preload {

constexpr int THREAD_PRI = 10;    // Same as main thread for time-slicing
constexpr int STACK_SIZE = 0x2000;

struct Request {
    char name[64];
    u8* romBase;
    u32 offset;
    u32 compressedLength;
    u32 decompressedLength;
};

struct Result {
    char name[64] = {0};
    u8* data = nullptr;
    u32 size = 0;

    void clear() {
        name[0] = '\0';
        data = nullptr;
        size = 0;
    }
};

static Mutex<Result> result;
static OSThread thread;
static OSMesgQueue queue;
static OSMesg queueMsg;
static bool started = false;

static void do_load(Request* req) {
    u8* romStart = req->romBase + req->offset;
    bool isCompressed = req->compressedLength != req->decompressedLength;

    u8* decompressedData;

    if (isCompressed) {
        decompressedData = new u8[req->decompressedLength + 8];  // +8 for LZ4
        u8* compressedData = new u8[req->compressedLength];

        dma_copy(romStart, romStart + req->compressedLength, compressedData);
        decompress_lz4_full_fast(compressedData, req->compressedLength, decompressedData);

        delete[] compressedData;
    } else {
        decompressedData = new u8[req->decompressedLength];
        dma_copy(romStart, romStart + req->decompressedLength, decompressedData);
    }

    // Store result
    {
        auto r = result.lock();
        strncpy(r->name, req->name, sizeof(r->name) - 1);
        r->name[sizeof(r->name) - 1] = '\0';
        r->data = decompressedData;
        r->size = req->decompressedLength;
    }

    printf("Preloaded %s (%lu bytes)\n", req->name, req->decompressedLength);
    delete req;
}

static void thread_func(void* arg) {
    (void)arg;

    while (true) {
        OSMesg msg;
        osRecvMesg(&queue, &msg, OS_MESG_BLOCK);
        do_load((Request*)msg);
    }
}

static void init() {
    osCreateMesgQueue(&queue, &queueMsg, 1);

    u8* stack = new u8[STACK_SIZE + 16];
    u8* stackAligned = (u8*)(((u32)stack + 15) & ~15);

    osCreateThread(&thread, 100, thread_func, nullptr,
                   stackAligned + STACK_SIZE, THREAD_PRI);
    osStartThread(&thread);
    started = true;
}

} // namespace preload

// Start a DMA transfer without waiting for completion.
static void dma_start_async(u8* romStart, u8* dest, u32 size) {
    if (!sAsyncDmaQueueInit) {
        osCreateMesgQueue(&sAsyncDmaQueue, &sAsyncDmaMesg, 1);
        sAsyncDmaQueueInit = true;
    }

    osRecvMesg(&sAsyncDmaQueue, NULL, OS_MESG_NOBLOCK);
    osInvalDCache(dest, size);

    sAsyncDmaIoMesg.hdr.pri = OS_MESG_PRI_NORMAL;
    sAsyncDmaIoMesg.hdr.retQueue = &sAsyncDmaQueue;
    sAsyncDmaIoMesg.dramAddr = dest;
    sAsyncDmaIoMesg.devAddr = (u32)romStart;
    sAsyncDmaIoMesg.size = size;

    osEPiStartDma(nuPiCartHandle, &sAsyncDmaIoMesg, OS_READ);
}

static void dma_wait_async() {
    osRecvMesg(&sAsyncDmaQueue, NULL, OS_MESG_BLOCK);
}

#define ASSET_TABLE_ROM_START (s32) mapfs_ROM_START

namespace dx {
namespace asset {

using rc::Rc;
using string::FixedString;
using collections::Vec;

// Cache value: stores location info and loaded instance for an asset
struct AssetCacheValue {
    u8* base;              // ROM base address for this asset's table
    struct {
        u32 offset;
        u32 compressedLength;
        u32 decompressedLength;
        u32 hash;
    } header;    // Asset metadata
    Weak<Asset> loaded;  // Weak reference - asset is freed when no strong refs exist
};

// Caches info per asset so that we don't have to do a linear lookup every load
static HashMap<FixedString<64>, AssetCacheValue> assets;
static bool assetsLoaded = false;

// Track generations of tables in the chain (index 0 = root, 1 = first mod, etc.)
static Vec<u8> lastSeenGenerations;

extern "C" void poll_hot_assets() {
    if (assetsLoaded && !_assetsDirty) {
        return;
    }

    // Pre-allocate assets map based on root table size (speeds up initial load)
    if (!assetsLoaded) {
        AssetTableHeader rootHeader;
        u8* rootBase = (u8*) ASSET_TABLE_ROM_START;
        dma_copy(rootBase, rootBase + sizeof(AssetTableHeader), &rootHeader);
        assets.reserve(rootHeader.entryCount);
    }

    // Save old hashes and loaded instances before rebuilding
    u32 assetCount = assets.size();

    HashMap<FixedString<64>, u32> oldHashes(assetCount);
    HashMap<FixedString<64>, Weak<Asset>> oldLoaded(assetCount);
    for (auto [name, value] : assets) {
        oldHashes.put(name, value.header.hash);
        if (value.loaded.is_alive()) {
            oldLoaded.put(name, value.loaded);
        }
    }

    // PASS 1: Traverse all asset tables and build final cache (last instance wins)
    u8* tableBase = (u8*) ASSET_TABLE_ROM_START;
    AssetTableHeader tableHeader;
    AssetHeader* assetTableBuffer = nullptr;
    u32 bufferCapacity = 0;
    u32 tableIndex = 0;

    while (tableBase != nullptr) {
        // Read table header
        dma_copy(tableBase, tableBase + sizeof(AssetTableHeader), &tableHeader);

        if (tableHeader.magic[0] != 'M' || tableHeader.magic[1] != 'A' || tableHeader.magic[2] != 'P' || tableHeader.magic[3] != 'F' || tableHeader.magic[4] != 'S') {
            printf("Ignoring invalid asset table at %p (bad magic)\n", tableBase);
            break;
        }

        // Check if this table's generation changed
        bool tableChanged = tableIndex >= lastSeenGenerations.size() || tableHeader.generation != lastSeenGenerations[tableIndex];

        if (tableChanged) {
            // Allocate or resize buffer for entries
            u32 tableSize = tableHeader.entryCount * sizeof(AssetHeader);
            if (tableSize > bufferCapacity) {
                heap_free(assetTableBuffer);
                assetTableBuffer = (AssetHeader*) heap_malloc(tableSize);
                bufferCapacity = tableSize;
            }

            // Read all entries
            u8* entriesStart = tableBase + sizeof(AssetTableHeader);
            dma_copy(entriesStart, entriesStart + tableSize, assetTableBuffer);

            // Process each entry
            for (u32 i = 0; i < tableHeader.entryCount; i++) {
                AssetHeader* curAsset = &assetTableBuffer[i];

                AssetCacheValue cacheValue {
                    tableBase,
                    {
                        curAsset->offset,
                        curAsset->compressedLength,
                        curAsset->decompressedLength,
                        curAsset->hash
                    },
                    Weak<Asset>()  // Empty weak reference for now
                };
                assets.put(FixedString<64>(curAsset->name), cacheValue);
            }
        }

        // Store generation for this table
        if (tableIndex >= lastSeenGenerations.size()) {
            lastSeenGenerations.push(tableHeader.generation);
        } else {
            lastSeenGenerations[tableIndex] = tableHeader.generation;
        }

        // Follow chain to next table
        tableBase = tableHeader.nextTable != 0 ? (u8*) tableHeader.nextTable : nullptr;
        tableIndex++;
    }

    // Trim vector if chain got shorter
    if (tableIndex < lastSeenGenerations.size()) {
        lastSeenGenerations.resize(tableIndex);
    }

    heap_free(assetTableBuffer);

    // PASS 2: Restore loaded instances and check for hot reloads
    // Only iterate over assets that were actually loaded (not the entire cache)
    for (auto [name, weak] : oldLoaded) {
        auto entry = assets.get(name);
        if (!entry) {
            continue;
        }

        auto& value = entry.unwrap();
        value.loaded = weak;

        // Check if the FINAL hash changed from previous run
        auto oldHash = oldHashes.get(name);
        if (oldHash && oldHash.unwrap() != value.header.hash) {
            if (auto rc = weak.upgrade()) {
                rc.unwrap()->reload(
                    value.base,
                    value.header.offset,
                    value.header.compressedLength,
                    value.header.decompressedLength
                );
            }
        }
    }

    assetsLoaded = true;
    _assetsDirty = false;
}

Asset::Asset(void* data, u32 size, u32 generation)
    : dataPtr(data), dataSize(size), gen(generation), exclusive(false), pendingReload(false) {}

Asset::~Asset() {
    if (dataPtr) {
        delete[] static_cast<u8*>(dataPtr);
    }
}

void Asset::reload(u8* base, u32 offset, u32 compressedLength, u32 decompressedLength) {
    if (exclusive) {
        pendingReload = true;
        return;
    }

    u8* romStart = base + offset;
    bool isCompressed = compressedLength != decompressedLength;

    u8* decompressedData;

    if (isCompressed) {
        decompressedData = new u8[decompressedLength + 8]; // +8 for lz4 algorithm
        u8* compressedData = new u8[compressedLength];

        // LZ4 streaming decompression
        dma_start_async(romStart, compressedData, compressedLength);
        decompress_lz4_full_fast(compressedData, compressedLength, decompressedData);
        dma_wait_async();

        delete[] compressedData;
    } else {
        // Uncompressed - direct DMA
        decompressedData = new u8[decompressedLength];
        dma_copy(romStart, romStart + decompressedLength, decompressedData);
    }

    // Free old data if any
    if (dataPtr) {
        delete[] static_cast<u8*>(dataPtr);
    }

    // Update state
    dataPtr = decompressedData;
    dataSize = decompressedLength;
    gen++;
}

Rc<Asset> Asset::load(const char* name) {
    poll_hot_assets();

    // Look up asset in cache
    auto entry = assets.get(name);
    if (!entry) {
        PANIC_MSG("Asset not found: %s", name);
    }

    AssetCacheValue& value = entry.unwrap();

    // Try to upgrade weak reference
    auto existingAsset = value.loaded.upgrade();
    if (existingAsset) {
        ASSERT_MSG(!existingAsset.unwrap()->exclusive,
            "Asset '%s' is exclusively owned by a Module", name);
        return existingAsset.unwrap();
    }

    // Check if this asset was preloaded
    {
        auto r = preload::result.lock();
        if (strcmp(r->name, name) == 0 && r->data != nullptr) {
            u8* data = r->data;
            u32 size = r->size;
            r->clear();

            Rc<Asset> asset = Rc<Asset>::make(
                static_cast<void*>(data),
                size,
                static_cast<u32>(1)
            );
            value.loaded = asset.downgrade();
            return asset;
        }
    }

    // Load fresh
    Rc<Asset> asset = Rc<Asset>::make(static_cast<void*>(nullptr), static_cast<u32>(0), static_cast<u32>(1));
    asset->reload(
        value.base,
        value.header.offset,
        value.header.compressedLength,
        value.header.decompressedLength
    );

    // Store weak reference in cache
    value.loaded = asset.downgrade();
    return asset;
}

void Asset::preload(const char* name) {
    if (!preload::started) {
        preload::init();
    }

    // Check if already loaded or preloaded
    poll_hot_assets();
    auto entry = assets.get(name);
    if (!entry) {
        return;
    }

    AssetCacheValue& value = entry.unwrap();
    if (value.loaded.is_alive()) {
        return;
    }

    // Check if already preloading/preloaded
    {
        auto r = preload::result.lock();
        if (r->name[0] != '\0') {
            return;
        }
    }

    // Queue preload request
    auto* req = new preload::Request();
    strncpy(req->name, name, sizeof(req->name) - 1);
    req->name[sizeof(req->name) - 1] = '\0';
    req->romBase = value.base;
    req->offset = value.header.offset;
    req->compressedLength = value.header.compressedLength;
    req->decompressedLength = value.header.decompressedLength;

    osSendMesg(&preload::queue, req, OS_MESG_NOBLOCK);
}

// Legacy C API implementations
extern "C" {

void* load_asset_by_name(const char* assetName, u32* decompressedSize) {
    poll_hot_assets();

    auto entry = assets.get(assetName);
    if (!entry) {
        PANIC_MSG("Asset not found: %s", assetName);
    }

    AssetCacheValue& value = entry.unwrap();
    *decompressedSize = value.header.decompressedLength;

    u8* romStart = value.base + value.header.offset;
    bool isCompressed = value.header.compressedLength != value.header.decompressedLength;

    if (isCompressed) {
        // LZ4 streaming decompression - decompress while DMA is in progress
        u8* compressedData = (u8*)general_heap_malloc(value.header.compressedLength);

        // Allocate output buffer (+8 for LZ4 overwrite safety)
        u8* decompressedData = (u8*)general_heap_malloc(value.header.decompressedLength + 8);

        // Start async DMA - decompressor will poll PI registers to track progress
        dma_start_async(romStart, compressedData, value.header.compressedLength);

        // Decompress - polls PI_DRAM_ADDR to wait for data as needed
        decompress_lz4_full_fast(compressedData, value.header.compressedLength, decompressedData);

        general_heap_free(compressedData);
        return decompressedData;
    } else {
        // Uncompressed - direct copy
        void* data = general_heap_malloc(value.header.decompressedLength);
        dma_copy(romStart, romStart + value.header.decompressedLength, data);
        return data;
    }
}

s32 get_asset_offset(char* assetName, s32* compressedSize) {
    poll_hot_assets();

    auto entry = assets.get(assetName);
    if (!entry) {
        PANIC_MSG("Asset not found: %s", assetName);
    }

    AssetCacheValue& value = entry.unwrap();
    *compressedSize = value.header.compressedLength;
    return (s32)(value.base + value.header.offset);
}

void preload_asset(const char* assetName) {
    Asset::preload(assetName);
}

}  // extern "C"

} // namespace asset
} // namespace dx
