#include "kkj_02.h"

EntryList Entrances = {
    [kkj_02_ENTRY_0]    {  -75.0,    0.0,    0.0,   90.0 },
    [kkj_02_ENTRY_1]    { 1175.0,  110.0,    0.0,  270.0 },
    [kkj_02_ENTRY_2]    {  354.0,    0.0,  294.0,  117.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .sfxReverb = 2,
};
