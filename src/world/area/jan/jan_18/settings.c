#include "jan_18.h"

EntryList Entrances = {
    [jan_18_ENTRY_0]    {   25.0,  180.0,  205.0,  172.0 },
    [jan_18_ENTRY_1]    {   20.0,  345.0, -210.0,    6.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_18 },
};
