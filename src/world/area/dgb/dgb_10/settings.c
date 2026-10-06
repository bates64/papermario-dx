#include "dgb_10.h"

EntryList Entrances = {
    [dgb_10_ENTRY_0]    {  300.0,    0.0,  -50.0,    0.0 },
    [dgb_10_ENTRY_1]    {  375.0,    0.0, -240.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
