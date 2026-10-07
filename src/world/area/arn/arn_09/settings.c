#include "arn_09.h"

EntryList Entrances = {
    [arn_09_ENTRY_0]    {  125.0,    0.0,    0.0,  270.0 },
    [arn_09_ENTRY_1]    {    0.0,  200.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_arn_09 },
    .songVariation = 1,
    .sfxReverb = 1,
};
