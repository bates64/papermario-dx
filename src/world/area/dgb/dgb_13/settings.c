#include "dgb_13.h"

EntryList Entrances = {
    [dgb_13_ENTRY_0]    { -450.0,    0.0,  -40.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_13 },
    .songVariation = 1,
    .sfxReverb = 2,
};
