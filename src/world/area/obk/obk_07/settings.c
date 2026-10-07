#include "obk_07.h"

EntryList Entrances = {
    [obk_07_ENTRY_0]    {   68.0,    0.0,  235.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_obk_07 },
    .songVariation = 1,
    .sfxReverb = 1,
};
