#include "tik_24.h"

export s32 map_init(void) {
    use_map_geometry("tik_18");
    return false;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_tik_24 },
    .songVariation = 1,
    .sfxReverb = 2,
};
