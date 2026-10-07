#include "tik_02.h"

EntryList Entrances = {
    [tik_02_ENTRY_0]    { -360.0,  -10.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
