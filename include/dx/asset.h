#pragma once

#include "common.h"
#include "dx/prelude.h"
#include "dx/rc.h"

/// Header at the start of each asset table
struct AssetTableHeader {
    char magic[8];       // 0x00  "MAPFS\0\0\0"
    u32  entryCount;     // 0x08  Number of assets in this table
    u32  nextTable;      // 0x0C  ROM address of next table header, or 0
    u32  entriesHash;    // 0x10  Hash of entry names
    u8   generation;     // 0x14  Incremented (with overflow) on overwrite
    u8   reserved[11];   // 0x15  Reserved for future use
};                       // 0x20 = 32 bytes total

/// Asset info from the asset table.
struct AssetHeader {
    char name[64];
    u32 offset;
    u32 compressedLength;
    u32 decompressedLength;
    u32 hash;  // Hash of compressed data (0 for vanilla assets)
};

/// Global for tooling - set to true to force table-of-contents reload
EXTERN_C b32 _assetsDirty;

// Legacy C API
EXTERN_C void* load_asset_by_name(const char* assetName, u32* decompressedSize);
EXTERN_C s32 get_asset_offset(char* assetName, s32* compressedSize);

#ifdef __cplusplus

namespace dx {
namespace asset {

/// An asset loaded from the ROM.
/// Assets are shared - multiple loads of the same asset return references to the same data.
/// Hot reload updates the shared data in-place and increments the generation counter.
class Asset {
public:
    ~Asset();

    /// Get pointer to asset data
    /// WARNING: Pointer may become invalid if asset is reloaded. Don't cache it. Don't write to it.
    void* data() const { return dataPtr; }

    /// Get size of asset data in bytes
    u32 size() const { return dataSize; }

    /// Get generation counter - increments each time asset is hot reloaded
    /// Use this to detect when an asset has changed and rebuild derived data
    u32 generation() const { return gen; }

    /// Loads and decompresses an asset by name
    /// Returns a shared reference - multiple loads of the same asset return the same instance
    /// Panics if asset not found
    static rc::Rc<Asset> load(const char* name);

    /// Polls for asset changes and reloads modified assets (call each frame)
    static void pollForChanges();

    /// Loads data from ROM (replaces data in-place, increments generation)
    /// Internal use only - called automatically by the asset system during hot reload
    void reload(u8* base, u32 offset, u32 compressedLength, u32 decompressedLength);

    // Constructor for Rc::make
    Asset(void* data, u32 size, u32 generation);

private:
    // Non-copyable, non-movable (Rc handles sharing)
    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;
    Asset(Asset&&) = delete;
    Asset& operator=(Asset&&) = delete;

    void* dataPtr;
    u32 dataSize;
    u32 gen;
};

} // namespace asset
} // namespace dx

#endif
