#include "sam_12.h"

EntryList Entrances = {
    [sam_12_ENTRY_0]    { -372.0,   15.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_sam_12 },
    .songVariation = 1,
    .sfxReverb = 1,
};
