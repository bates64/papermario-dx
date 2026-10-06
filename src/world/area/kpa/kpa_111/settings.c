#include "kpa_111.h"

EntryList Entrances = {
    [kpa_111_ENTRY_0]   { -208.0,    0.0,  105.0,   90.0 },
    [kpa_111_ENTRY_1]   {  300.0,    0.0,   25.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_111 },
    .songVariation = 1,
    .sfxReverb = 3,
};
