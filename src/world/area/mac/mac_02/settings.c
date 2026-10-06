#include "mac_02.h"

EntryList Entrances = {
    [mac_02_ENTRY_0]    { -600.0,    0.0,    0.0,   90.0 },
    [mac_02_ENTRY_1]    {  600.0,    0.0,    0.0,  270.0 },
    [mac_02_ENTRY_2]    {    0.0,    0.0, -600.0,  180.0 },
    [mac_02_ENTRY_3]    {    0.0,    0.0,  600.0,    0.0 },
    [mac_02_ENTRY_4]    { -450.0,   30.0,  245.0,   90.0 },
    [mac_02_ENTRY_5]    { -460.0,   50.0, -270.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mac_02 },
};
