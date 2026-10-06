#include "isk_05.h"

EntryList Entrances = {
    [isk_05_ENTRY_0]    {  463.0,   25.0, -279.0,  320.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
