#include "dro_02.h"

EntryList Entrances = {
    [dro_02_ENTRY_0]    { -473.0,    0.0,   12.0,   90.0 },
    [dro_02_ENTRY_1]    {  415.0,   35.0,  -15.0,  180.0 },
    [dro_02_ENTRY_2]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_02_ENTRY_3]    {    0.0,    0.0,    0.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_dro_02 },
};
