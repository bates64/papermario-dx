#include "kpa_16.h"

EntryList Entrances = {
    [kpa_16_ENTRY_0]    {   25.0,    0.0,  -92.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_16 },
    .songVariation = 1,
    .sfxReverb = 3,
};
