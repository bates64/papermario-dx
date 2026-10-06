#include "obk_05.h"

EntryList Entrances = {
    [obk_05_ENTRY_0]    {  -68.0,    0.0,  235.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_obk_05 },
    .songVariation = 1,
    .sfxReverb = 1,
};
