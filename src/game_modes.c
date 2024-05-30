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
    /* 0x0C */ void (*renderBackUI)(void);
    /* 0x10 */ void (*renderFrontUI)(void); ///< @see render_game_mode_frontUI
} GameModeData; // size = 0x14

const GameModeData GameModeTemplates[] = {
    [GAME_MODE_STARTUP] {
        .init = state_init_startup,
        .step = state_step_startup,
        .renderBackUI = state_drawUI_startup,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_LOGOS] {
        .init = state_init_logos,
        .step = state_step_logos,
        .renderBackUI = state_drawUI_logos,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_TITLE_SCREEN] {
        .init = state_init_title_screen,
        .step = state_step_title_screen,
        .renderBackUI = state_drawUI_title_screen,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_ENTER_DEMO_WORLD] {
        .init = state_init_enter_demo,
        .step = state_step_enter_world,
        .renderBackUI = state_drawUI_enter_world,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_ENTER_WORLD] {
        .init = state_init_enter_world,
        .step = state_step_enter_world,
        .renderBackUI = state_drawUI_enter_world,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_WORLD] {
        .init = state_init_world,
        .step = state_step_world,
        .renderBackUI = state_drawUI_world,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_CHANGE_MAP] {
        .init = state_init_change_map,
        .step = state_step_change_map,
        .renderBackUI = state_drawUI_change_map,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_GAME_OVER] {
        .init = state_init_game_over,
        .step = state_step_game_over,
        .renderBackUI = state_drawUI_game_over,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_BATTLE] {
        .init = state_init_battle,
        .step = state_step_battle,
        .renderBackUI = state_drawUI_battle,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_END_BATTLE] {
        .init = state_init_end_battle,
        .step = state_step_end_battle,
        .renderBackUI = state_drawUI_end_battle,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_PAUSE] {
        .init = state_init_pause,
        .step = state_step_pause,
        .renderBackUI = state_drawUI_pause,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_UNPAUSE] {
        .init = state_init_unpause,
        .step = state_step_unpause,
        .renderBackUI = state_drawUI_unpause,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_FILE_SELECT] {
        .init = state_init_file_select,
        .step = state_step_file_select,
        .renderBackUI = state_drawUI_file_select,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_END_FILE_SELECT] {
        .init = state_init_exit_file_select,
        .step = state_step_exit_file_select,
        .renderBackUI = state_drawUI_exit_file_select,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_INTRO] {
        .init = state_init_intro,
        .step = state_step_intro,
        .renderBackUI = state_drawUI_intro,
        .renderFrontUI = NULL,
    },
    [GAME_MODE_DEMO] {
        .init = state_init_demo,
        .step = state_step_demo,
        .renderBackUI = state_drawUI_demo,
        .renderFrontUI = NULL,
    },
};

BSS s32 CurGameModeID;
BSS GameModeData CurGameMode;

void game_mode_nop(void) {
}

s32 get_game_mode(void) {
    return CurGameModeID;
}

void set_game_mode(s32 modeID) {
    GameModeData* template = &GameModeTemplates[modeID];
    CurGameModeID = modeID;

    CurGameMode.flags = MODE_FLAG_INITIALIZED | MODE_FLAG_NEEDS_STEP;
    CurGameMode.init = template->init;
    CurGameMode.step = template->step;
    CurGameMode.renderBackUI = template->renderBackUI;

    if (CurGameMode.init == NULL) {
        CurGameMode.init = game_mode_nop;
    }
    if (CurGameMode.step == NULL) {
        CurGameMode.step = game_mode_nop;
    }
    if (CurGameMode.renderBackUI == NULL) {
        CurGameMode.renderBackUI = game_mode_nop;
    }

    CurGameMode.renderFrontUI = game_mode_nop;
    CurGameMode.init();
}

void init_game_mode(void) {
    CurGameMode.flags = MODE_FLAG_NONE;
}

void set_game_mode_render_frontUI(void (*fn)(void)) {
    CurGameMode.renderFrontUI = fn;
    CurGameMode.flags |= MODE_FLAG_HAS_FRONT_UI;

    if (fn == NULL) {
        CurGameMode.renderFrontUI = game_mode_nop;
    }
}

void step_game_mode(void) {
    if (CurGameMode.flags == MODE_FLAG_NONE) {
        return;
    }

    CurGameMode.flags &= ~MODE_FLAG_NEEDS_STEP;
    CurGameMode.step();
}

void render_game_mode_backUI(void) {
    if (CurGameMode.flags == MODE_FLAG_NONE) {
        return;
    }

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
