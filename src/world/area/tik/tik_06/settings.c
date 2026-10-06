#include "tik_06.h"

EntryList Entrances = {
    [tik_06_ENTRY_0]    { -520.0,  -10.0,    0.0,   90.0 },
    [tik_06_ENTRY_1]    {  170.0,  -10.0,    0.0,  270.0 },
    [tik_06_ENTRY_2]    { -500.0,   90.0,  -90.0,   90.0 },
    [tik_06_ENTRY_3]    { -244.0,  -10.0, -110.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_06 },
    .songVariation = 1,
    .sfxReverb = 2,
};
