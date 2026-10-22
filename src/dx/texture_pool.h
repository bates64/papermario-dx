#pragma once

#include "common.h"

/// Where a texture is in the texture pool, which holds every map's textures. Entries are in their texture archives'
/// order, so a texture's variants are the entries after it.
typedef struct TexPoolEntry {
    /* 0x00 */ u32 romStart; ///< Offset from tex_pool_ROM_START of the texture's header
    /* 0x04 */ u32 size;     ///< Size of the header and every image and palette after it
} TexPoolEntry; // size = 0x08

extern const TexPoolEntry gTexturePoolEntries[];
extern const s32 gTexturePoolCount;

/// How many of the entries after each pool texture are its variants.
extern const u8 gTexturePoolVariantCounts[];

/// The texture handle each pool texture is loaded into, or 0 if it isn't loaded.
extern u8 gTexturePoolHandles[];

/// The index in the pool of the texture named `name`, or -1 if the pool has no texture with that name.
s32 tex_pool_find(const char* name);
