#include "end_01.h"

export s32 map_init(void) {
    return false;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};
