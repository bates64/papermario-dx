#include "omo_16.h"

EntryList Entrances = {
    [omo_16_ENTRY_0]    { -1460.0,   50.0,    0.0,   90.0 },
    [omo_16_ENTRY_1]    { 1460.0,   50.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .songVariation = 1,
    .sfxReverb = 2,
};
