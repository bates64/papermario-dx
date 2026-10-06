#include "sam_04.h"

EntryList Entrances = {
    [sam_04_ENTRY_0]    { -330.0,    0.0,  340.0,   45.0 },
    [sam_04_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sam_04_ENTRY_2]    {    0.0,    0.0, -250.0,  180.0 },
    [sam_04_ENTRY_3]    { -360.0,   80.0,  -80.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_04 },
};
