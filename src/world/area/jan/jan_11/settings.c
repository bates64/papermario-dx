#include "jan_11.h"

EntryList Entrances = {
    [jan_11_ENTRY_0]    {  -90.0,    0.0,   61.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_jan_11 },
    .songVariation = 1,
    .sfxReverb = 2,
};
