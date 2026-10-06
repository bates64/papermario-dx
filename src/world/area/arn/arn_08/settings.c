#include "arn_08.h"

EntryList Entrances = {
    [arn_08_ENTRY_0]    {  -80.0,    0.0,  108.0,   45.0 },
    [arn_08_ENTRY_1]    {    0.0,    0.0,    0.0,    0.0 },
    [arn_08_ENTRY_2]    {  -85.0,    0.0,   55.0,   45.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_arn_08 },
    .songVariation = 1,
    .sfxReverb = 1,
};
