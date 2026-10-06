#include "mac_00.h"

EntryList Entrances = {
    [mac_00_ENTRY_0]    { -387.0,    0.0, -460.0,  125.0 },
    [mac_00_ENTRY_1]    {  600.0,    0.0,    0.0,  270.0 },
    [mac_00_ENTRY_2]    { -435.0,  147.0, -441.0,  125.0 },
    [mac_00_ENTRY_3]    {    0.0,   50.0,  300.0,  180.0 },
    [mac_00_ENTRY_4]    { -100.0,   30.0, -370.0,  180.0 },
    [mac_00_ENTRY_5]    { -100.0,   30.0, -370.0,  135.0 },
    [mac_00_ENTRY_6]    { -100.0,   30.0, -370.0,  135.0 },
    [mac_00_ENTRY_7]    { -100.0,   30.0, -370.0,  135.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mac_00 },
};
