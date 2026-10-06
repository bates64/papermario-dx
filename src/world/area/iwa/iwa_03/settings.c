#include "iwa_03.h"

EntryList Entrances = {
    [iwa_03_ENTRY_0]    {   14.0,  -18.0,    7.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_03 },
};
