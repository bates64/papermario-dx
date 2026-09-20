// this file and world/actions.c are candidates for merging

#include "common.h"
#include "world/partners.h"
#include "world/actions.h"
#include "world/disguise.h"
#include "npc.h"
#include "effects.h"
#include "dx/overlay.h"

static Overlay* CurrentActionOverlay;
static ActionFamily CurrentActionFamily;
static ActionUpdate CurrentActionUpdate;
s32 gSpinHistoryBufferPos;
s32 gSpinHistoryPosX[5];
s32 gSpinHistoryPosY[5];
s32 gSpinHistoryPosZ[5];
s16 gSpinHistoryPosAngle[5];

s32 PrevPlayerCamRelativeYaw = 0;

f32 LastMidairPlayerVelY = 0.0;

s32 (*LandingAdjustCamCallback)(void) = nullptr;

void unload_player_action(void) {
    ovl_unload(CurrentActionOverlay);
    CurrentActionOverlay = nullptr;
    CurrentActionFamily = nullptr;
    CurrentActionUpdate = nullptr;
}

static void load_player_action(Action* action) {
    ASSERT_MSG(action->entry != nullptr, "Action state %d has no entry point",
               (int)gPlayerStatus.actionState);

    if (CurrentActionOverlay == nullptr ||
        strcmp(CurrentActionFamily, action->family) != 0) {
        unload_player_action();
        CurrentActionOverlay = ovl_load(action->family, OVL_ACTION);
        CurrentActionFamily = action->family;
    }

    CurrentActionUpdate = ovl_import(CurrentActionOverlay, action->entry);
    ASSERT_MSG(CurrentActionUpdate != nullptr, "Action overlay '%s' has no export '%s'",
               action->family, action->entry);
}

void phys_set_landing_adjust_cam_check(s32 (*funcPtr)(void)) {
    LandingAdjustCamCallback = funcPtr;
}

s32 phys_adjust_cam_on_landing(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (LandingAdjustCamCallback != nullptr) {
        ret = LandingAdjustCamCallback();
    }

    if (ret == LANDING_CAM_CHECK_SURFACE) {
        s32 surfaceType = get_collider_flags(gCollisionStatus.curFloor) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;

        if (surfaceType == SURFACE_TYPE_LAVA) {
            gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_IGNORE_PLAYER_Y;
            ret = LANDING_CAM_NEVER_ADJUST;
        } else {
            gCameras[CAM_DEFAULT].moveFlags &= ~CAMERA_MOVE_IGNORE_PLAYER_Y;
        }
    } else if (gPartnerStatus.actingPartner == PARTNER_PARAKARRY && gPartnerStatus.partnerActionState != PARTNER_ACTION_NONE) {
        gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_NO_INTERP_Y;
    } else {
        gCameras[CAM_DEFAULT].moveFlags &= ~CAMERA_MOVE_NO_INTERP_Y;
    }

    return ret;
}

void phys_clear_spin_history(void) {
    s32 i;

    gSpinHistoryBufferPos = 0;

    for (i = 0; i < ARRAY_COUNT(gSpinHistoryPosAngle); i++) {
        gSpinHistoryPosAngle[i] = 180;
        gSpinHistoryPosY[i] = 0x80000000;
    }
}

f32 phys_get_spin_history(s32 lag, s32* x, s32* y, s32* z) {
    s32 idx = gSpinHistoryBufferPos - lag;

    if (idx < 0) {
        idx += ARRAY_COUNT(gSpinHistoryPosAngle);
    }

    *x = gSpinHistoryPosX[idx];
    *y = gSpinHistoryPosY[idx];
    *z = gSpinHistoryPosZ[idx];
    return gSpinHistoryPosAngle[idx];
}

void phys_reset_spin_history(void) {
    s32 i;

    mem_clear(&gPlayerSpinState, sizeof(PlayerSpinState));
    gSpinHistoryBufferPos = 0;

    for (i = 0; i < ARRAY_COUNT(gSpinHistoryPosAngle); i++) {
        gSpinHistoryPosAngle[i] = 0;
        gSpinHistoryPosX[i] = 0;
        gSpinHistoryPosY[i] = 0;
        gSpinHistoryPosZ[i] = 0;
    }

    unload_player_action();
}

