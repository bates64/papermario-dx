#include "kmr_00.h"

EntryList Entrances = {
    [kmr_00_ENTRY_0]    {  485.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_00 },
    .sfxReverb = 1,
};
