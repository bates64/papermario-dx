#pragma once

#include "common.h"

#define TXP_UNASSIGNED -1

/// A texture in the texture pool, which holds every map's textures.
typedef struct TexPoolEntry {
    /* 0x00 */ const char name[32];
    /* 0x20 */ const u32 romStart; ///< Offset from tex_pool_ROM_START
    /* 0x24 */ const u32 romEnd;
    /* 0x28 */ s32 assignedHandleIdx; ///< The texture handle it's loaded into, or TXP_UNASSIGNED
    /* 0x2C */ char reserved[4];
} TexPoolEntry; // size = 0x30

extern TexPoolEntry gTexturePoolEntries[];

/// The texture named `name`, or nullptr if the pool has no texture with that name.
TexPoolEntry* tex_pool_lookup(const char* name);

/// Forgets which textures are loaded, before a map or battle loads its textures.
void tex_pool_clear_assignments(void);
