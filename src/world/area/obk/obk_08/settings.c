#include "obk_08.h"

EntryList Entrances = {
    [obk_08_ENTRY_0]    {  -68.0,    0.0,  235.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_obk_08 },
    .songVariation = 1,
    .sfxReverb = 1,
};
