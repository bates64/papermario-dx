#include "tik_19.h"

EntryList Entrances = {
    [tik_19_ENTRY_0]    { -170.0,  -10.0,  -90.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_19 },
    .songVariation = 1,
    .sfxReverb = 2,
};
