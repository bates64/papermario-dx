#include "hos_06.h"

EntryList N(Entrances) = {
    [hos_06_ENTRY_0]    { -484.0,    0.0,    5.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_06 },
};
