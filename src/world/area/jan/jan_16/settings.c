#include "jan_16.h"

EntryList Entrances = {
    [jan_16_ENTRY_0]    { -480.0,    0.0,    0.0,   90.0 },
    [jan_16_ENTRY_1]    {  480.0,    0.0,    0.0,  270.0 },
    [jan_16_ENTRY_2]    { -247.0,    0.0,    0.0,  225.0 },
    [jan_16_ENTRY_3]    { -390.0,    0.0,   20.0,  100.0 },
    [jan_16_ENTRY_4]    {   35.0,  600.0,  330.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_16 },
    .songVariation = 1,
    .sfxReverb = 1,
};
