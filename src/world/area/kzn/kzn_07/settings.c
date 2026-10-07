#include "kzn_07.h"

EntryList Entrances = {
    [kzn_07_ENTRY_0]    {  290.0,    0.0,   70.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
