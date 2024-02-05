#include "kpa_08.h"

EntryList N(Entrances) = {
    [kpa_08_ENTRY_0]    { -483.0,    0.0,  -19.0,   90.0 },
    [kpa_08_ENTRY_1]    {  203.0,  100.0,  -22.0,  270.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .tattle = { MSG_MapTattle_kpa_08 },
};
