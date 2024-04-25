#include "ld_addrs.h"
#include "dx/texture_pool.h"

#include "tex_pool_table.h"

TexPoolEntry* tex_pool_lookup(const u8* name) {
    TexPoolEntry* ptr = &gTexturePoolEntries;

    if (name == NULL) {
        return NULL;
    }

    while (ptr->name != NULL) {
        if (strcmp(ptr->name, name) == 0) {
            return ptr;
        }
        ptr++;
    }

    return NULL;
}

void tex_pool_clear_assignments() {
    for (s32 i = 0; i < ARRAY_COUNT(gTexturePoolEntries); i++) {
        gTexturePoolEntries[i].assignedHandleIdx = TXP_UNASSIGNED;
    }
}
