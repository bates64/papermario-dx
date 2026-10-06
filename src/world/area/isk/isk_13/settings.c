#include "isk_13.h"

EntryList Entrances = {
    [isk_13_ENTRY_0]    {  568.0, -650.0, -120.0,  340.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_13 },
    .songVariation = 1,
    .sfxReverb = 2,
};
