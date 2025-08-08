#include "functions.h"
#include "npc.h"
#include "game_modes.h"
#include "dx/config.h"
#include "dx/profiling.h"

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
    profiler_update(PROFILE_TIME_WORLD_ENCOUNTERS, 0);
    update_npcs();
    profiler_update(PROFILE_TIME_WORLD_NPCS, 0);
    update_player();
    profiler_update(PROFILE_TIME_WORLD_PLAYER, 0);
    update_item_entities();
    profiler_update(PROFILE_TIME_WORLD_ITEM_ENTITIES, 0);
    update_effects();
    profiler_update(PROFILE_TIME_WORLD_EFFECTS, 0);
    update_cameras();
    profiler_update(PROFILE_TIME_WORLD_CAMERAS, 0);
}

void state_drawUI_world(void) {
    draw_status_ui();
    draw_encounter_ui();
    imgfx_update_cache();
}

void state_world_draw_aux_ui(void) {
    draw_first_strike_ui();
}
