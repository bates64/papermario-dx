#include "hos_10.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList Entrances = {
    [hos_10_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_10_ENTRY_1]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_10_ENTRY_2]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_10_ENTRY_3]    {    0.0, -1000.0,    0.0,   90.0 },
    [hos_10_ENTRY_4]    {    0.0, -1000.0,    0.0,   90.0 },
    [hos_10_ENTRY_5]    {    0.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
