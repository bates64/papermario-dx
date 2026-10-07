#include "kpa_01.h"

EntryList Entrances = {
    [kpa_01_ENTRY_0]    {  690.0, -378.0,  337.0,   90.0 },
    [kpa_01_ENTRY_1]    { -511.0,  149.0,   57.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_01 },
    .songVariation = 1,
    .sfxReverb = 3,
};
