#include "isk_06.h"

EntryList Entrances = {
    [isk_06_ENTRY_0]    {  471.0,  -80.0, -290.0,  320.0 },
    [isk_06_ENTRY_1]    {  509.0, -270.0, -318.0,  320.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_06 },
    .songVariation = 1,
    .sfxReverb = 2,
};
