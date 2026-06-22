#include "common.h"
#include "ld_addrs.h"
#include "world/disguise.h"
#include "world/surfaces.h"
#include "world/partner/watt.h"
#include "sprite/player.h"

PlayerStatus gPlayerStatus;
PlayerData gPlayerData;

extern s32 WorldTattleInteractionID;

extern DisguiseAnims BasicPeachDisguiseAnims[];

void phys_update_standard(void);
void phys_update_lava_reset(void);
void update_player_blink(void);

void check_for_ispy(void);
void check_for_pulse_stone(void);
void clear_ispy_icon(void);
void clear_pulse_stone_icon(void);
void check_for_conversation_prompt(void);
void clear_conversation_prompt(void);
void check_for_interactables(void);
void clear_interact_prompt(void);

void update_partner_timers(void);
void player_update_sprite(void);
void update_player_shadow(void);
s32 partner_use_ability(void);

// main function for player physics called from state step functions
void update_player(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;

    #if DX_DEBUG_MENU
    if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_SPEED_MODE)) {
        gPlayerStatus.walkSpeed = 6.0f;
        gPlayerStatus.runSpeed = 12.0f;
    }
    #endif

    update_partner_timers();

    if ((playerStatus->timeInAir > 100) || (playerStatus->pos.y < -2000.0f)) {
        if (!(playerStatus->animFlags & PA_FLAG_NO_OOB_RESPAWN)) {
            playerStatus->timeInAir = 0;
            playerStatus->pos.x = playerStatus->lastGoodPos.x;
            playerStatus->pos.y = playerStatus->lastGoodPos.y;
            playerStatus->pos.z = playerStatus->lastGoodPos.z;

            if (playerStatus->animFlags & PA_FLAG_RIDING_PARTNER) {
                Npc* partner;

                playerStatus->animFlags |= PA_FLAG_DISMOUNTING_ALLOWED | PA_FLAG_INTERRUPT_USE_PARTNER;
                partner = get_npc_unsafe(NPC_PARTNER);
                partner->pos.x = playerStatus->lastGoodPos.x;
                partner->pos.y = playerStatus->lastGoodPos.y + playerStatus->colliderHeight;
                partner->pos.z = playerStatus->lastGoodPos.z;
                partner->moveToPos.y = playerStatus->lastGoodPos.y;
            } else {
                playerStatus->timeInAir = 10;
            }
        }
    }

    collisionStatus->curWall = NO_COLLIDER;
    collisionStatus->lastWallHammered = NO_COLLIDER;
    collisionStatus->curInspect = NO_COLLIDER;
    collisionStatus->floorBelow = true;

    update_player_input();
    playerStatus->flags &= ~PS_FLAG_SPECIAL_LAND;
    update_player_blink();

    if (playerStatus->flags & PS_FLAG_NO_STATIC_COLLISION) {
        phys_update_action_state();
        if (!check_player_action_debug()) {
            collision_main_lateral();
        }
    } else if (playerStatus->actionState != ACTION_STATE_HIT_LAVA) {
        phys_update_standard();
    } else {
        phys_update_lava_reset();
    }

    if (playerStatus->flags & PS_FLAG_CUTSCENE_MOVEMENT) {
        playerStatus->moveFrames--;
        if (playerStatus->moveFrames <= 0) {
            playerStatus->moveFrames = 0;
            playerStatus->flags &= ~PS_FLAG_CUTSCENE_MOVEMENT;
        }
    }

    if (!(playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS)) {
        player_surface_spawn_fx();
    }

    player_update_sprite();

    gGameStatus.playerPos.x = playerStatus->pos.x;
    gGameStatus.playerPos.y = playerStatus->pos.y;
    gGameStatus.playerPos.z = playerStatus->pos.z;
    gGameStatus.playerYaw = playerStatus->curYaw;

    check_input_open_menus();
    if (!(playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS)) {
        check_input_status_bar();
    }

    update_player_shadow();

    check_for_interactables();
    check_for_conversation_prompt();
    check_for_pulse_stone();
    check_for_ispy();

    playerStatus->pushVel.x = 0.0f;
    playerStatus->pushVel.y = 0.0f;
    playerStatus->pushVel.z = 0.0f;
    playerStatus->flags &= ~PS_FLAG_SLIDING;
    playerStatus->animFlags &= ~PA_FLAG_FORCE_USE_PARTNER;
}

void check_input_use_partner(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerData* playerData = &gPlayerData;
    u32 actionState = playerStatus->actionState;

    if (!(playerStatus->animFlags & PA_FLAG_8BIT_MARIO)
        && (playerStatus->animFlags & PA_FLAG_FORCE_USE_PARTNER || playerStatus->inputDisabledCount == 0)
        && (playerStatus->pressedButtons & BUTTON_C_DOWN && !(playerStatus->flags & PS_FLAG_NO_PARTNER_USAGE))
        && !(playerStatus->pressedButtons & BUTTON_B)
        && !(playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS)
        && actionState <= ACTION_STATE_RUN
    ) {
        if (playerData->curPartner == PARTNER_GOOMBARIO) {
            WorldTattleInteractionID = playerStatus->interactingWithID;
        }
        partner_use_ability();
    }
}

