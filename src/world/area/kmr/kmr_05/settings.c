#include "kmr_05.h"

EntryList Entrances = {
    [kmr_05_ENTRY_0]    { -110.0,    0.0,  -19.0,   90.0 },
    [kmr_05_ENTRY_1]    { 1397.0,  200.0, -145.0,  220.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_05 },
};
