#include "tik_24.h"

export s32 map_init(void) {
    sprintf(wMapShapeName, "tik_18_shape");
    sprintf(wMapHitName, "tik_18_hit");
    return false;
}

EntryList Entrances = {
    [tik_24_ENTRY_0]    { -220.0,  -10.0,    0.0,   90.0 },
    [tik_24_ENTRY_1]    {  320.0,  -10.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_24 },
    .songVariation = 1,
    .sfxReverb = 2,
};
