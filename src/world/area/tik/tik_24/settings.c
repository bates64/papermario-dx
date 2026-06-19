#include "tik_24.h"

export s32 N(map_init)(void) {
    sprintf(wMapShapeName, "tik_18_shape");
    sprintf(wMapHitName, "tik_18_hit");
    return false;
}

EntryList N(Entrances) = {
    [tik_24_ENTRY_0]    { -220.0,  -10.0,    0.0,   90.0 },
    [tik_24_ENTRY_1]    {  320.0,  -10.0,    0.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .tattle = { MSG_MapTattle_tik_24 },
    .songVariation = 1,
    .sfxReverb = 2,
};
