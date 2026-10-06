#include "obk_02.h"

EntryList Entrances = {
    [obk_02_ENTRY_0]    {   67.0,    0.0,  235.0,    0.0 },
    [obk_02_ENTRY_1]    {    0.0, -210.0,  235.0,    0.0 },
    [obk_02_ENTRY_2]    {  220.0, -210.0,   65.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_obk_02 },
    .songVariation = 1,
    .sfxReverb = 1,
};
