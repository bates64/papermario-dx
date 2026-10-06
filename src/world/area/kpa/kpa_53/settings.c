#include "kpa_53.h"

EntryList Entrances = {
    [kpa_53_ENTRY_0]    { -480.0,    0.0,  -28.0,   90.0 },
    [kpa_53_ENTRY_1]    {  768.0,    0.0,  -28.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_53 },
    .songVariation = 1,
    .sfxReverb = 2,
};
