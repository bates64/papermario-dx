#include "jan_04.h"

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH5_SUSHIE_JOINED_PARTY) {
        return MSG_MapTattle_jan_04_before;
    } else {
        return MSG_MapTattle_jan_04_after;
    }
}
