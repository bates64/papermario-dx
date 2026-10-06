#include "omo_11.h"

EntryList Entrances = {
    [omo_11_ENTRY_0]    { -640.0,    0.0,   20.0,   90.0 },
    [omo_11_ENTRY_1]    {  730.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_11 },
    .songVariation = 1,
    .sfxReverb = 2,
};
