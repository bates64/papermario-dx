#include "nok_14.h"

EntryList Entrances = {
    [nok_14_ENTRY_0]    { -855.0,   75.0,  -35.0,   90.0 },
    [nok_14_ENTRY_1]    {  436.0,    0.0,  -49.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_14 },
};
