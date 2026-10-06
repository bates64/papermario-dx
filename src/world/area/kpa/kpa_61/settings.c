#include "kpa_61.h"

EntryList Entrances = {
    [kpa_61_ENTRY_0]    { -100.0, -160.0,  116.0,  120.0 },
    [kpa_61_ENTRY_1]    { -100.0,  200.0,  102.0,  120.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kpa_61 },
};
