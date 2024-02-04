#include "game_modes.h"

GameMode GameModeStartup = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_startup,
    .step = state_step_startup,
    .render = state_drawUI_startup,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeLogos = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_logos,
    .step = state_step_logos,
    .render = state_drawUI_logos,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeTitleScreen = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_title_screen,
    .step = state_step_title_screen,
    .render = state_drawUI_title_screen,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeEnterDemoWorld = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_enter_demo,
    .step = state_step_enter_world,
    .render = state_drawUI_enter_world,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeChangeMap = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_change_map,
    .step = state_step_change_map,
    .render = state_drawUI_change_map,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeGameOver = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_game_over,
    .step = state_step_game_over,
    .render = state_drawUI_game_over,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeEnterWorld = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_enter_world,
    .step = state_step_enter_world,
    .render = state_drawUI_enter_world,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeWorld = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_world,
    .step = state_step_world,
    .render = state_drawUI_world,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeBattle = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_battle,
    .step = state_step_battle,
    .render = state_drawUI_battle,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeEndBattle = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_end_battle,
    .step = state_step_end_battle,
    .render = state_drawUI_end_battle,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModePause = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_pause,
    .step = state_step_pause,
    .render = state_drawUI_pause,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeUnpause = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_unpause,
    .step = state_step_unpause,
    .render = state_drawUI_unpause,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeLanguageSelect = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_language_select,
    .step = state_step_language_select,
    .render = state_drawUI_language_select,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeEndLanguageSelect = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_exit_language_select,
    .step = state_step_exit_language_select,
    .render = state_drawUI_exit_language_select,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeFileSelect = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_file_select,
    .step = state_step_file_select,
    .render = state_drawUI_file_select,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeEndFileSelect = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_exit_file_select,
    .step = state_step_exit_file_select,
    .render = state_drawUI_exit_file_select,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeIntro = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_intro,
    .step = state_step_intro,
    .render = state_drawUI_intro,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode GameModeDemo = {
    .flags = MODE_FLAG_NONE,
    .init = state_init_demo,
    .step = state_step_demo,
    .render = state_drawUI_demo,
    .renderAux = NULL,
    .unusedFunc = NULL,
};

GameMode* GameModeMap[] = {
    [GAME_MODE_STARTUP]             (GameMode*) &GameModeStartup,
    [GAME_MODE_LOGOS]               (GameMode*) &GameModeLogos,
    [GAME_MODE_TITLE_SCREEN]        (GameMode*) &GameModeTitleScreen,
    [GAME_MODE_ENTER_DEMO_WORLD]    (GameMode*) &GameModeEnterDemoWorld,
    [GAME_MODE_WORLD]               (GameMode*) &GameModeWorld,
    [GAME_MODE_CHANGE_MAP]          (GameMode*) &GameModeChangeMap,
    [GAME_MODE_GAME_OVER]           (GameMode*) &GameModeGameOver,
    [GAME_MODE_ENTER_WORLD]         (GameMode*) &GameModeEnterWorld,
    [GAME_MODE_BATTLE]              (GameMode*) &GameModeBattle,
    [GAME_MODE_END_BATTLE]          (GameMode*) &GameModeEndBattle,
    [GAME_MODE_PAUSE]               (GameMode*) &GameModePause,
    [GAME_MODE_UNPAUSE]             (GameMode*) &GameModeUnpause,
    [GAME_MODE_LANGUAGE_SELECT]     (GameMode*) &GameModeLanguageSelect,
    [GAME_MODE_END_LANGUAGE_SELECT] (GameMode*) &GameModeEndLanguageSelect,
    [GAME_MODE_FILE_SELECT]         (GameMode*) &GameModeFileSelect,
    [GAME_MODE_END_FILE_SELECT]     (GameMode*) &GameModeEndFileSelect,
    [GAME_MODE_INTRO]               (GameMode*) &GameModeIntro,
    [GAME_MODE_DEMO]                (GameMode*) &GameModeDemo,
};

SHIFT_BSS s16 CurGameMode;

void set_game_mode(s16 mode) {
    CurGameMode = mode;
    set_game_mode_slot(0, GameModeMap[mode]);
}

s16 get_game_mode(void) {
    return CurGameMode;
}
