#include "jan_12.h"

EntryList Entrances = {
    [jan_12_ENTRY_0]    { -300.0,    0.0,  120.0,    0.0 },
    [jan_12_ENTRY_1]    {  250.0,    0.0, -120.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_12 },
    .songVariation = 1,
    .sfxReverb = 1,
};
