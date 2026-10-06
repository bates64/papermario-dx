#include "isk_08.h"

EntryList Entrances = {
    [isk_08_ENTRY_0]    { -510.0, -390.0,  207.0,  150.0 },
    [isk_08_ENTRY_1]    { -557.0, -520.0,  224.0,  150.0 },
    [isk_08_ENTRY_2]    { -401.0, -390.0,  447.0,  320.0 },
    [isk_08_ENTRY_3]    { -401.0, -520.0,  447.0,  320.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_isk_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
