#include "kkj_15.h"

EntryList Entrances = {
    [kkj_15_ENTRY_0]    {  225.0,    0.0,  -80.0,  270.0 },
    [kkj_15_ENTRY_1]    {   50.0,   10.0, -150.0,  270.0 },
    [kkj_15_ENTRY_2]    { -237.0,    0.0,   -5.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_15 },
};
