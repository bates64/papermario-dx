#include "sam_07.h"

EntryList N(Entrances) = {
    [sam_07_ENTRY_0]    { -1500.0, -120.0,  -75.0,   90.0 },
    [sam_07_ENTRY_1]    { 1085.0,  270.0,  -80.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_07 },
    .songVariation = 1,
    .sfxReverb = 1,
};
