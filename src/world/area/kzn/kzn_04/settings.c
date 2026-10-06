#include "kzn_04.h"

EntryList Entrances = {
    [kzn_04_ENTRY_0]    { -560.0,  500.0,    5.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
