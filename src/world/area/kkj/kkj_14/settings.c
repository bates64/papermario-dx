#include "kkj_14.h"

export s32 map_init(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) == STORY_INTRO) {
        sprintf(wMapBgName, "nok_bg");
    }
    return false;
}
