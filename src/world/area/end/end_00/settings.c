#include "end_00.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_MARIO_PARADE;
    return false;
}

EntryList Entrances = {
    [end_00_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
