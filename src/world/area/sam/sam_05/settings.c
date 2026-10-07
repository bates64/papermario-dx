#include "sam_05.h"

EntryList Entrances = {
    [sam_05_ENTRY_0]    { -730.0,    0.0,  -45.0,   90.0 },
    [sam_05_ENTRY_1]    {  735.0,   95.0,  -50.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sam_bg",
    .tattle = { MSG_MapTattle_sam_05 },
};
