#include "game_modes.h"

enum GameModeFlags {
    MODE_FLAG_NONE          = 0,
    MODE_FLAG_INITIALIZED   = (1 << 0), // Set when the mode is initialized
    MODE_FLAG_NEEDS_STEP    = (1 << 1), // Turned off after the first step is done
    MODE_FLAG_HAS_FRONT_UI  = (1 << 2), // renderFrontUI function has been assigned
};

typedef struct GameModeData {
    /* 0x00 */ u16 flags;
    /* 0x04 */ void (*init)(void);
    /* 0x08 */ void (*step)(void);
    /* 0x0C */ UNK_FUN_PTR(unusedFunc);
    /* 0x10 */ void (*render)(void);
    #ifdef AVOID_UB
    /* 0x14 */ void (*renderAux)(void); ///< @see state_render_frontUI
    #endif
} GameModeIncomplete; // size = 0x14

GameModeIncomplete GameModeStartup = {
    MODE_FLAG_NONE,
    state_init_startup,
    state_step_startup,
    nullptr,
    state_drawUI_startup,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeLogos = {
    MODE_FLAG_NONE,
    state_init_logos,
    state_step_logos,
    nullptr,
    state_drawUI_logos,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeTitleScreen = {
    MODE_FLAG_NONE,
    state_init_title_screen,
    state_step_title_screen,
    nullptr,
    state_drawUI_title_screen,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeEnterDemoWorld = {
    MODE_FLAG_NONE,
    state_init_enter_demo,
    state_step_enter_world,
    nullptr,
    state_drawUI_enter_world,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeChangeMap = {
    MODE_FLAG_NONE,
    state_init_change_map,
    state_step_change_map,
    nullptr,
    state_drawUI_change_map,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeGameOver = {
    MODE_FLAG_NONE,
    state_init_game_over,
    state_step_game_over,
    nullptr,
    state_drawUI_game_over,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeEnterWorld = {
    MODE_FLAG_NONE,
    state_init_enter_world,
    state_step_enter_world,
    nullptr,
    state_drawUI_enter_world,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeWorld = {
    MODE_FLAG_NONE,
    state_init_world,
    state_step_world,
    nullptr,
    state_drawUI_world,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeBattle = {
    MODE_FLAG_NONE,
    state_init_battle,
    state_step_battle,
    nullptr,
    state_drawUI_battle,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeEndBattle = {
    MODE_FLAG_NONE,
    state_init_end_battle,
    state_step_end_battle,
    nullptr,
    state_drawUI_end_battle,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModePause = {
    MODE_FLAG_NONE,
    state_init_pause,
    state_step_pause,
    nullptr,
    state_drawUI_pause,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeUnpause = {
    MODE_FLAG_NONE,
    state_init_unpause,
    state_step_unpause,
    nullptr,
    state_drawUI_unpause,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeLanguageSelect = {
    MODE_FLAG_NONE,
    state_init_language_select,
    state_step_language_select,
    nullptr,
    state_drawUI_language_select,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeEndLanguageSelect = {
    MODE_FLAG_NONE,
    state_init_exit_language_select,
    state_step_exit_language_select,
    nullptr,
    state_drawUI_exit_language_select,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeFileSelect = {
    MODE_FLAG_NONE,
    state_init_file_select,
    state_step_file_select,
    nullptr,
    state_drawUI_file_select,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeEndFileSelect = {
    MODE_FLAG_NONE,
    state_init_exit_file_select,
    state_step_exit_file_select,
    nullptr,
    state_drawUI_exit_file_select,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeIntro = {
    MODE_FLAG_NONE,
    state_init_intro,
    state_step_intro,
    nullptr,
    state_drawUI_intro,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

GameModeIncomplete GameModeDemo = {
    MODE_FLAG_NONE,
    state_init_demo,
    state_step_demo,
    nullptr,
    state_drawUI_demo,
    #ifdef AVOID_UB
    nullptr,
    #endif
};

    CurGameMode.renderBackUI();
}

void render_game_mode_frontUI(void) {
    if (CurGameMode.flags == MODE_FLAG_NONE) {
        return;
    }

    if (CurGameMode.flags & MODE_FLAG_NEEDS_STEP) {
        return;
    }

    if (CurGameMode.flags & MODE_FLAG_HAS_FRONT_UI) {
        CurGameMode.renderFrontUI();
    }
}
