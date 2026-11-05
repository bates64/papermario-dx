#include "sbk_02.h"

s32 get_tattle(void) {
    s32 tattle;
    if (evt_get_variable(nullptr, GB_StoryProgress) > STORY_CH2_GOT_PULSE_STONE) {
        tattle = MSG_MapTattle_sbk_02_after;
    } else {
        tattle = MSG_MapTattle_sbk_02_before;
    }
    return tattle;
}
