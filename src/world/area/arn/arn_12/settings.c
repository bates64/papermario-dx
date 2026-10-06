#include "arn_12.h"

EntryList Entrances = {
    [arn_12_ENTRY_0]    { -231.0,    0.0,    5.0,   90.0 },
    [arn_12_ENTRY_1]    {  231.0,    0.0,    5.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_arn_12 },
    .songVariation = 1,
    .sfxReverb = 1,
};
