#include "dgb_15.h"

EntryList Entrances = {
    [dgb_15_ENTRY_0]    { -1290.0,    0.0,  180.0,   90.0 },
    [dgb_15_ENTRY_1]    {  125.0,    0.0,  180.0,  270.0 },
    [dgb_15_ENTRY_2]    {    0.0,    0.0,   88.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_15 },
    .songVariation = 1,
    .sfxReverb = 2,
};
