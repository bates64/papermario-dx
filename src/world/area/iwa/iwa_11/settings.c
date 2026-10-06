#include "iwa_11.h"

EntryList Entrances = {
    [iwa_11_ENTRY_0]    {    0.0,    0.0,   15.0,   90.0 },
    [iwa_11_ENTRY_1]    {    0.0,    0.0,   15.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
#if VERSION_JP
    .tattle = { MSG_MapTattle_018C }
#endif
};
