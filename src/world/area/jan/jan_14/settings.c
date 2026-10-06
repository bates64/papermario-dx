#include "jan_14.h"

EntryList Entrances = {
    [jan_14_ENTRY_0]    { -250.0,    0.0,  120.0,    0.0 },
    [jan_14_ENTRY_1]    {  250.0,    0.0, -120.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_14 },
    .songVariation = 1,
    .sfxReverb = 1,
};
