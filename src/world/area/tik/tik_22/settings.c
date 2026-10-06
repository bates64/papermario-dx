#include "tik_22.h"

EntryList Entrances = {
    [tik_22_ENTRY_0]    { -222.0,    0.0,    0.0,   90.0 },
    [tik_22_ENTRY_1]    {  -50.0,   50.0,   20.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_22 },
    .songVariation = 1,
    .sfxReverb = 2,
};
