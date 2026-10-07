#include "iwa_04.h"

EntryList Entrances = {
    [iwa_04_ENTRY_0]    { -630.0,    0.0,  -49.0,   90.0 },
    [iwa_04_ENTRY_1]    {  770.0, -250.0,  -40.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_04 },
};
