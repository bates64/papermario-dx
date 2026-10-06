#include "kmr_09.h"

EntryList Entrances = {
    [kmr_09_ENTRY_0]    { -127.0,    0.0,   24.0,   90.0 },
    [kmr_09_ENTRY_1]    {  840.0,    0.0,   24.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_09 },
};
