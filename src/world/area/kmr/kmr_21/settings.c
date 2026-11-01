#include "kmr_21.h"

// skip loading shape/hit/tex for this map
export s32 map_init(void) {
    return true;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};
