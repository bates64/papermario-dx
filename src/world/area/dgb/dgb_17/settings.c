#include "dgb_17.h"

EntryList Entrances = {
    [dgb_17_ENTRY_0]    { -570.0,    0.0,  180.0,   90.0 },
    [dgb_17_ENTRY_1]    { -180.0,    0.0,  180.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_17 },
    .songVariation = 1,
    .sfxReverb = 2,
};
