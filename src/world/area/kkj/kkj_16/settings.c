#include "kkj_16.h"

EntryList Entrances = {
    [kkj_16_ENTRY_0]    {  435.0,    0.0,  -25.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_16 },
    .sfxReverb = 1,
};
