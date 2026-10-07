#include "omo_14.h"

EntryList Entrances = {
    [omo_14_ENTRY_0]    { -260.0,    0.0,   20.0,   90.0 },
    [omo_14_ENTRY_1]    {  230.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_omo_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
