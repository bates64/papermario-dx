#include "arn_11.h"

EntryList Entrances = {
    [arn_11_ENTRY_0]    { -165.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_arn_11 },
    .songVariation = 1,
    .sfxReverb = 1,
};
