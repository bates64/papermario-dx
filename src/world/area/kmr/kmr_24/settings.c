#include "kmr_24.h"

// skip loading shape/hit/tex for this map
export s32 map_init(void) {
    return true;
}

EntryList Entrances = {
    [kmr_24_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
