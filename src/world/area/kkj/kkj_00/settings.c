#include "kkj_00.h"

export s32 map_init(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) >= STORY_EPILOGUE) {
        gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    }
    return false;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .songVariation = 1,
    .sfxReverb = 3,
};
