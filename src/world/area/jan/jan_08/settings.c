#include "jan_08.h"

EntryList Entrances = {
    [jan_08_ENTRY_0]    { -330.0,    0.0,  330.0,   45.0 },
    [jan_08_ENTRY_1]    {  500.0,  -20.0,    0.0,  270.0 },
    [jan_08_ENTRY_2]    {    0.0,    0.0, -450.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_08 },
};
