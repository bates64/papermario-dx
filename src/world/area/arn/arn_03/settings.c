#include "arn_03.h"

EntryList Entrances = {
    [arn_03_ENTRY_0]    {  -76.0,  165.0,  150.0,   90.0 },
    [arn_03_ENTRY_1]    {  576.0,  225.0,  150.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_03 },
};
