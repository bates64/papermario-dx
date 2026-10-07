#include "isk_16.h"

EntryList Entrances = {
    [isk_16_ENTRY_0]    {  307.0, -910.0,  492.0,   50.0 },
    [isk_16_ENTRY_1]    {  492.0, -910.0,  307.0,  220.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_16 },
    .songVariation = 1,
    .sfxReverb = 2,
};
