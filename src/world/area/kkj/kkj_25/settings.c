#include "kkj_25.h"

export s32 N(map_init)(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList N(Entrances) = {
    [kkj_25_ENTRY_0]    { -605.0,    0.0,    0.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_25 },
};
