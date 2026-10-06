#include "tik_10.h"

EntryList Entrances = {
    [tik_10_ENTRY_0]    {  330.0,   20.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
