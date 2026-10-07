#include "sam_03.h"

EntryList Entrances = {
    [sam_03_ENTRY_0]    { -730.0,    0.0,    0.0,   90.0 },
    [sam_03_ENTRY_1]    {  730.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_03 },
};
