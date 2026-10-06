#include "arn_07.h"

EntryList Entrances = {
    [arn_07_ENTRY_0]    {    0.0,   20.0, -147.0,  180.0 },
    [arn_07_ENTRY_1]    {  485.0,    0.0,    0.0,  270.0 },
    [arn_07_ENTRY_2]    { -488.0,    0.0,    0.0,   90.0 },
    [arn_07_ENTRY_3]    {  194.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_07 },
};
