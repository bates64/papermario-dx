#include "sam_08.h"

EntryList Entrances = {
    [sam_08_ENTRY_0]    { -1527.0, -120.0,    0.0,   90.0 },
    [sam_08_ENTRY_1]    { -150.0,    0.0,  -80.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_08 },
    .songVariation = 1,
    .sfxReverb = 1,
};
