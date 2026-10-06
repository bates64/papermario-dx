#include "isk_02.h"

EntryList Entrances = {
    [isk_02_ENTRY_0]    { -484.0,    0.0,  302.0,  140.0 },
    [isk_02_ENTRY_1]    {  258.0,   50.0,  486.0,  250.0 },
    [isk_02_ENTRY_2]    {  283.0,  -80.0,  530.0,  250.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk3_bg",
    .tattle = { MSG_MapTattle_isk_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
