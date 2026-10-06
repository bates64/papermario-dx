#include "isk_14.h"

EntryList Entrances = {
    [isk_14_ENTRY_0]    { -538.0, -780.0, -217.0,   29.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
