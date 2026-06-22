// this file and world/actions.c are candidates for merging

#include "common.h"
#include "world/partners.h"
#include "world/actions.h"
#include "world/disguise.h"
#include "npc.h"
#include "effects.h"
#include "ld_addrs.h"

extern Addr world_action_CLASS_VRAM;

void* LastLoadedActionOffset;
s32 gSpinHistoryBufferPos;
s32 gSpinHistoryPosX[5];
s32 gSpinHistoryPosY[5];
s32 gSpinHistoryPosZ[5];
s16 gSpinHistoryPosAngle[5];

s32 PrevPlayerCamRelativeYaw = 0;

f32 LastMidairPlayerVelY = 0.0;

s32 (*LandingAdjustCamCallback)(void) = nullptr;

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

    LastLoadedActionOffset = nullptr;
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

        if (playerStatus->flags & PS_FLAG_ACTION_STATE_CHANGED) {
            if (action->dmaStart != nullptr && action->dmaStart != LastLoadedActionOffset) {
                LastLoadedActionOffset = action->dmaStart;
                dma_copy(action->dmaStart, action->dmaEnd, world_action_CLASS_VRAM);
            }
        }
        action->update();
    } while (playerStatus->flags & PS_FLAG_ACTION_STATE_CHANGED);
}

void phys_peach_update(void) {
    calculate_camera_yinterp_rate();

    do {
        if (!(gPlayerStatus.flags & PS_FLAG_PAUSED) && check_conversation_trigger()) {
            set_action_state(ACTION_STATE_TALK);
        }

        Action* action = &PlayerActionsTable[gPlayerStatus.actionState];

        if (action->flag) {
            if (gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED) {
                if (action->dmaStart != nullptr && action->dmaStart != LastLoadedActionOffset) {
                    LastLoadedActionOffset = action->dmaStart;
                    dma_copy(action->dmaStart, action->dmaEnd, world_action_CLASS_VRAM);
                }
            }
            action->update();
        }
    } while (gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED);

    peach_check_for_parasol_input();
    if (gPlayerStatus.animFlags & PA_FLAG_INVISIBLE) {
        peach_sync_disguise_npc();
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
        if (actionState >= ACTION_STATE_IDLE && actionState < ACTION_STATE_TALK) {
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
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (!is_ability_active(ABILITY_SLOW_GO) &&
        SQ(playerStatus->stickAxis[0]) + SQ(playerStatus->stickAxis[1]) > SQ(55))
    {
        set_action_state(ACTION_STATE_RUN);
    } else {
        set_action_state(ACTION_STATE_WALK);
    }
}

void start_falling(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    set_action_state(ACTION_STATE_FALLING);
    LOAD_INTEGRATOR_FALL(playerStatus->gravityIntegrator);
}

void start_bounce_a(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    set_action_state(ACTION_STATE_BOUNCE);
    playerStatus->gravityIntegrator[0] = 10.0f;
    playerStatus->gravityIntegrator[1] = -2.0f;
    playerStatus->gravityIntegrator[2] = 0.8f;
    playerStatus->gravityIntegrator[3] = -0.75f;
}

void start_bounce_b(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    set_action_state(ACTION_STATE_BOUNCE);
    playerStatus->gravityIntegrator[0] = 8.0f;
    playerStatus->gravityIntegrator[1] = -1.0f;
    playerStatus->gravityIntegrator[2] = 0;
    playerStatus->gravityIntegrator[3] = 0;
    playerStatus->flags |= PS_FLAG_SCRIPTED_FALL;
}

b32 check_input_hammer(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerData* playerData = &gPlayerData;

    if (playerStatus->pressedButtons & BUTTON_B) {
        if (playerStatus->flags & PS_FLAG_FALLING) {
            return false;
        }

        if (gPartnerStatus.partnerActionState == PARTNER_ACTION_USE && playerData->curPartner == PARTNER_WATT) {
            return false;
        }

        if (playerData->hammerLevel == -1) {
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
            if ((entity->boundScriptBytecode == nullptr) || (entity->flags & ENTITY_FLAG_4000)) {
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
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerSpinState* spinState = &gPlayerSpinState;
    PlayerSpinState* temp2 = spinState;

    if (!((playerStatus->flags & (PS_FLAG_NO_STATIC_COLLISION | PS_FLAG_CUTSCENE_MOVEMENT)) ||
          (playerStatus->animFlags & PA_FLAG_USING_WATT) ||
          (playerStatus->curButtons & BUTTON_C_DOWN) ||
          is_ability_active(ABILITY_SLOW_GO))) {

        s32 actionState = playerStatus->actionState;
        s32 btnPressed = playerStatus->pressedButtons & Z_TRIG;

        // TODO
        if (actionState != ACTION_STATE_RIDE) {
            if (actionState < ACTION_STATE_STEP_UP) {
                if (actionState < ACTION_STATE_JUMP) {
                    if (actionState >= 0 && !(playerStatus->animFlags & PA_FLAG_SPINNING)) {
                        if (btnPressed || spinState->hasBufferedSpin) {
                            set_action_state(ACTION_STATE_SPIN);
                            if (spinState->hasBufferedSpin != false) {
                                if (spinState->bufferedStickAxis.x != 0 || spinState->bufferedStickAxis.y != 0) {
                                    playerStatus->prevActionState = temp2->prevActionState;
                                } else {
                                    playerStatus->prevActionState = ACTION_STATE_IDLE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
