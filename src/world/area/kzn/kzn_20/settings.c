#include "kzn_20.h"

EntryList Entrances = {
    [kzn_20_ENTRY_0]    { -182.0,    0.0,   36.0,   90.0 },
    [kzn_20_ENTRY_1]    {  164.0,  150.0,   20.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_20 },
    .songVariation = 1,
    .sfxReverb = 2,
};
