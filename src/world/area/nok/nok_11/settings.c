#include "nok_11.h"

EntryList Entrances = {
    [nok_11_ENTRY_0]    { -758.0,    0.0,  -49.0,   90.0 },
    [nok_11_ENTRY_1]    {  886.0,    0.0,  -40.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_11 },
};
