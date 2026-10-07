#include "sam_07.h"

EntryList Entrances = {
    [sam_07_ENTRY_0]    { -1500.0, -120.0,  -75.0,   90.0 },
    [sam_07_ENTRY_1]    { 1085.0,  270.0,  -80.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_07 },
    .songVariation = 1,
    .sfxReverb = 1,
};
