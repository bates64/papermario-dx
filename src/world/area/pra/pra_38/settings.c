#include "pra_38.h"

EntryList Entrances = {
    [pra_38_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_38_ENTRY_1]    {  487.0,    0.0,   70.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_38 },
    .songVariation = 1,
    .sfxReverb = 2,
};
