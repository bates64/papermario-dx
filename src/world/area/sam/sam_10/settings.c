#include "sam_10.h"

EntryList Entrances = {
    [sam_10_ENTRY_0]    { -730.0,    0.0,    0.0,   90.0 },
    [sam_10_ENTRY_1]    {  985.0, 1140.0, -200.0,  270.0 },
    [sam_10_ENTRY_2]    {  337.0,  -20.0, -104.0,  270.0 },
    [sam_10_ENTRY_3]    { -255.0,  840.0, -215.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_10 },
    .songVariation = 1,
    .sfxReverb = 1,
};
