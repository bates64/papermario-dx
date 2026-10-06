#include "kmr_06.h"

EntryList Entrances = {
    [kmr_06_ENTRY_0]    { -110.0,    0.0,   33.0,   90.0 },
    [kmr_06_ENTRY_1]    {  850.0,    0.0,   35.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_06 },
};
