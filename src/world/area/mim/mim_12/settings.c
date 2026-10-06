#include "mim_12.h"

EntryList Entrances = {
    [mim_12_ENTRY_0]    { -380.0,    0.0,   10.0,   90.0 },
    [mim_12_ENTRY_1]    {  380.0,    0.0,   10.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_mim_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
