#include "kkj_13.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_13 },
    .songVariation = 1,
    .sfxReverb = 3,
};
