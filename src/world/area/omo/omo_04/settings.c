#include "omo_04.h"

EntryList Entrances = {
    [omo_04_ENTRY_0]    { -965.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
