#include "flo_13.h"

EntryList Entrances = {
    [flo_13_ENTRY_0]    {  570.0,    0.0,    0.0,  270.0 },
    [flo_13_ENTRY_1]    { -570.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_13 },
};
