#include "omo_09.h"

EntryList Entrances = {
    [omo_09_ENTRY_0]    { -980.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
