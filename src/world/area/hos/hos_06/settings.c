#include "hos_06.h"

EntryList Entrances = {
    [hos_06_ENTRY_0]    { -484.0,    0.0,    5.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_06 },
};
