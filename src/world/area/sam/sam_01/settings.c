#include "sam_01.h"

EntryList Entrances = {
    [sam_01_ENTRY_0]    {  480.0,    0.0,    0.0,  270.0 },
    [sam_01_ENTRY_1]    { -305.0,    0.0, -180.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_01 },
};
