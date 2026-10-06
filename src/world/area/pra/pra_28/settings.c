#include "pra_28.h"

EntryList Entrances = {
    [pra_28_ENTRY_0]    {   23.0,    0.0,   70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_28 },
    .songVariation = 1,
    .sfxReverb = 1,
};
