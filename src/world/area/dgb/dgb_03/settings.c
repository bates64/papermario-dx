#include "dgb_03.h"

EntryList Entrances = {
    [dgb_03_ENTRY_0]    { -343.0,    0.0,   80.0,   90.0 },
    [dgb_03_ENTRY_1]    {  343.0,    0.0,   80.0,  270.0 },
    [dgb_03_ENTRY_2]    { -220.0,    0.0, -170.0,  180.0 },
    [dgb_03_ENTRY_3]    { -343.0,  210.0,   80.0,   90.0 },
    [dgb_03_ENTRY_4]    {  343.0,  210.0,   80.0,  270.0 },
    [dgb_03_ENTRY_5]    { -220.0,  210.0, -170.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_03 },
    .songVariation = 1,
    .sfxReverb = 2,
};
