#pragma once

#include "common.h"

enum GameMode {
    GAME_MODE_STARTUP,
    GAME_MODE_LOGOS,
    GAME_MODE_TITLE_SCREEN,
    GAME_MODE_ENTER_DEMO_WORLD,
    GAME_MODE_ENTER_WORLD,
    GAME_MODE_WORLD,
    GAME_MODE_CHANGE_MAP,
    GAME_MODE_GAME_OVER,
    GAME_MODE_BATTLE,
    GAME_MODE_END_BATTLE,
    GAME_MODE_PAUSE,
    GAME_MODE_UNPAUSE,
    GAME_MODE_FILE_SELECT,
    GAME_MODE_END_FILE_SELECT,
    GAME_MODE_INTRO,
    GAME_MODE_DEMO,
};

void set_game_mode(s32 mode);
s32 get_game_mode(void);
void set_game_mode_render_frontUI(void (*fn)(void));

void clear_game_mode(void);
void step_game_mode(void);
void render_game_mode_backUI(void);
void render_game_mode_frontUI(void);
