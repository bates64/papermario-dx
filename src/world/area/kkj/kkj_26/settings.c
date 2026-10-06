#include "kkj_26.h"

EntryList Entrances = {
    [kkj_26_ENTRY_0]    {  472.0,   30.0,  -26.0,   90.0 },
    [kkj_26_ENTRY_1]    {  540.0,   30.0,  -20.0,   90.0 },
    [kkj_26_ENTRY_2]    {  400.0,   30.0,  -20.0,   90.0 },
    [kkj_26_ENTRY_3]    {  483.0,   30.0,    8.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_26 },
    .bgName = "kpa_bg",
    .sfxReverb = 2,
};
