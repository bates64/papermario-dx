#include "arn_10.h"

EntryList Entrances = {
    [arn_10_ENTRY_0]    { -225.0,    0.0,    0.0,   90.0 },
    [arn_10_ENTRY_1]    {  225.0,    0.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_arn_10 },
    .songVariation = 1,
    .sfxReverb = 1,
};
