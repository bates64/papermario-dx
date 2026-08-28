#pragma once

#include "common.h"

#define BATTLE_MENU_EXPORT_NAME "gBattleMenu"

typedef void (*BattleMenuCallback)(s32 state);

typedef struct BattleMenuInterface {
    /* 0x00 */ BattleMenuCallback update;
    /* 0x04 */ BattleMenuCallback draw;
} BattleMenuInterface; // size = 0x08

#define BATTLE_MENU_INTERFACE(updateFunc, drawFunc) \
    export const BattleMenuInterface gBattleMenu = { \
        .update = (updateFunc), \
        .draw = (drawFunc), \
    }

extern const BattleMenuInterface gBattleMenu;

void load_battle_menu(void);
void unload_battle_menu(void);
void update_battle_menu(s32 state);
void draw_battle_menu(s32 state);
