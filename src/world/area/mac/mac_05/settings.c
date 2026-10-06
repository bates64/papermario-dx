#include "mac_05.h"

EntryList Entrances = {
    [mac_05_ENTRY_0]    {  426.0,    0.0, -426.0,  225.0 },
    [mac_05_ENTRY_1]    {    0.0,    0.0,    0.0,    0.0 },
    [mac_05_ENTRY_2]    { -120.0,   24.0,  375.0,    0.0 },
    [mac_05_ENTRY_3]    { -280.0,  -10.0,  371.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mac_05 },
};
