#include "kmr_22.h"

export s32 map_init(void) {
    return true;
}

EntryList Entrances = {
    [kmr_22_ENTRY_0]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_1]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_2]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_3]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_4]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_5]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_6]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_7]    {    0.0,    0.0,    0.0,   90.0 },
    [kmr_22_ENTRY_8]    {    0.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
