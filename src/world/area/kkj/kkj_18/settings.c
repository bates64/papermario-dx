#include "kkj_18.h"

EntryList Entrances = {
    [kkj_18_ENTRY_0]    { -187.0,    0.0,  -35.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_18 },
};
