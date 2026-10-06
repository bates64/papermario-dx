#include "kzn_06.h"

EntryList Entrances = {
    [kzn_06_ENTRY_0]    {  385.0,  115.0,   55.0,  270.0 },
    [kzn_06_ENTRY_1]    { -385.0,   75.0,   68.0,   90.0 },
    [kzn_06_ENTRY_2]    {  400.0,    5.0,  175.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_06 },
    .songVariation = 1,
    .sfxReverb = 2,
};