void phys_update_action_state(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerSpinState* playerSpinState = &gPlayerSpinState;

    if (!(playerStatus->flags & PS_FLAG_ENTERING_BATTLE)) {
        playerStatus->flags &= ~PS_FLAG_TIME_STOPPED;
    }

    if (playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS) {
        phys_peach_update();
        return;
    }

    if (playerStatus->camResetDelay != 0) {
        playerStatus->camResetDelay--;
        if (playerStatus->camResetDelay == 0) {
            gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_ACCEL_INTERP_Y;
        }
    }

    // if midair, look for velocity inflection
    if (playerStatus->timeInAir != 0) {
        if (playerStatus->gravityIntegrator[0] <= 0.0f && LastMidairPlayerVelY > 0.0f) {
            playerStatus->peakJumpTime = playerStatus->timeInAir;
        }
        LastMidairPlayerVelY = playerStatus->gravityIntegrator[0];
    }

    calculate_camera_yinterp_rate();

    if (playerSpinState->stopSoundTimer != 0) {
        playerSpinState->stopSoundTimer--;
        if (playerSpinState->stopSoundTimer == 0) {
            playerStatus->animFlags &= ~PA_FLAG_SPINNING;
            if (playerSpinState->spinSoundID != 0) {
                sfx_stop_sound(playerSpinState->spinSoundID);
            }
        }
    }

    do {
        s32 actionState = playerStatus->actionState;

        if (actionState == ACTION_STATE_IDLE || actionState == ACTION_STATE_WALK || actionState == ACTION_STATE_RUN) {
            s32 cond;

            if (!(playerStatus->flags & PS_FLAG_INPUT_DISABLED)) {
                cond = check_conversation_trigger();
            } else {
                cond = false;
            }

            if ((gPartnerStatus.partnerActionState == PARTNER_ACTION_NONE) && !(playerStatus->flags & PS_FLAG_PAUSED) && cond) {
                set_action_state(ACTION_STATE_TALK);
            }
            check_input_spin();
        }

        Action* action = &PlayerActionsTable[gPlayerStatus.actionState];

        if ((playerStatus->flags & PS_FLAG_ACTION_STATE_CHANGED) || CurrentActionOverlay == nullptr) {
            load_player_action(action);
        }
        CurrentActionUpdate();
    } while (playerStatus->flags & PS_FLAG_ACTION_STATE_CHANGED);
}

void phys_peach_update(void) {
    calculate_camera_yinterp_rate();

    do {
        if (!(gPlayerStatus.flags & PS_FLAG_PAUSED) && check_conversation_trigger()) {
            set_action_state(ACTION_STATE_TALK);
        }

        Action* action = &PlayerActionsTable[gPlayerStatus.actionState];

        if (action->enabledForPeach) {
            if ((gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED) || CurrentActionOverlay == nullptr) {
                load_player_action(action);
            }
            CurrentActionUpdate();
        }
    } while (gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED);

    peach_check_for_parasol_input();
    if (gPlayerStatus.animFlags & PA_FLAG_INVISIBLE) {
        peach_sync_disguise_npc();
    }
}

b32 action_is_locomotion(s32 actionState) {
    switch (actionState) {
        case ACTION_STATE_IDLE:
        case ACTION_STATE_WALK:
        case ACTION_STATE_RUN:
            return true;
        default:
            return false;
    }
}

b32 action_8bit_supported(s32 actionState) {
    switch (actionState) {
        case ACTION_STATE_IDLE:
        case ACTION_STATE_WALK:
        case ACTION_STATE_RUN:
        case ACTION_STATE_JUMP:
        case ACTION_STATE_BOUNCE:
        case ACTION_STATE_HOP:
        case ACTION_STATE_LAUNCH:
        case ACTION_STATE_LANDING_ON_SWITCH:
        case ACTION_STATE_FALLING:
        case ACTION_STATE_STEP_DOWN:
        case ACTION_STATE_LAND:
        case ACTION_STATE_STEP_DOWN_LAND:
            return true;
        default:
            return false;
    }
}