void phys_update_standard(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    check_input_use_partner();
    phys_update_action_state();

    #if DX_DEBUG_MENU
        if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_FLY) && playerStatus->curButtons & BUTTON_L) {
            playerStatus->pos.y += 5.0f;
            playerStatus->flags |= PS_FLAG_JUMPING;
        }
    #endif

    if (!(playerStatus->flags & PS_FLAG_FLYING)) {
        if (playerStatus->flags & PS_FLAG_JUMPING) {
            phys_update_jump();
        }
    }

    if (playerStatus->flags & PS_FLAG_FALLING) {
        if (!(playerStatus->flags & PS_FLAG_FLYING)) {
            phys_update_falling();
        }
    }

    check_input_midair_jump();

    if (playerStatus->actionState != ACTION_STATE_SLIDING) {
        collision_main_lateral();
        collision_check_player_overlaps();

        if (collision_main_above() <= NO_COLLIDER
            && playerStatus->timeInAir == 0
            && playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS
        ) {
            collision_lateral_peach();
        }

        if (playerStatus->actionState != ACTION_STATE_ENEMY_FIRST_STRIKE
            && playerStatus->actionState != ACTION_STATE_STEP_UP
        ) {
            phys_main_collision_below();
        }
    }

    if (playerStatus->animFlags & PA_FLAG_WATT_IN_HANDS) {
        world_watt_sync_held_position();
    }

    if (!(playerStatus->flags & PS_FLAG_CAMERA_DOESNT_FOLLOW)) {
        gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
        gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
        gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;
    }
}

void phys_update_lava_reset(void) {
    phys_update_action_state();
    collision_main_lateral();
    collision_lava_reset_check_additional_overlaps();

    if (!(gPlayerStatusPtr->flags & PS_FLAG_CAMERA_DOESNT_FOLLOW)) {
        Camera* camera = &gCameras[CAM_DEFAULT];

        camera->targetPos.x = gPlayerStatusPtr->pos.x;
        camera->targetPos.y = gPlayerStatusPtr->pos.y;
        camera->targetPos.z = gPlayerStatusPtr->pos.z;
    }
}

void clear_player_status(void) {
    mem_clear(&gPlayerStatus, sizeof(gPlayerStatus));
}

void player_reset_data(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    mem_clear(playerStatus, sizeof(PlayerStatus));
    playerStatus->flags = PS_FLAG_HAS_REFLECTION;
    reset_player_status();
    playerStatus->shadowID = create_shadow_type(SHADOW_VARYING_CIRCLE,
        playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z);
    clear_world_menus();
    clear_interact_prompt();
    clear_conversation_prompt();
    clear_pulse_stone_icon();
    clear_ispy_icon();
}

b32 is_player_dismounted(void) {
    if (gPartnerStatus.partnerActionState == PARTNER_ACTION_USE &&
        (gPartnerStatus.actingPartner == PARTNER_WATT
        || gPartnerStatus.actingPartner == PARTNER_BOW
        || gPartnerStatus.actingPartner == PARTNER_SUSHIE
        || gPartnerStatus.actingPartner == PARTNER_PARAKARRY
        || gPartnerStatus.actingPartner == PARTNER_LAKILESTER)) {
        return false;
    }
    return true;
}

s32 get_overriding_player_anim(s32 anim) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (playerStatus->actionState == ACTION_STATE_USE_SPINNING_FLOWER
        && anim != ANIM_Mario1_Flail
        && anim != ANIM_Mario1_Jump
    ) {
        return -1;
    }

    if (partnerStatus->partnerActionState != PARTNER_ACTION_NONE) {
        if (partnerStatus->actingPartner == PARTNER_LAKILESTER && anim == ANIM_Mario1_Idle) {
            anim = ANIM_MarioW2_RideLaki;
        }

        if (partnerStatus->partnerActionState != PARTNER_ACTION_NONE
            && partnerStatus->actingPartner == PARTNER_BOW
            && anim != ANIM_Mario1_Crouch
            && anim != ANIM_Mario1_Idle
        ) {
            return -1;
        }
    }

    if (anim == ANIM_Mario1_ThumbsUp && partnerStatus->partnerActionState == PARTNER_ACTION_USE) {
        return -1;
    }

    if (anim == ANIM_MarioW1_Lift || anim == ANIM_Peach2_SpreadArms || anim == ANIM_Mario1_Idle) {
        if (!(playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS)) {
            if (!is_player_dismounted()) {
                return -1;
            }
        } else if (!(playerStatus->animFlags & PA_FLAG_INVISIBLE)) {
            anim = ANIM_Peach2_SpreadArms;
        } else {
            peach_set_disguise_anim(BasicPeachDisguiseAnims[playerStatus->peachDisguise].hold);
            return -1;
        }
    } else if (playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS) {
        if (playerStatus->peachItemHeld != PEACH_BAKING_NONE
            && (anim == ANIM_Peach2_RaiseArms || anim == ANIM_Peach2_Talk || anim == ANIM_Peach2_LowerArms)
        ) {
            anim = ANIM_Peach3_PresentCompleteCake;
        }
    }

    if (anim == ANIM_MarioW2_Collapse) {
        exec_ShakeCam1(0, 0, 2);
    }

    return anim;
}

