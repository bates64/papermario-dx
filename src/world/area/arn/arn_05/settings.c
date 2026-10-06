
#include "arn_05.h"

EntryList Entrances = {
    [arn_05_ENTRY_0]    {  -77.0,  135.0,  150.0,   90.0 },
    [arn_05_ENTRY_1]    {  577.0,  200.0,  150.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_05 },
};
