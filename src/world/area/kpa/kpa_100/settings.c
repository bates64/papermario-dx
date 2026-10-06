#include "kpa_100.h"

EntryList Entrances = {
    [kpa_100_ENTRY_0]   { -208.0,    0.0,  100.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_100 },
    .songVariation = 1,
    .sfxReverb = 1,
};
