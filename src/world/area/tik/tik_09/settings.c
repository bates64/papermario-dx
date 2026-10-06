#include "tik_09.h"

EntryList Entrances = {
    [tik_09_ENTRY_0]    { -225.0,  -10.0,    0.0,   90.0 },
    [tik_09_ENTRY_1]    {  325.0,  -10.0,    0.0,  270.0 },
    [tik_09_ENTRY_2]    {  -30.0,   25.0,  -40.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
