#include "dx/prelude.h"
#include "functions.h"
#include "ld_addrs.h"
#include <string.h>

b32 _assetsDirty = false;

#define ASSET_TABLE_ROM_START (s32) mapfs_ROM_START

#define ASSET_TABLE_HEADER_SIZE 0x20
#define ASSET_TABLE_FIRST_ENTRY (ASSET_TABLE_ROM_START + ASSET_TABLE_HEADER_SIZE)

namespace dx {

// Cache value: stores location info for an asset
struct AssetCacheValue {
    u8* base;              // ROM base address for this asset's table
    AssetHeader header;    // Asset metadata
};

// Caches info per asset so that we don't have to do a linear lookup every load
static HashMap<String, AssetCacheValue> assets;
static bool assetsLoaded = false;

void Asset::init() {
    if (assetsLoaded && !_assetsDirty) {
        return;
    }

    // Clear old cache if rebuilding
    assets.clear();

    // Traverse all asset tables
    u8* base = (u8*) ASSET_TABLE_FIRST_ENTRY;
    AssetHeader firstHeader;
    AssetHeader* assetTableBuffer;
    AssetHeader* curAsset;

    dma_copy(base, base + sizeof(AssetHeader), &firstHeader);
    assetTableBuffer = (AssetHeader*) heap_malloc(firstHeader.offset);
    curAsset = &assetTableBuffer[0];
    dma_copy(base, base + firstHeader.offset, assetTableBuffer);

    // Traverse entire chain to find all assets (last instance wins - for mods)
    while (true) {
        if (strcmp(curAsset->name, "END DATA") == 0) {
            if (curAsset->decompressedLength == 0) {
                // End of chain
                break;
            }
            // Follow link to next asset table (stored in decompressedLength)
            base = (u8*) curAsset->decompressedLength;
            dma_copy(base, base + sizeof(AssetHeader), &firstHeader);
            heap_free(assetTableBuffer);
            assetTableBuffer = (AssetHeader*) heap_malloc(firstHeader.offset);
            curAsset = &assetTableBuffer[0];
            dma_copy(base, base + firstHeader.offset, assetTableBuffer);
        } else {
            // Upsert asset in cache
            assets.emplace(curAsset->name, AssetCacheValue { base, *curAsset });
            curAsset++;
        }
    }

    heap_free(assetTableBuffer);
    assetsLoaded = true;
    _assetsDirty = false;
}

Asset::Asset(void* data, u32 size)
    : dataPtr(data), dataSize(size) {}

Asset::~Asset() {
    delete[] static_cast<u8*>(dataPtr);
}

Asset::Asset(Asset&& other)
    : dataPtr(other.dataPtr), dataSize(other.dataSize) {
    other.dataPtr = nullptr;
    other.dataSize = 0;
}

Asset& Asset::operator=(Asset&& other) {
    if (this != &other) {
        delete[] static_cast<u8*>(dataPtr);
        dataPtr = other.dataPtr;
        dataSize = other.dataSize;
        other.dataPtr = nullptr;
        other.dataSize = 0;
    }
    return *this;
}

Asset Asset::load(const char* name) {
    init();

    // Look up asset in cache
    auto entry = assets.get(String(name));
    if (!entry) {
        PANIC_MSG("Asset not found: %s", name);
    }

    AssetCacheValue& value = entry.unwrap();
    u8* romStart = value.base + value.header.offset;
    u32 compressedSize = value.header.compressedLength;
    u32 decompressedSize = value.header.decompressedLength;

    // Allocate and load compressed data
    u8* compressedData = new u8[compressedSize];
    dma_copy(romStart, romStart + compressedSize, compressedData);

    // Allocate and decompress
    u8* decompressedData = new u8[decompressedSize];
    decode_yay0(compressedData, decompressedData);

    // Free compressed data
    delete[] compressedData;

    return Asset(decompressedData, decompressedSize);
}

Option<AssetHeader&> Asset::get_info(const char* name) {
    init();
    auto entry = assets.get(String(name));
    if (entry) {
        return Option<AssetHeader&>::some(entry->header);
    }
    return Option<AssetHeader&>::none();
}

} // namespace dx

// Legacy C API implementations
extern "C" {

using namespace dx;

void* load_asset_by_name(const char* assetName, u32* decompressedSize) {
    Asset::init();

    auto entry = assets.get(String(assetName));
    if (!entry) {
        ASSERT_MSG(false, "Asset not found: %s", assetName);
        return nullptr;
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
    Asset::init();

    auto entry = assets.get(String(assetName));
    if (!entry) {
        ASSERT_MSG(false, "Asset not found: %s", assetName);
        return 0;
    }

    AssetCacheValue& value = entry.unwrap();
    *compressedSize = value.header.compressedLength;
    return (s32)(value.base + value.header.offset);
}

}  // extern "C"
