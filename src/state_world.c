#include "functions.h"
#include "npc.h"
#include "game_modes.h"
#include "dx/config.h"
#include "dx/debug_menu.h"

void state_world_draw_aux_ui(void);

void state_init_world(void) {
    set_game_mode_render_frontUI(state_world_draw_aux_ui);

#ifdef DX_QUICK_LAUNCH_BATTLE
    if (gGameStatus.loadType == LOAD_FROM_FILE_SELECT) {
        dx_debug_begin_battle_with_IDs(DX_QUICK_LAUNCH_BATTLE);
    }
#endif
}

void state_step_world(void) {
    update_encounters();
    update_npcs();
    update_player();
    update_item_entities();
    update_effects();
    update_cameras();
}

void state_drawUI_world(void) {
    draw_status_ui();
    draw_encounter_ui();
    imgfx_update_cache();
}

void state_world_draw_aux_ui(void) {
    draw_first_strike_ui();
}
