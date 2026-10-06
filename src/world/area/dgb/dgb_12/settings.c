#include "dgb_12.h"

EntryList Entrances = {
    [dgb_12_ENTRY_0]    { -500.0,    0.0,  -40.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
