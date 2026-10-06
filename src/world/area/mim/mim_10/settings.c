#include "mim_10.h"

EntryList Entrances = {
    [mim_10_ENTRY_0]    { -385.0,   20.0,   10.0,   90.0 },
    [mim_10_ENTRY_1]    {  385.0,    0.0,   10.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mim_10 },
};
