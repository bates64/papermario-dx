#include "kmr_12.h"

EntryList Entrances = {
    [kmr_12_ENTRY_0]    { -126.0,    0.0,   12.0,   90.0 },
    [kmr_12_ENTRY_1]    {  471.0,    0.0,   12.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_12 },
};
