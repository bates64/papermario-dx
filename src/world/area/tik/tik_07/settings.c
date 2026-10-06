#include "tik_07.h"

EntryList Entrances = {
    [tik_07_ENTRY_0]    { -270.0,  -10.0,    0.0,   90.0 },
    [tik_07_ENTRY_1]    { -275.0,   90.0, -110.0,  180.0 },
    [tik_07_ENTRY_2]    {  525.0,   25.0, -100.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
