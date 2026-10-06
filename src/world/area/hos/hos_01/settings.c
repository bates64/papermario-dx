#include "hos_01.h"

EntryList Entrances = {
    [hos_01_ENTRY_0]    { -400.0,    0.0,  410.0,   45.0 },
    [hos_01_ENTRY_1]    {   22.0,  285.0, -190.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_01 },
};
