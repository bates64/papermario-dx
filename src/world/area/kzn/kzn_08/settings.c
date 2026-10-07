#include "kzn_08.h"
#include "model.h"

EntryList Entrances = {
    [kzn_08_ENTRY_0]    { -315.0,    0.0,   85.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