void set_action_state(s32 actionState) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerData* playerData = &gPlayerData;
    PlayerSpinState* spinState = &gPlayerSpinState;

    if (playerStatus->flags & PS_FLAG_SPECIAL_JUMP) {
        playerStatus->flags &= ~PS_FLAG_SPECIAL_JUMP;
        enable_player_input();
    }

    if (playerStatus->animFlags & PA_FLAG_8BIT_MARIO) {
        if (action_8bit_supported(actionState)) {
            playerStatus->prevActionState = playerStatus->actionState;
            playerStatus->actionState = actionState;
            playerStatus->flags |= PS_FLAG_ACTION_STATE_CHANGED;
        }
        return;
    }

    if (actionState == ACTION_STATE_HIT_FIRE || actionState == ACTION_STATE_HIT_LAVA) {
        s8 partner;

        if (playerStatus->hazardType == HAZARD_TYPE_FIRE_BAR) {
            actionState = ACTION_STATE_HIT_FIRE;
        }

        // Whilst Sushie, Lakilester, or Parakarry's ability is active, hazards have no effect.
        partner = playerData->curPartner;

        if (partner == PARTNER_SUSHIE || partner == PARTNER_LAKILESTER || partner == PARTNER_PARAKARRY) {
            if (gPartnerStatus.partnerActionState != PARTNER_ACTION_NONE) {
                playerStatus->animFlags |= PA_FLAG_INTERRUPT_USE_PARTNER;
                playerStatus->flags |= PS_FLAG_HIT_FIRE;
                return;
            }
        }
    }

    if (actionState == ACTION_STATE_SLIDING) {
        playerStatus->flags |= PS_FLAG_SLIDING;
        playerStatus->moveFrames = 0;
        playerStatus->flags &= ~PS_FLAG_CUTSCENE_MOVEMENT;
    }

    playerStatus->prevActionState = playerStatus->actionState;
    if (actionState == ACTION_STATE_USE_TWEESTER) {
        playerStatus->prevActionState = ACTION_STATE_IDLE;
    }

    if (actionState == ACTION_STATE_ENEMY_FIRST_STRIKE) {
        playerStatus->animFlags |= PA_FLAG_INTERRUPT_USE_PARTNER;
    }
    playerStatus->actionState = actionState;
    playerStatus->flags |= PS_FLAG_ACTION_STATE_CHANGED;

    if (playerStatus->actionState == ACTION_STATE_SPIN) {
        return;
    }

    playerStatus->flags &= ~PS_FLAG_SPINNING;
    playerStatus->animFlags &= ~PA_FLAG_SPINNING;

    if (spinState->spinSoundID != 0) {
        sfx_stop_sound(spinState->spinSoundID);
    }

    if (playerStatus->specialDecorationEffect != nullptr) {
        playerStatus->specialDecorationEffect->data.spin->timeLeft = 10;
        playerStatus->specialDecorationEffect = nullptr;
    }
}

void update_locomotion_state(void) {
    if (is_ability_active(ABILITY_SLOW_GO)) {
        set_action_state(ACTION_STATE_WALK);
    } else if (SQ(gPlayerStatus.stickAxis[0]) + SQ(gPlayerStatus.stickAxis[1]) > SQ(55)) {
        set_action_state(ACTION_STATE_RUN);
    } else {
        set_action_state(ACTION_STATE_WALK);
    }
}

void start_falling(void) {
    set_action_state(ACTION_STATE_FALLING);
    LOAD_INTEGRATOR_FALL(gPlayerStatus.gravityIntegrator);
}

void start_bounce_a(void) {
    set_action_state(ACTION_STATE_BOUNCE);
    gPlayerStatus.gravityIntegrator[0] = 10.0f;
    gPlayerStatus.gravityIntegrator[1] = -2.0f;
    gPlayerStatus.gravityIntegrator[2] = 0.8f;
    gPlayerStatus.gravityIntegrator[3] = -0.75f;
}

