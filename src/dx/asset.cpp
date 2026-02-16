#include "dx/prelude.h"
#include "functions.h"
#include "ld_addrs.h"
#include <string.h>

b32 _assetsDirty = false;

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

    // Allocate decompressed buffer FIRST (larger, needs more space)
    // This is more likely to succeed right after freeing the old asset
    u8* decompressedData;
    if (compressedLength != decompressedLength) {
        decompressedData = new u8[decompressedLength];
    }

    // Now allocate and load compressed data (smaller, easier to find space)
    u8* compressedData = new u8[compressedLength];
    dma_copy(romStart, romStart + compressedLength, compressedData);

    // Decompress if necessary
    if (compressedLength != decompressedLength) {
        if (compressedData[0] == 'Y' && compressedData[1] == 'a' && compressedData[2] == 'y' && compressedData[3] == '0')
            decode_yay0(compressedData, decompressedData);
        else PANIC();

        delete[] compressedData;
    } else {
        decompressedData = compressedData;
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

    // Asset was freed - load it fresh
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

    // Load compressed data
    u8* romStart = value.base + value.header.offset;
    void* compressedData = general_heap_malloc(value.header.compressedLength);
    dma_copy(romStart, romStart + value.header.compressedLength, compressedData);

    return compressedData;  // Returns compressed data (caller decompresses)
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

}  // extern "C"

} // namespace asset
} // namespace dx
