#include "pra_39.h"

EntryList Entrances = {
    [pra_39_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_39_ENTRY_1]    {  487.0,    0.0,   70.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_39 },
    .songVariation = 1,
    .sfxReverb = 2,
};
