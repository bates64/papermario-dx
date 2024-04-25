#ifndef DX_TEX_POOL_H
#define DX_TEX_POOL_H

#include "common.h"

#define TXP_UNASSIGNED -1

typedef struct TexPoolEntry {
    /* 0x00 */ const u8 name[32];
    /* 0x20 */ const u32 romStart;
    /* 0x24 */ const u32 romEnd;
    /* 0x28 */ u32 assignedHandleIdx;
    /* 0x2C */ unsigned char reserved[4];
} TexPoolEntry; // size = 0x30

extern TexPoolEntry gTexturePoolEntries[];

TexPoolEntry* tex_pool_lookup(const u8* name);
void tex_pool_clear_assignments();

#endif
