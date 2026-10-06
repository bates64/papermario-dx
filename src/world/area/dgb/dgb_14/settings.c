#include "dgb_14.h"

EntryList Entrances = {
    [dgb_14_ENTRY_0]    {  575.0,    0.0,  180.0,  270.0 },
    [dgb_14_ENTRY_1]    {  575.0,  210.0,  180.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
