#include "nok_03.h"

EntryList Entrances = {
    [nok_03_ENTRY_0]    { -654.0,    0.0,    6.0,   90.0 },
    [nok_03_ENTRY_1]    { 1046.0,    0.0,  -31.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_03 },
};
