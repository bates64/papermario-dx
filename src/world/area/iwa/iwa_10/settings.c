#include "iwa_10.h"

EntryList Entrances = {
    [iwa_10_ENTRY_0]    { -1250.0,   30.0,    0.0,   90.0 },
    [iwa_10_ENTRY_1]    { -445.0,  215.0, -500.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_10 },
};
