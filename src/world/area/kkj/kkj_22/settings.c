#include "kkj_22.h"

EntryList Entrances = {
    [kkj_22_ENTRY_0]    { -225.0,    0.0,  -45.0,   90.0 },
    [kkj_22_ENTRY_1]    { -395.0,  300.0, -115.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_22 },
    .songVariation = 1,
    .sfxReverb = 2,
};
