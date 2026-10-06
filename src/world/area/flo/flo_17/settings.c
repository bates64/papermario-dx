#include "flo_17.h"

EntryList Entrances = {
    [flo_17_ENTRY_0]    { -730.0,    0.0,    0.0,   90.0 },
    [flo_17_ENTRY_1]    {  730.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_17 },
};
