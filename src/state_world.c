#include "functions.h"
#include "npc.h"
#include "game_modes.h"
#include "dx/profiling.h"

void state_world_draw_aux_ui(void);

void state_init_world(void) {
    game_mode_set_fpDrawAuxUI(0, state_world_draw_aux_ui);
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
    iterate_models(); // no-op
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