void start_bounce_b(void) {
    set_action_state(ACTION_STATE_BOUNCE);
    gPlayerStatus.gravityIntegrator[0] = 8.0f;
    gPlayerStatus.gravityIntegrator[1] = -1.0f;
    gPlayerStatus.gravityIntegrator[2] = 0;
    gPlayerStatus.gravityIntegrator[3] = 0;
    gPlayerStatus.flags |= PS_FLAG_SCRIPTED_FALL;
}

b32 check_input_hammer(void) {
    if (gPlayerStatus.pressedButtons & BUTTON_B) {
        if (gPlayerStatus.flags & PS_FLAG_FALLING) {
            return false;
        }

        if (gPartnerStatus.partnerActionState == PARTNER_ACTION_USE && gPlayerData.curPartner == PARTNER_WATT) {
            return false;
        }

        if (gPlayerData.hammerLevel == GEAR_RANK_NONE) {
            return false;
        }

        set_action_state(ACTION_STATE_HAMMER);
        return true;
    }
    return false;
}

b32 check_input_jump(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;
    s32 surfaceType;

    if (!(playerStatus->pressedButtons & BUTTON_A)) {
        return false;
    }

    surfaceType = get_collider_flags((u16)gCollisionStatus.curFloor) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
    if ((surfaceType == SURFACE_TYPE_SLIDE) && phys_should_player_be_sliding()) {
        return false;
    }

    if (collisionStatus->touchingWallTrigger != 0 ||
        (playerStatus->animFlags & (PA_FLAG_SPEECH_PROMPT_AVAILABLE |
                                    PA_FLAG_INTERACT_PROMPT_AVAILABLE)))
    {
        return false;
    }

    if ((collisionStatus->curInspect != -1) && (collisionStatus->curInspect & COLLISION_WITH_ENTITY_BIT)) {
        Entity* entity = get_entity_by_index(collisionStatus->curInspect);

        if (entity->flags & ENTITY_FLAG_SHOWS_INSPECT_PROMPT) {
            if ((entity->script.source == nullptr) || (entity->flags & ENTITY_FLAG_4000)) {
                if (entity->type == ENTITY_TYPE_PINK_FLOWER ||
                    entity->type == ENTITY_TYPE_BELLBELL_PLANT ||
                    entity->type == ENTITY_TYPE_TRUMPET_PLANT)
                {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    set_action_state(ACTION_STATE_JUMP);
    return true;
}

void check_input_spin(void) {
    s32 actionState = gPlayerStatus.actionState;
    s32 btnPressed = gPlayerStatus.pressedButtons & Z_TRIG;

    // no spinning if normal collisions are disabled
    if (gPlayerStatus.flags & (PS_FLAG_NO_STATIC_COLLISION | PS_FLAG_CUTSCENE_MOVEMENT)) {
        return;
    }

    // cant spin with Watt out or if already spinning
    if (gPlayerStatus.animFlags & (PA_FLAG_USING_WATT | PA_FLAG_SPINNING)) {
        return;
    }

    // cant spin and use partner at the same time
    if (gPlayerStatus.curButtons & BUTTON_C_DOWN) {
        return;
    }

    // cant spin with Slow Go equipped
    if (is_ability_active(ABILITY_SLOW_GO)) {
        return;
    }

    // only allow spinning in a locomotion action state
    if (!action_is_locomotion(actionState)) {
        return;
    }

    if (btnPressed || gPlayerSpinState.hasBufferedSpin) {
        set_action_state(ACTION_STATE_SPIN);
        if (gPlayerSpinState.hasBufferedSpin) {
            if (gPlayerSpinState.bufferedStickAxis.x != 0 || gPlayerSpinState.bufferedStickAxis.y != 0) {
                gPlayerStatus.prevActionState = gPlayerSpinState.prevActionState;
            } else {
                gPlayerStatus.prevActionState = ACTION_STATE_IDLE;
            }
        }
    }
}
