#include "mgm_00.h"

EntryList Entrances = {
    [mgm_00_ENTRY_0]    { -152.0,    0.0, -218.0,   90.0 },
    [mgm_00_ENTRY_1]    {  -25.0,   30.0, -168.0,   90.0 },
    [mgm_00_ENTRY_2]    {   95.0,   30.0, -168.0,   90.0 },
    [mgm_00_ENTRY_3]    {  237.0,    0.0,  -53.0,  270.0 },
    [mgm_00_ENTRY_4]    {   20.0,    0.0,  -80.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_mgm_00 },
};
