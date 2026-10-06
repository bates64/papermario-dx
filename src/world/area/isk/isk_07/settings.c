#include "isk_07.h"

EntryList Entrances = {
    [isk_07_ENTRY_0]    { -283.0, -390.0,  530.0,  110.0 },
    [isk_07_ENTRY_1]    {  560.0, -340.0,  217.0,  210.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
