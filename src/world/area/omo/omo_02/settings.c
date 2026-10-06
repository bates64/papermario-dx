#include "omo_02.h"

EntryList Entrances = {
    [omo_02_ENTRY_0]    { -970.0,    0.0,    0.0,   90.0 },
    [omo_02_ENTRY_1]    {  360.0,    0.0,   20.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
