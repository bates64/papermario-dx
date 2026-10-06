#include "tik_23.h"

EntryList Entrances = {
    [tik_23_ENTRY_0]    { -270.0,  -20.0,  -20.0,   90.0 },
    [tik_23_ENTRY_1]    {  107.0,  -20.0, -115.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_23 },
    .songVariation = 1,
    .sfxReverb = 2,
};
