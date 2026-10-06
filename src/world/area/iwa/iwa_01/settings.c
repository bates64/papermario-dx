#include "iwa_01.h"

EntryList Entrances = {
    [iwa_01_ENTRY_0]    { -786.0,   63.0,  323.0,   90.0 },
    [iwa_01_ENTRY_1]    { -770.0,  163.0,   45.0,   90.0 },
    [iwa_01_ENTRY_2]    {  958.0,  170.0,  173.0,  270.0 },
    [iwa_01_ENTRY_3]    {  989.0,  370.0,  235.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_01 },
};
