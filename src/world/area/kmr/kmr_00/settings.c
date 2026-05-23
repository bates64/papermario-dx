#include "kmr_00.h"

EntryList N(Entrances) = {
    [kmr_00_ENTRY_0]    {  485.0,    0.0,    0.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_00 },
    .sfxReverb = 1,
};
