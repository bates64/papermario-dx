#include "tik_20.h"

EntryList Entrances = {
    [tik_20_ENTRY_0]    { -320.0,  -20.0,    0.0,   90.0 },
    [tik_20_ENTRY_1]    {  507.0,  -20.0,    0.0,  270.0 },
    [tik_20_ENTRY_2]    {  207.0,   60.0, -100.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_20 },
    .songVariation = 1,
    .sfxReverb = 2,
};
