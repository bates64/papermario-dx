#include "kzn_17.h"

EntryList Entrances = {
    [kzn_17_ENTRY_0]    { -670.0,    0.0,  160.0,   90.0 },
    [kzn_17_ENTRY_1]    {  620.0,    0.0,   30.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_17 },
    .songVariation = 1,
    .sfxReverb = 2,
};
