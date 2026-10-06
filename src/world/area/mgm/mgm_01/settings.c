#include "mgm_01.h"

EntryList Entrances = {
    [mgm_01_ENTRY_0]    {    0.0,  200.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_mgm_01 },
};
