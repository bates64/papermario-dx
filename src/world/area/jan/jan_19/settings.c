#include "jan_19.h"

EntryList Entrances = {
    [jan_19_ENTRY_0]    { -220.0,    0.0,   10.0,   90.0 },
    [jan_19_ENTRY_1]    {  190.0,  450.0,  110.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_jan_19 },
    .songVariation = 1,
    .sfxReverb = 2,
};
