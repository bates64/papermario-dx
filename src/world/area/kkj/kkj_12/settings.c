#include "kkj_12.h"

EntryList Entrances = {
    [kkj_12_ENTRY_0]    {  -75.0,    0.0,    0.0,   90.0 },
    [kkj_12_ENTRY_1]    { 1175.0,  110.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
