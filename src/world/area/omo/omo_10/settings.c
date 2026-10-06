#include "omo_10.h"

EntryList Entrances = {
    [omo_10_ENTRY_0]    { -330.0,    0.0,  330.0,   45.0 },
    [omo_10_ENTRY_1]    {  330.0,    0.0,  330.0,  315.0 },
    [omo_10_ENTRY_2]    { -330.0,   10.0, -330.0,  135.0 },
    [omo_10_ENTRY_3]    {  330.0,   10.0, -330.0,  225.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
