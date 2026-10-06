#include "isk_19.h"

EntryList Entrances = {
    [isk_19_ENTRY_0]    {  548.0, -910.0,  182.0,   21.0 },
    [isk_19_ENTRY_1]    {  573.0, -910.0,   21.0,  186.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_19 },
    .songVariation = 1,
    .sfxReverb = 2,
};
