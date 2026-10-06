#include "dgb_09.h"

EntryList Entrances = {
    [dgb_09_ENTRY_0]    { -567.0,    0.0,  180.0,   90.0 },
    [dgb_09_ENTRY_1]    {  567.0,    0.0,  180.0,  270.0 },
    [dgb_09_ENTRY_2]    { -450.0,    0.0,   90.0,  180.0 },
    [dgb_09_ENTRY_3]    {  300.0,    0.0,   90.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
