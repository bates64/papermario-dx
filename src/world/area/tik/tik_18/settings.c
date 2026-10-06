#include "tik_18.h"

EntryList Entrances = {
    [tik_18_ENTRY_0]    { -220.0,  -10.0,    0.0,   90.0 },
    [tik_18_ENTRY_1]    {  320.0,  -10.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_18 },
    .songVariation = 1,
    .sfxReverb = 2,
};
