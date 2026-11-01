#include "sam_11.h"

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH7_SHATTERED_FROZEN_POND) {
        return MSG_MapTattle_sam_11_before;
    } else {
        return MSG_MapTattle_sam_11_after;
    }
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yki_bg",
    .tattle = { .get = &get_tattle },
};
