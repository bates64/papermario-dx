#include "dgb_00.h"

EntryList Entrances = {
    [dgb_00_ENTRY_0]    { -733.0,    0.0,   -8.0,   90.0 },
    [dgb_00_ENTRY_1]    {  250.0,   10.0, -100.0,  225.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_dgb_00 },
};
