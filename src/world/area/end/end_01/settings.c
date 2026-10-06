#include "end_01.h"

export s32 map_init(void) {
    return false;
}

EntryList Entrances = {
    [end_01_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
