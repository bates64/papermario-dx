#include "flo_10.h"

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH6_FILLED_SPRING_WITH_WATER) {
        return MSG_MapTattle_flo_10_before;
    } else {
        return MSG_MapTattle_flo_10_after;
    }
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "fla_bg",
    .tattle = { .get = &get_tattle },
};
