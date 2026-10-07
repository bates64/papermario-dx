#include "isk_10.h"

EntryList Entrances = {
    [isk_10_ENTRY_0]    { -594.0, -520.0,   84.0,    0.0 },
    [isk_10_ENTRY_1]    { -575.0, -780.0,  -81.0,  180.0 },
    [isk_10_ENTRY_2]    { -577.0, -780.0,   81.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
