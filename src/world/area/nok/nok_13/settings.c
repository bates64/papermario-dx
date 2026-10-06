#include "nok_13.h"

EntryList Entrances = {
    [nok_13_ENTRY_0]    { -488.0,  150.0,    0.0,   90.0 },
    [nok_13_ENTRY_1]    {  165.0,    0.0, -483.0,  180.0 },
    [nok_13_ENTRY_2]    {  277.0,  150.0,  210.0,  315.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_13 },
};
