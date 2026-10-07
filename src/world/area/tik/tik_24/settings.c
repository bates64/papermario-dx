#include "tik_24.h"

export s32 map_init(void) {
    use_map_geometry("tik_18");
    return false;
}

EntryList Entrances = {
    [tik_24_ENTRY_0]    { -220.0,  -10.0,    0.0,   90.0 },
    [tik_24_ENTRY_1]    {  320.0,  -10.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_tik_24 },
    .songVariation = 1,
    .sfxReverb = 2,
};
