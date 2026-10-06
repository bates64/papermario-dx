#include "kzn_11.h"

EntryList Entrances = {
    [kzn_11_ENTRY_0]    { -810.0,   20.0,    0.0,   90.0 },
    [kzn_11_ENTRY_1]    {  810.0,   20.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_11 },
    .songVariation = 1,
    .sfxReverb = 2,
};
