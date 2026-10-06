#include "omo_07.h"

EntryList Entrances = {
    [omo_07_ENTRY_0]    { -960.0,    0.0,   73.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
