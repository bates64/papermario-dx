#include "osr_03.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList Entrances = {
    [osr_03_ENTRY_0]    {    0.0,    0.0,  604.0,    0.0 },
    [osr_03_ENTRY_1]    {    0.0,    0.0,    0.0,  270.0 },
    [osr_03_ENTRY_2]    {    0.0,    0.0,  290.0,  180.0 },
    [osr_03_ENTRY_3]    {    0.0,  -50.0,    0.0,  180.0 },
    [osr_03_ENTRY_4]    {    0.0,    0.0,    0.0,  180.0 },
    [osr_03_ENTRY_5]    {    0.0,  -50.0,    0.0,  180.0 },
    [osr_03_ENTRY_6]    {    0.0,    0.0, -290.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
};
