#include "kkj_21.h"

EntryList Entrances = {
    [kkj_21_ENTRY_0]    {  325.0,    0.0,  -30.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kkj_21 },
    .sfxReverb = 1,
};
