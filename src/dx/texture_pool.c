#include "dx/texture_pool.h"

#include "tex_pool_table.h"

/// FNV-1a. tools/build/tex_pool.py hashes texture names the same way.
static u32 hash_texture_name(const char* name) {
    u32 hash = 0x811C9DC5;

    while (*name != '\0') {
        hash ^= (u8) *name++;
        hash *= 0x01000193;
    }
    return hash;
}

s32 tex_pool_find(const char* name) {
    u32 hash = hash_texture_name(name);
    s32 low = 0;
    s32 high = gTexturePoolCount - 1;

    while (low <= high) {
        s32 mid = (low + high) / 2;
        u32 midHash = gTexturePoolHashes[mid];

        if (midHash == hash) {
            return gTexturePoolHashIndices[mid];
        } else if (midHash < hash) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}
