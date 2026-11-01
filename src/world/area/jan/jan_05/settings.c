#include "jan_05.h"

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH5_SUSHIE_JOINED_PARTY) {
        return MSG_MapTattle_jan_05_before;
    } else {
        return MSG_MapTattle_jan_05_after;
    }
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yos_bg",
    .tattle = { .get = &get_tattle },
};
