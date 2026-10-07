#include "mim_07.h"

EntryList Entrances = {
    [mim_07_ENTRY_0]    {    0.0,    0.0, -530.0,  180.0 },
    [mim_07_ENTRY_1]    { -530.0,    0.0,    0.0,   90.0 },
    [mim_07_ENTRY_2]    {    0.0,    0.0,  530.0,    0.0 },
    [mim_07_ENTRY_3]    {  530.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_mim_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
