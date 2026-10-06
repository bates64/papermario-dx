#include "arn_02.h"

EntryList Entrances = {
    [arn_02_ENTRY_0]    { -585.0,   60.0,  150.0,   90.0 },
    [arn_02_ENTRY_1]    {  880.0,  320.0,  150.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_02 },
};
