#include "pra_06.h"

EntryList Entrances = {
    [pra_06_ENTRY_0]    {   13.0,    0.0,   75.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_06 },
    .songVariation = 1,
    .sfxReverb = 1,
};
