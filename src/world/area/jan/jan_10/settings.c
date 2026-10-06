#include "jan_10.h"

EntryList Entrances = {
    [jan_10_ENTRY_0]    {  380.0,  -20.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_10 },
};
