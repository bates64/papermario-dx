#include "kzn_05.h"

EntryList Entrances = {
    [kzn_05_ENTRY_0]    { -430.0, -259.0,   10.0,   90.0 },
    [kzn_05_ENTRY_1]    {  450.0,    0.0,   10.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