void suggest_player_anim_allow_backward(AnimID anim) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    AnimID newAnim = get_overriding_player_anim(anim);

    if (newAnim != -1) {
        playerStatus->anim = newAnim;
        playerStatus->animNotifyValue = 0;
        playerStatus->flags &= ~PS_FLAG_FACE_FORWARD;
    }
}

void force_player_anim(AnimID anim) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    playerStatus->anim = anim;
    playerStatus->animNotifyValue = 0;
    playerStatus->flags &= ~PS_FLAG_FACE_FORWARD;
}

void suggest_player_anim_always_forward(AnimID anim) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    AnimID newAnim = get_overriding_player_anim(anim);

    if (newAnim != -1) {
        playerStatus->anim = newAnim;
        playerStatus->animNotifyValue = 0;
        playerStatus->flags |= PS_FLAG_FACE_FORWARD;
    }
}

void update_player_blink(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    b32 outtaSight = false;

    if (gPartnerStatus.actingPartner == PARTNER_BOW) {
        outtaSight = gPartnerStatus.partnerActionState != PARTNER_ACTION_NONE;
    }

    if (playerStatus->blinkTimer > 0) {
        playerStatus->blinkTimer--;

        if (!(gGameStatusPtr->frameCounter & 1)) {
            if (outtaSight) {
                playerStatus->curAlpha = 192;
            } else {
                playerStatus->curAlpha = 255;
            }
        } else {
            playerStatus->curAlpha = 96;
        }

        if (!playerStatus->blinkTimer) {
            if (outtaSight) {
                playerStatus->curAlpha = 128;
                playerStatus->flags |= PS_FLAG_HAZARD_INVINCIBILITY;
            } else {
                playerStatus->curAlpha = 255;
                playerStatus->flags &= ~PS_FLAG_HAZARD_INVINCIBILITY;
            }
        } else {
            playerStatus->flags |= PS_FLAG_HAZARD_INVINCIBILITY;
        }
    }
}

f32 get_xz_dist_to_player(f32 x, f32 z) {
    return dist2D(x, z, gPlayerStatus.pos.x, gPlayerStatus.pos.z);
}

void enable_player_shadow(void) {
    get_shadow_by_index(gPlayerStatus.shadowID)->flags &= ~ENTITY_FLAG_HIDDEN;
}

void disable_player_shadow(void) {
    get_shadow_by_index(gPlayerStatus.shadowID)->flags |= ENTITY_FLAG_HIDDEN;
}

s32 disable_player_static_collisions(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    playerStatus->flags |= PS_FLAG_NO_STATIC_COLLISION;
    playerStatus->enableCollisionOverlapsCheck++;
    return playerStatus->enableCollisionOverlapsCheck;
}

s32 enable_player_static_collisions(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    playerStatus->enableCollisionOverlapsCheck--;
    if (playerStatus->enableCollisionOverlapsCheck == 0) {
        playerStatus->flags &= ~PS_FLAG_NO_STATIC_COLLISION;
    }
    return playerStatus->enableCollisionOverlapsCheck;
}

s32 disable_player_input(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    playerStatus->flags |= PS_FLAG_INPUT_DISABLED;
    playerStatus->inputDisabledCount++;
    return playerStatus->inputDisabledCount;
}

s32 enable_player_input(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    playerStatus->inputDisabledCount--;
    if (playerStatus->inputDisabledCount == 0) {
        playerStatus->flags &= ~PS_FLAG_INPUT_DISABLED;
    }
    return playerStatus->inputDisabledCount;
}

b32 check_player_action_debug(void) {
    if (gGameStatusPtr->debugScripts != DEBUG_SCRIPTS_NONE && (gGameStatusPtr->curButtons[0] & BUTTON_R)) {
        if (gPartnerStatus.partnerActionState == PARTNER_ACTION_NONE) {
            set_action_state(ACTION_STATE_IDLE);
        }
        return true;
    }
    return false;
}

void update_partner_timers(void) {
    PlayerData* playerData = &gPlayerData;

    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        s32 i;

        for (i = 1; i < ARRAY_COUNT(playerData->partnerUnlockedTime); i++) {
            if (playerData->partners[i].enabled) {
                playerData->partnerUnlockedTime[i]++;
            }
        }
    }
}
