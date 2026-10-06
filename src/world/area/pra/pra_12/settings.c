#include "pra_12.h"

EntryList Entrances = {
    [pra_12_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_12 },
    .songVariation = 1,
    .sfxReverb = 1,
};
