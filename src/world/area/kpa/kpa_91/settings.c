#include "kpa_91.h"

EntryList Entrances = {
    [kpa_91_ENTRY_0]    { -200.0,    0.0,  100.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_91 },
    .songVariation = 1,
    .sfxReverb = 2,
};
