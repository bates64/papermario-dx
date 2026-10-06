#include "tik_17.h"

EntryList Entrances = {
    [tik_17_ENTRY_0]    {  400.0,   20.0,   10.0,  180.0 },
    [tik_17_ENTRY_1]    {  720.0,   65.0,    5.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_17 },
    .songVariation = 1,
    .sfxReverb = 2,
};
