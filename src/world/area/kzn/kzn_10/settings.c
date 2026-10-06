#include "kzn_10.h"

EntryList Entrances = {
    [kzn_10_ENTRY_0]    { -445.0,    0.0,    0.0,   90.0 },
    [kzn_10_ENTRY_1]    {  425.0, -259.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
