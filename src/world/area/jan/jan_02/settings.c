#include "jan_02.h"

EntryList Entrances = {
    [jan_02_ENTRY_0]    { -450.0,    0.0, -450.0,  135.0 },
    [jan_02_ENTRY_1]    {  640.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_02 },
};
