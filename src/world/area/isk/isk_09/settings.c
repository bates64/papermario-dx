#include "isk_09.h"

EntryList Entrances = {
    [isk_09_ENTRY_0]    { -575.0, -390.0,   81.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
