#include "kzn_23.h"

EntryList Entrances = {
    [kzn_23_ENTRY_0]    {    0.0,    0.0,  100.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .songVariation = 1,
    .sfxReverb = 2,
};
