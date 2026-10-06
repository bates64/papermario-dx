#include "isk_01.h"

EntryList Entrances = {
    [isk_01_ENTRY_0]    { -576.0,    0.0,  -71.0,  179.0 },
    [isk_01_ENTRY_1]    { -555.0,    0.0,  170.0,  350.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk3_bg",
    .tattle = { MSG_MapTattle_isk_01 },
    .songVariation = 1,
    .sfxReverb = 2,
};
