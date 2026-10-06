#include "tik_08.h"

EntryList Entrances = {
    [tik_08_ENTRY_0]    { -520.0,  -10.0,    0.0,   90.0 },
    [tik_08_ENTRY_1]    {  170.0,  -10.0,    0.0,  270.0 },
    [tik_08_ENTRY_2]    { -375.0,  200.0,    0.0,   90.0 },
    [tik_08_ENTRY_3]    { -467.0,  -10.0, -110.0,   90.0 },
    [tik_08_ENTRY_4]    {   95.0,   25.0,  -88.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
