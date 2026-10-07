#include "kmr_11.h"

EntryList Entrances = {
    [kmr_11_ENTRY_0]    { -925.0,    0.0,  -53.0,   90.0 },
    [kmr_11_ENTRY_1]    {  770.0,    0.0, -525.0,  225.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_11 },
};
