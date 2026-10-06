#include "kkj_19.h"

EntryList Entrances = {
    [kkj_19_ENTRY_0]    {  485.0,    0.0,   25.0,  330.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_19 },
};
