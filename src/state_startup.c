#include "common.h"
#include "hud_element.h"
#include "fio.h"
#include "sprite.h"
#include "game_modes.h"
#include "dx/config.h"
#include "dx/versioning.h"
#include "dx/boot.h"

/// What to boot into when SaveGlobals::bootTo leaves it to dx/config.h.
s32 startup_default_boot_to(void) {
    #if !DX_SKIP_LOGOS
        return BOOT_TO_LOGOS;
    #elif DX_SKIP_STORY
        return BOOT_TO_TITLE;
    #else
        return BOOT_TO_INTRO;
    #endif
}

void startup_boot_to(s32 bootTo) {
    if (bootTo == BOOT_TO_DEFAULT) {
        bootTo = startup_default_boot_to();
    }

    switch (bootTo) {
        case BOOT_TO_RECORD:
            if (dx_boot_from_record()) {
                set_game_mode(GAME_MODE_ENTER_WORLD);
                gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD;
                return;
            }
            startup_boot_to(startup_default_boot_to());
            return;
        case BOOT_TO_INTRO:
            set_curtain_scale(1.0f);
            set_curtain_fade(0.3f);
            gGameStatus.introPart = gSaveGlobals.bootScene;
            set_game_mode(GAME_MODE_INTRO);
            return;
        case BOOT_TO_DEMO:
            gGameStatus.demoState = DEMO_STATE_ACTIVE;
            gGameStatus.nextDemoScene = gSaveGlobals.bootScene < LAST_DEMO_SCENE_IDX ? gSaveGlobals.bootScene : 0;
            set_game_mode(GAME_MODE_DEMO);
            return;
        case BOOT_TO_TITLE:
            set_curtain_scale(1.0f);
            set_curtain_fade(0.0f);
            set_game_mode(GAME_MODE_TITLE_SCREEN);
            return;
        case BOOT_TO_FILE_SELECT:
            // the map behind the file select menu, as the title screen sets it
            gGameStatus.areaID = AREA_KMR;
            gGameStatus.mapID = 0xB; //TODO hardcoded map IDs
            gGameStatus.entryID = 0;
            set_game_mode(GAME_MODE_FILE_SELECT);
            return;
        case BOOT_TO_LOGOS:
        default:
            set_game_mode(GAME_MODE_LOGOS);
            return;
    }
}

void state_init_startup(void) {
    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
    gGameStatus.startupState = 3;
}

void state_step_startup(void) {
    s32 i;

    if (gGameStatus.startupState != 0) {
        gGameStatus.startupState--;
        return;
    }

    gOverrideFlags = 0;
    gGameStatus.areaID = 0;
    gGameStatus.context = CONTEXT_WORLD;
    gGameStatus.prevArea = -1;
    gGameStatus.mapID = 0;
    gGameStatus.entryID = 0;
    gGameStatus.debugUnused1 = false;
    gGameStatus.debugScripts = DEBUG_SCRIPTS_NONE;
    gGameStatus.keepUsingPartnerOnMapChange = false;
    gGameStatus.introPart = INTRO_PART_NONE;
    gGameStatus.demoBattleFlags = 0;
    gGameStatus.unk_A9 = -1;
    gGameStatus.demoState = DEMO_STATE_NONE;

    general_heap_create();
    clear_render_tasks();
    clear_worker_list();
    clear_script_list();
    create_cameras();
    spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
    clear_entity_models();
    clear_animator_list();
    clear_model_data();
    clear_sprite_shading_data();
    reset_background_settings();
    hud_element_set_aux_cache(0, 0);
    hud_element_clear_cache();
    clear_trigger_data();
    clear_printers();
    clear_entity_data(false);
    clear_screen_overlays();
    clear_player_status();
    clear_npcs();
    clear_player_data();
    reset_battle_status();
    init_encounter_status();
    clear_effect_data();
    clear_item_entity_data();
    clear_saved_variables();
    initialize_collision();
    bgm_init_music_players();
    clear_windows();
    partner_initialize_data();
    sfx_clear_sounds();
    bgm_reset_volume();
    initialize_curtains();

    for (i = 0; i < ARRAY_COUNT(gGameStatus.holdRepeatInterval); i++) {
        gGameStatus.holdRepeatInterval[i] = 4;
        gGameStatus.holdDelayTime[i] = 15;
    }

    fio_load_globals();

    if (gSaveGlobals.useMonoSound == 0) {
        gGameStatus.soundOutputMode = SOUND_OUT_STEREO;
        snd_set_stereo();
    } else {
        gGameStatus.soundOutputMode = SOUND_OUT_MONO;
        snd_set_mono();
    }

    gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;

    startup_boot_to(gSaveGlobals.bootTo);
}

void state_drawUI_startup(void) {
    startup_draw_prim_rect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, 255);
}
