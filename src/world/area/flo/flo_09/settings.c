#include "flo_09.h"

EntryList Entrances = {
    [flo_09_ENTRY_0]    { -520.0,    0.0,    0.0,   90.0 },
    [flo_09_ENTRY_1]    {  520.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_09 },
};
