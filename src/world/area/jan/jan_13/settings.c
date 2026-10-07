#include "jan_13.h"

EntryList Entrances = {
    [jan_13_ENTRY_0]    { -300.0,    0.0,  120.0,    0.0 },
    [jan_13_ENTRY_1]    {   55.0,    0.0, -120.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_13 },
    .songVariation = 1,
    .sfxReverb = 1,
};
