#include "tik_12.h"

EntryList Entrances = {
    [tik_12_ENTRY_0]    { -173.0, -135.0, -100.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
