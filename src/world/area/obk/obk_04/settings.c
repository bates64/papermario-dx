#include "obk_04.h"

EntryList Entrances = {
    [obk_04_ENTRY_0]    { -235.0,    0.0,    5.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_obk_04 },
    .songVariation = 1,
    .sfxReverb = 1,
};
