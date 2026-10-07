#include "tik_15.h"

EntryList Entrances = {
    [tik_15_ENTRY_0]    { -230.0,  -10.0,    0.0,   90.0 },
    [tik_15_ENTRY_1]    {   75.0,  -10.0,  -15.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_15 },
    .songVariation = 1,
    .sfxReverb = 2,
};
