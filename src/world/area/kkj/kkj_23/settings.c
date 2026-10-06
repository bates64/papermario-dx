#include "kkj_23.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    return false;
}

EntryList Entrances = {
    [kkj_23_ENTRY_0]    {  735.0,    0.0,  -60.0,  270.0 },
    [kkj_23_ENTRY_1]    {   10.0,    0.0,  -60.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_23 },
};
