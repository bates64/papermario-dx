#include "osr_02.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList Entrances = {
    [osr_02_ENTRY_0]    { -205.0,    0.0,   55.0,  135.0 },
    [osr_02_ENTRY_1]    {    0.0,   20.0, -290.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_osr_02 },
};
