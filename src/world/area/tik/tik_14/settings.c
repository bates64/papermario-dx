#include "tik_14.h"

EntryList Entrances = {
    [tik_14_ENTRY_0]    { -173.0,    0.0,    0.0,   90.0 },
    [tik_14_ENTRY_1]    {   30.0,    0.0,   45.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
