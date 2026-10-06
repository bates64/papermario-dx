#include "dgb_02.h"

EntryList Entrances = {
    [dgb_02_ENTRY_0]    { -567.0,    0.0,  180.0,   90.0 },
    [dgb_02_ENTRY_1]    {  567.0,    0.0,  180.0,  270.0 },
    [dgb_02_ENTRY_2]    { -450.0,    0.0,   88.0,  180.0 },
    [dgb_02_ENTRY_3]    {  450.0,    0.0,   88.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
