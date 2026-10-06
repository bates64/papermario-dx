#include "kmr_23.h"

// skip loading shape/hit/tex for this map
export s32 map_init(void) {
    return true;
}

EntryList Entrances = {
    [kmr_23_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_1]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_2]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_3]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_4]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_5]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_6]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_23_ENTRY_7]    {    0.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
