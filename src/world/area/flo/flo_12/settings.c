#include "flo_12.h"

EntryList Entrances = {
    [flo_12_ENTRY_0]    {  280.0,    0.0,    0.0,  270.0 },
    [flo_12_ENTRY_1]    {  280.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_12 },
};
