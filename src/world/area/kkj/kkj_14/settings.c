#include "kkj_14.h"

export s32 map_init(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) == STORY_INTRO) {
        sprintf(wMapBgName, "nok_bg");
    }
    return false;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_14 },
};
