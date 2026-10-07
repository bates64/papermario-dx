#include "nok_01.h"

EntryList Entrances = {
    [nok_01_ENTRY_0]    { -333.0,    0.0,  350.0,   45.0 },
    [nok_01_ENTRY_1]    {  470.0,    0.0,   10.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_01 },
};
