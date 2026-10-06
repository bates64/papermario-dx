#include "kpa_101.h"

EntryList Entrances = {
    [kpa_101_ENTRY_0]   {    6.0,    0.0,  100.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_101 },
    .songVariation = 1,
    .sfxReverb = 1,
};
