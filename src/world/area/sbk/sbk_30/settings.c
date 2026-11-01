#include "sbk_30.h"

s32 get_tattle(void) {
    s32 tattle;
    if (evt_get_variable(nullptr, GB_StoryProgress) > STORY_CH2_STAR_SPIRIT_DEPARTED) {
        tattle = MSG_MapTattle_sbk_30_after;
    } else {
        tattle = MSG_MapTattle_sbk_30_before;
    }
    return tattle;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { .get = &get_tattle },
};
