#include "kkj_20.h"

EntryList Entrances = {
    [kkj_20_ENTRY_0]    { -185.0,    0.0,  -25.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_20 },
};
