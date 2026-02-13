#pragma once

#include "common.h"
#include "dx/prelude.h"

/// Asset info from the asset table.
struct AssetHeader {
    char name[64];
    u32 offset;
    u32 compressedLength;
    u32 decompressedLength;
};

/// Global for tooling - set to true to force table-of-contents reload
EXTERN_C b32 _assetsDirty;

// Legacy C API
EXTERN_C void* load_asset_by_name(const char* assetName, u32* decompressedSize);
EXTERN_C s32 get_asset_offset(char* assetName, s32* compressedSize);

#ifdef __cplusplus

namespace dx {

using option::Option;

/// An asset loaded from the ROM.
class Asset {
public:
    ~Asset();

    void* data() const { return dataPtr; }
    u32 size() const { return dataSize; }

    // Move-only (no copy)
    Asset(Asset&& other);
    Asset& operator=(Asset&& other);

    /// Loads and decompresses an asset by name
    /// Panics if asset not found
    static Asset load(const char* name);

    /// Looks up asset info without loading
    static Option<AssetHeader&> get_info(const char* name);

    /// Initializes asset system (called automatically by load/get_info)
    static void init();

private:
    Asset(void* data, u32 size);
    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;

    void* dataPtr;
    u32 dataSize;
};

} // namespace dx

#endif
