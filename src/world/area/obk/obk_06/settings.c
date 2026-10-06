#include "obk_06.h"

EntryList Entrances = {
    [obk_06_ENTRY_0]    {    0.0,  200.0,    0.0,    0.0 },
    [obk_06_ENTRY_1]    { -220.0,    0.0,   50.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_obk_06 },
    .songVariation = 1,
    .sfxReverb = 1,
};
