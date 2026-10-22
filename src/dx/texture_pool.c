#include "dx/texture_pool.h"
#include <string.h>

#include "tex_pool_table.h"

TexPoolEntry* tex_pool_lookup(const char* name) {
    if (name == nullptr) {
        return nullptr;
    }

    for (TexPoolEntry* entry = gTexturePoolEntries; entry->name[0] != '\0'; entry++) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
    }

    return nullptr;
}

void tex_pool_clear_assignments(void) {
    for (s32 i = 0; i < ARRAY_COUNT(gTexturePoolEntries); i++) {
        gTexturePoolEntries[i].assignedHandleIdx = TXP_UNASSIGNED;
    }
}
