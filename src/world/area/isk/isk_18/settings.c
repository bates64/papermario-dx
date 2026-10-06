#include "isk_18.h"

EntryList Entrances = {
    [isk_18_ENTRY_0]    { -528.0, -780.0,  217.0,  150.0 },
    [isk_18_ENTRY_1]    {  431.0, -780.0,  388.0,  230.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_18 },
    .songVariation = 1,
    .sfxReverb = 2,
};
