#include "tik_25.h"

EntryList Entrances = {
    [tik_25_ENTRY_0]    {  325.0, -135.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_25 },
    .songVariation = 1,
    .sfxReverb = 2,
};
