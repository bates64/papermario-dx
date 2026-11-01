#include "kzn_18.h"

extern EvtScript(EVS_Main);

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH5_STAR_SPIRIT_DEPARTED) {
        return MSG_MapTattle_kzn_18_before;
    } else {
        return MSG_MapTattle_kzn_18_after;
    }
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { .get = get_tattle },
    .songVariation = 1,
    .sfxReverb = 2,
};
