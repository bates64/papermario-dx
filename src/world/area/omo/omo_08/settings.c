#include "omo_08.h"

EntryList Entrances = {
    [omo_08_ENTRY_0]    {  333.0,    0.0,  333.0,  315.0 },
    [omo_08_ENTRY_1]    { -335.0,   10.0, -335.0,  135.0 },
    [omo_08_ENTRY_2]    {  340.0,   10.0, -340.0,  225.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
