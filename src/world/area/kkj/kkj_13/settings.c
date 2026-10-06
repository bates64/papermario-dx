#include "kkj_13.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList Entrances = {
    [kkj_13_ENTRY_0]    {  -95.0,    0.0,    0.0,   90.0 },
    [kkj_13_ENTRY_1]    { 1295.0,    0.0,    0.0,  270.0 },
    [kkj_13_ENTRY_2]    {  630.0,    0.0,    0.0,   90.0 },
    [kkj_13_ENTRY_3]    {    0.0,    0.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_13 },
    .songVariation = 1,
    .sfxReverb = 3,
};
