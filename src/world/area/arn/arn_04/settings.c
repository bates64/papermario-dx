#include "arn_04.h"

EntryList Entrances = {
    [arn_04_ENTRY_0]    { -585.0,   60.0,  150.0,   90.0 },
    [arn_04_ENTRY_1]    {  820.0,  285.0,  150.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_04 },
};
