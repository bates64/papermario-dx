#include "kzn_02.h"

EntryList Entrances = {
    [kzn_02_ENTRY_0]    { -810.0,   20.0,  -10.0,   90.0 },
    [kzn_02_ENTRY_1]    {  810.0,   20.0,  -10.0,  270.0 },
    [kzn_02_ENTRY_2]    { -810.0,   20.0,  -10.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
