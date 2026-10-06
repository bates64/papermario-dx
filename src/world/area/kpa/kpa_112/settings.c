#include "kpa_112.h"

EntryList Entrances = {
    [kpa_112_ENTRY_0]   { -150.0,    0.0,  110.0,    0.0 },
    [kpa_112_ENTRY_1]   {  473.0,    0.0,  112.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_112 },
    .songVariation = 1,
    .sfxReverb = 2,
};
