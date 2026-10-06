#include "dgb_04.h"

EntryList Entrances = {
    [dgb_04_ENTRY_0]    {  575.0,    0.0,  180.0,  270.0 },
    [dgb_04_ENTRY_1]    {  575.0, -420.0,  180.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
