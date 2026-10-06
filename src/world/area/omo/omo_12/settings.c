#include "omo_12.h"

EntryList Entrances = {
    [omo_12_ENTRY_0]    {  260.0,    0.0,   20.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_omo_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
