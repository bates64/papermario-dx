#include "obk_03.h"

EntryList Entrances = {
    [obk_03_ENTRY_0]    {  -20.0,    0.0, -235.0,  180.0 },
    [obk_03_ENTRY_1]    {  240.0,    0.0,    0.0,  270.0 },
    [obk_03_ENTRY_2]    {  660.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_obk_03 },
    .songVariation = 1,
    .sfxReverb = 1,
};
