#include "common.h"
#include "world/partners.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/player.h"

BSS b32 UsingAbility;
BSS b32 LockingPlayerInput;
BSS b32 PlayerCollisionDisabled; // minor bug: never gets properly reset to false
BSS b32 PlayerWasFacingLeft;
BSS s32 AbilityState;
BSS s32 AbilityStateTime;
BSS TweesterPhysics TweesterPhysicsData;

enum {
    AIR_LIFT_NONE       = 0,  // only used for initial value
    // next two states lock input for a few frames, during which the ability can be canceled
    AIR_LIFT_INIT       = 40,
    AIR_LIFT_DELAY      = 41,
    AIR_LIFT_BEGIN      = 30,
    AIR_LIFT_GATHER     = 31,
    AIR_LIFT_PICKUP     = 1,   // pick up the player and lift them into the air
    AIR_LIFT_CARRY      = 2,   // carry the player through the air
    AIR_LIFT_HOLD       = 6,   // remain in one position for a short period of time
    AIR_LIFT_JUMP       = 20,  // player jumped off while being carried
    AIR_LIFT_DROP       = 21,  // dropping the player
    AIR_LIFT_CANCEL     = 22,
};

void init(Npc* parakarry) {
    parakarry->collisionHeight = 37;
    parakarry->collisionDiameter = 40;
    UsingAbility  = false;
    AbilityState = AIR_LIFT_NONE;
    LockingPlayerInput = false;
    PlayerCollisionDisabled = false;
    PlayerWasFacingLeft = false;
    AbilityStateTime = 0;
}

API_CALLABLE(TakeOut) {
    Npc* parakarry = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(parakarry);
    }

    if (partner_get_out(parakarry)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldParakarry_TakeOut = {
    Call(TakeOut)
    Return
    End
};

TweesterPhysics* TweesterPhysicsPtr = &TweesterPhysicsData;

API_CALLABLE(Update) {
    PlayerData* playerData = &gPlayerData;
    Npc* parakarry = script->owner2.npc;
    f32 sinAngle, cosAngle, liftoffVelocity;
    Entity* entity;

    if (isInitialCall) {
        partner_flying_enable(parakarry, true);
        mem_clear(TweesterPhysicsPtr, sizeof(TweesterPhysics));
        TweesterTouchingPartner = nullptr;
    }

    playerData->partnerUsedTime[PARTNER_PARAKARRY]++;
    entity = TweesterTouchingPartner;

    if (entity == nullptr) {
        partner_flying_update_player_tracking(parakarry);
        partner_flying_update_motion(parakarry);
        return ApiStatus_BLOCK;
    }

    switch (TweesterPhysicsPtr->state) {
        case TWEESTER_PARTNER_INIT:
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_ATTRACT;
            TweesterPhysicsPtr->prevFlags = parakarry->flags;
            TweesterPhysicsPtr->radius = fabsf(dist2D(parakarry->pos.x, parakarry->pos.z,
                                                     entity->pos.x, entity->pos.z));
            TweesterPhysicsPtr->angle = atan2(entity->pos.x, entity->pos.z,
                                              parakarry->pos.x, parakarry->pos.z);
            TweesterPhysicsPtr->angularVel = 6.0f;
            TweesterPhysicsPtr->liftoffVelPhase = 50.0f;
            TweesterPhysicsPtr->countdown = 120;
            parakarry->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_FLYING;
            parakarry->flags &= ~NPC_FLAG_GRAVITY;
        case TWEESTER_PARTNER_ATTRACT:
            sin_cos_rad(DEG_TO_RAD(TweesterPhysicsPtr->angle), &sinAngle, &cosAngle);
            parakarry->pos.x = entity->pos.x + (sinAngle * TweesterPhysicsPtr->radius);
            parakarry->pos.z = entity->pos.z - (cosAngle * TweesterPhysicsPtr->radius);
            TweesterPhysicsPtr->angle = clamp_angle(TweesterPhysicsPtr->angle - TweesterPhysicsPtr->angularVel);

            if (TweesterPhysicsPtr->radius > 20.0f) {
                TweesterPhysicsPtr->radius--;
            } else if (TweesterPhysicsPtr->radius < 19.0f) {
                TweesterPhysicsPtr->radius++;
            }

            liftoffVelocity = sin_rad(DEG_TO_RAD(TweesterPhysicsPtr->liftoffVelPhase)) * 3.0f;
            TweesterPhysicsPtr->liftoffVelPhase += 3.0f;

            if (TweesterPhysicsPtr->liftoffVelPhase > 150.0f) {
                TweesterPhysicsPtr->liftoffVelPhase = 150.0f;
            }

            parakarry->pos.y += liftoffVelocity;
            parakarry->renderYaw = clamp_angle(360.0f - TweesterPhysicsPtr->angle);
            TweesterPhysicsPtr->angularVel += 0.8;

            if (TweesterPhysicsPtr->angularVel > 40.0f) {
                TweesterPhysicsPtr->angularVel = 40.0f;
            }

            TweesterPhysicsPtr->countdown--;
            if (TweesterPhysicsPtr->countdown == 0) {
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_HOLD;
            }
            break;
        case TWEESTER_PARTNER_HOLD:
            parakarry->flags = TweesterPhysicsPtr->prevFlags;
            TweesterPhysicsPtr->countdown = 30;
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_RELEASE;
            break;
        case TWEESTER_PARTNER_RELEASE:
            partner_flying_update_player_tracking(parakarry);
            partner_flying_update_motion(parakarry);

            TweesterPhysicsPtr->countdown--;
            if (TweesterPhysicsPtr->countdown == 0) {
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
                TweesterTouchingPartner = nullptr;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldParakarry_Update = {
    Call(Update)
    Return
    End
};

void try_cancel_tweester(Npc* parakarry) {
    if (TweesterTouchingPartner) {
        TweesterTouchingPartner = nullptr;
        parakarry->flags = TweesterPhysicsPtr->prevFlags;
        TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
        partner_clear_player_tracking (parakarry);
    }
}

HitID update_current_floor(void) {
    f32 x, y, z, length, hitRx, hitRz, hitDirX, hitDirZ;
    f32 colliderBaseHeight = gPlayerStatus.colliderHeight;
    HitID hitID;
    s32 surfaceType;

    x = gPlayerStatus.pos.x;
    y = gPlayerStatus.pos.y + (colliderBaseHeight * 0.5);
    z = gPlayerStatus.pos.z;
    length = colliderBaseHeight / 2.0f;

    hitID = player_raycast_below_cam_relative(&gPlayerStatus, &x, &y, &z, &length, &hitRx,
                                                      &hitRz, &hitDirX, &hitDirZ);

    surfaceType = get_collider_flags(hitID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
    if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
        gPlayerStatus.hazardType = HAZARD_TYPE_SPIKES;
        gPlayerStatus.flags |= PS_FLAG_HIT_FIRE;
        AbilityState = AIR_LIFT_DROP;
    }

    return hitID;
}

API_CALLABLE(UseAbility) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    Npc* parakarry = script->owner2.npc;
    s32 buttonTemp = BUTTON_A;
    f32 x, y, z, yaw, length;
    f32 playerDeltaX, playerDeltaZ;
    f32 parakarryDeltaX, parakarryDeltaZ;
    f32 halfCollisionHeight;
    s32 hitCount;
    b32 hitAbove;

    if (gCurrentEncounter.battleTransitionState != BATTLE_TRANSITION_STATE_STARTED) {
         return ApiStatus_BLOCK;
    }

    if (isInitialCall) {
        try_cancel_tweester(parakarry);
        if ((playerStatus->animFlags & PA_FLAG_CHANGING_MAP)) {
            return ApiStatus_DONE2;
        }

        if (!partnerStatus->shouldResumeAbility) {
            if (!partner_can_continue_ability(PARTNER_PARAKARRY)) {
                return ApiStatus_DONE2;
            }
            AbilityState = AIR_LIFT_INIT;
            parakarry->flags &= ~NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD;
            parakarry->flags |= NPC_FLAG_COLLIDING_WITH_WORLD;
        } else {
            partnerStatus->shouldResumeAbility = false;
            set_action_state(ACTION_STATE_RIDE);
            parakarry->flags &= ~(NPC_FLAG_JUMPING | NPC_FLAG_GRAVITY);
            UsingAbility  = true;
            gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_IGNORE_PLAYER_Y;
            parakarry->curAnim = ANIM_WorldParakarry_CarryLight;
            partnerStatus->actingPartner = PARTNER_PARAKARRY;
            partnerStatus->partnerActionState = PARTNER_ACTION_PARAKARRY_HOVER;
            parakarry->flags &= ~NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD;
            parakarry->flags |= NPC_FLAG_COLLIDING_WITH_WORLD;
        }
    }

    switch (AbilityState) {
        case AIR_LIFT_INIT:
            if (playerStatus->inputDisabledCount != 0) {
                return ApiStatus_DONE2;
            }
            AbilityStateTime = 3;
            AbilityState = AIR_LIFT_DELAY;
            script->functionTemp[2] = playerStatus->inputDisabledCount;
            // fallthrough
        case AIR_LIFT_DELAY:
            if (AbilityStateTime == 0) {
                if (script->functionTemp[2] < playerStatus->inputDisabledCount || !partner_can_continue_ability(PARTNER_PARAKARRY)) {
                    return ApiStatus_DONE2;
                }
                AbilityState = AIR_LIFT_BEGIN;
            } else {
                AbilityStateTime--;
            }
            break;
    }

    switch (AbilityState) {
        case AIR_LIFT_BEGIN:
            set_action_state(ACTION_STATE_RIDE);
            disable_player_input();
            disable_player_static_collisions();
            script->functionTemp[2] = playerStatus->inputDisabledCount;
            LockingPlayerInput = true;
            PlayerCollisionDisabled = true;
            UsingAbility = true;
            gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_IGNORE_PLAYER_Y;
            parakarry->flags &= ~(NPC_FLAG_JUMPING | NPC_FLAG_GRAVITY);
            parakarry->flags |= NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_FLYING;
            partnerStatus->actingPartner = PARTNER_PARAKARRY;
            partnerStatus->partnerActionState = PARTNER_ACTION_PARAKARRY_HOVER;
            PlayerWasFacingLeft = partner_force_player_flip_done();
            enable_npc_blur(parakarry);
            parakarry->yaw = atan2(parakarry->pos.x, parakarry->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            parakarry->duration = 4;
            AbilityState++; // AIR_LIFT_GATHER
            break;
        case AIR_LIFT_GATHER:
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_HIT_LAVA
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
             || playerStatus->actionState == ACTION_STATE_JUMP
             || playerStatus->actionState == ACTION_STATE_HOP
            ) {
                disable_npc_blur(parakarry);
                AbilityState = AIR_LIFT_DROP;
            } else {
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                parakarry->moveToPos.x = playerStatus->pos.x;
                parakarry->moveToPos.y = playerStatus->pos.y + 32.0f;
                parakarry->moveToPos.z = playerStatus->pos.z;
                parakarry->curAnim = ANIM_WorldParakarry_Run;
                add_vec2D_polar(&parakarry->moveToPos.x, &parakarry->moveToPos.z, 0.0f, playerStatus->targetYaw);
                yaw = playerStatus->targetYaw;

                yaw += !PlayerWasFacingLeft ? 90.0f : -90.0f;

                add_vec2D_polar(&parakarry->moveToPos.x, &parakarry->moveToPos.z, 5.0f, clamp_angle(yaw));

                parakarry->pos.x += (parakarry->moveToPos.x - parakarry->pos.x) / parakarry->duration;
                parakarry->pos.y += (parakarry->moveToPos.y - parakarry->pos.y) / parakarry->duration;
                parakarry->pos.z += (parakarry->moveToPos.z - parakarry->pos.z) / parakarry->duration;
                parakarry->duration--;
                if (parakarry->duration != 0) {
                    if (script->functionTemp[2] < playerStatus->inputDisabledCount) {
                        disable_npc_blur(parakarry);
                        AbilityState = AIR_LIFT_CANCEL;
                    }
                } else {
                    disable_npc_blur(parakarry);
                    parakarry->yaw = playerStatus->targetYaw;
                    parakarry->moveSpeed = 0.2f;
                    parakarry->curAnim = ANIM_WorldParakarry_CarryHeavy;
                    parakarry->planarFlyDist = 0;
                    suggest_player_anim_always_forward(ANIM_MarioW2_HoldOnto);
                    sfx_play_sound_at_npc(SOUND_PARAKARRY_FLAP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                    gCollisionStatus.lastTouchedFloor = NO_COLLIDER;
                    gCollisionStatus.curFloor = NO_COLLIDER;
                    parakarry->curFloor = NO_COLLIDER;
                    AbilityStateTime = 20;
                    AbilityState = AIR_LIFT_PICKUP;
                }
            }
            break;
        case AIR_LIFT_PICKUP:
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_HIT_LAVA
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
            ) {
                AbilityState = AIR_LIFT_DROP;
                break;
            }
            // handle jump/cancel inputs
            if (partnerStatus->pressedButtons & (BUTTON_A | BUTTON_B | BUTTON_C_DOWN)) {
                AbilityState = (partnerStatus->pressedButtons & BUTTON_A) ? AIR_LIFT_JUMP : AIR_LIFT_DROP;
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                break;
            }

            if (gGameStatusPtr->frameCounter % 6 == 0) {
                sfx_play_sound_at_npc(SOUND_PARAKARRY_FLAP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
            }

            length = fabsf(sin_rad(DEG_TO_RAD((20 - AbilityStateTime) * 18))) * 1.3;
            playerStatus->pos.y += length;
            parakarry->pos.y += length;
            x = parakarry->pos.x;
            y = parakarry->pos.y + parakarry->collisionHeight / 2.0f;
            z = parakarry->pos.z;
            length = parakarry->collisionHeight / 2.0f;
            halfCollisionHeight = length;

            if (npc_raycast_up(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &length)) {
                if (length < halfCollisionHeight) {
                    AbilityStateTime = 0;
                }
            }

            length = playerStatus->colliderHeight / 2.0f;
            x = playerStatus->pos.x;
            y = playerStatus->pos.y + playerStatus->colliderHeight / 2.0f;
            z = playerStatus->pos.z;
            halfCollisionHeight = playerStatus->spriteFacingAngle - 90.0f + gCameras[gCurrentCameraID].curYaw;
            if (player_raycast_up_corners(playerStatus, &x, &y, &z, &length, halfCollisionHeight) > NO_COLLIDER) {
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                AbilityState = AIR_LIFT_DROP;
                break;
            }

            x = playerStatus->pos.x;
            y = playerStatus->pos.y;
            z = playerStatus->pos.z;
            hitCount = npc_test_move_complex_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, parakarry->moveSpeed, parakarry->yaw, playerStatus->colliderHeight, playerStatus->colliderDiameter);
            if (hitCount > 1) {
                playerStatus->pos.x += (x - playerStatus->pos.x) / 8.0f;
                playerStatus->pos.z += (z - playerStatus->pos.z) / 8.0f;
                parakarry->pos.x += (x - parakarry->pos.x) / 8.0f;
                parakarry->pos.z += (z - parakarry->pos.z) / 8.0f;
            }

            x = parakarry->pos.x;
            y = parakarry->pos.y;
            z = parakarry->pos.z;
            hitCount = npc_test_move_complex_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, parakarry->moveSpeed, parakarry->yaw, parakarry->collisionHeight, parakarry->collisionDiameter);
            if (hitCount > 1) {
                playerDeltaX = (x - playerStatus->pos.x) / 8.0f;
                playerDeltaZ = (z - playerStatus->pos.z) / 8.0f;
                parakarryDeltaX = (x - parakarry->pos.x) / 8.0f;
                parakarryDeltaZ = (z - parakarry->pos.z) / 8.0f;

                x = parakarry->pos.x + parakarryDeltaX;
                z = parakarry->pos.z + parakarryDeltaZ;

                x = parakarry->pos.x;
                y = parakarry->pos.y;
                z = parakarry->pos.z;
                hitCount = npc_test_move_complex_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, parakarry->moveSpeed, parakarry->yaw, parakarry->collisionHeight, parakarry->collisionDiameter);
                if (hitCount == 0) {
                    playerStatus->pos.x += playerDeltaX;
                    playerStatus->pos.z += playerDeltaZ;
                    parakarry->pos.x += parakarryDeltaX;
                    parakarry->pos.z += parakarryDeltaZ;
                }
            }

            if (hitCount == 0 && !(playerStatus->animFlags & PA_FLAG_NPC_COLLIDED)) {
                add_vec2D_polar(&parakarry->pos.x, &parakarry->pos.z, parakarry->moveSpeed, parakarry->yaw);
                add_vec2D_polar(&playerStatus->pos.x, &playerStatus->pos.z, parakarry->moveSpeed, parakarry->yaw);
                parakarry->planarFlyDist += parakarry->moveSpeed;
            }

            x = playerStatus->pos.x;
            y = playerStatus->pos.y + playerStatus->colliderHeight / 2.0f;
            z = playerStatus->pos.z;
            length = playerStatus->colliderHeight / 2.0f;
            if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &length, parakarry->yaw, parakarry->collisionDiameter)) {
                s32 surfaceType = get_collider_flags(NpcHitQueryColliderID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
                if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                    playerStatus->hazardType = HAZARD_TYPE_SPIKES;
                    playerStatus->flags |= PS_FLAG_HIT_FIRE;
                    AbilityState = AIR_LIFT_DROP;
                }

                playerStatus->pos.y += (y - playerStatus->pos.y) / 4.0f;
                parakarry->pos.y = playerStatus->pos.y + 32.0f;
            }

            if (parakarry->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                AbilityState = AIR_LIFT_DROP;
                break;
            }

            gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
            gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
            gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;
            if (AbilityStateTime != 0) {
                AbilityStateTime--;
            } else {
                parakarry->jumpVel = -0.5f;
                parakarry->jumpScale = -0.01f;
                parakarry->moveToPos.y = playerStatus->pos.y;
                parakarry->duration = 0;
                parakarry->curAnim = ANIM_WorldParakarry_CarryHeavy;
                parakarry->animationSpeed = 1.8f;
                gCollisionStatus.curFloor = NO_COLLIDER;
                AbilityState++; // AIR_LIFT_CARRY
            }
            break;
        case AIR_LIFT_CARRY:
            gCollisionStatus.curFloor = update_current_floor();
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_HIT_LAVA
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
            ) {
                AbilityState = AIR_LIFT_DROP;
                break;
            }

            suggest_player_anim_always_forward(ANIM_MarioW2_HoldOnto);
            if (playerStatus->flags & PS_FLAG_HIT_FIRE) {
                AbilityState = AIR_LIFT_JUMP;
                break;
            }

            // handle jump/cancel inputs
            if (partnerStatus->pressedButtons & (BUTTON_A | BUTTON_B | BUTTON_C_DOWN)) {
                if (partnerStatus->pressedButtons & buttonTemp) {   // TODO find a way to remove this while still loading 0x15 instead of moving it from register
                    if (!parakarry->pos.x) {

                    }
                }
                AbilityState = (partnerStatus->pressedButtons & BUTTON_A) ? AIR_LIFT_JUMP : AIR_LIFT_DROP;
                break;
            }

            if (gGameStatusPtr->frameCounter % 6 == 0) {
                sfx_play_sound_at_npc(SOUND_PARAKARRY_FLAP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
            }

            parakarry->jumpVel -= parakarry->jumpScale;
            if (parakarry->jumpVel > 0.0) {
                parakarry->jumpVel = 0.0f;
            }

            parakarry->pos.y += parakarry->jumpVel;
            playerStatus->pos.y += parakarry->jumpVel;
            if (!(playerStatus->animFlags & PA_FLAG_NPC_COLLIDED)) {
                parakarry->moveSpeed += 0.1;
                if (parakarry->moveSpeed > 2.0) {
                    parakarry->moveSpeed = 2.0f;
                }

                add_vec2D_polar(&parakarry->pos.x, &parakarry->pos.z, parakarry->moveSpeed, parakarry->yaw);
                add_vec2D_polar(&playerStatus->pos.x, &playerStatus->pos.z, parakarry->moveSpeed, parakarry->yaw);
                parakarry->planarFlyDist += parakarry->moveSpeed;
                parakarry->animationSpeed -= 0.05;
                if (parakarry->animationSpeed < 1.5) {
                    parakarry->animationSpeed = 1.5f;
                }
                if (parakarry->planarFlyDist > 80.0f) {
                    parakarry->animationSpeed += 0.5;
                }
                if (!(playerStatus->animFlags & PA_FLAG_NPC_COLLIDED)) {
                    x = playerStatus->pos.x;
                    y = playerStatus->pos.y;
                    z = playerStatus->pos.z;
                    if (npc_test_move_complex_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER,
                            &x, &y, &z, parakarry->moveSpeed, parakarry->yaw,
                            playerStatus->colliderHeight, playerStatus->colliderDiameter)
                    ) {
                        suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                        AbilityState = AIR_LIFT_DROP;
                        break;
                    }

                    x = parakarry->pos.x;
                    y = parakarry->pos.y;
                    z = parakarry->pos.z;
                    if (!npc_test_move_complex_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER,
                            &x, &y, &z, parakarry->moveSpeed, parakarry->yaw,
                            parakarry->collisionHeight, parakarry->collisionDiameter)
                    ) {
                        hitAbove = false;
                        x = parakarry->pos.x;
                        y = parakarry->pos.y + parakarry->collisionHeight / 2.0f;
                        z = parakarry->pos.z;
                        length = parakarry->collisionHeight / 2.0f;

                        halfCollisionHeight = length;
                        if (npc_raycast_up(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &length) && (length < halfCollisionHeight)) {
                            parakarry->pos.y =  y - parakarry->collisionHeight;
                            playerStatus->pos.y = parakarry->pos.y - 32.0f;
                            hitAbove = true;
                        }
                        x = playerStatus->pos.x;
                        y = playerStatus->pos.y + playerStatus->colliderHeight / 2.0f;
                        z = playerStatus->pos.z;
                        length = playerStatus->colliderHeight / 2.0f;

                        if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &length, parakarry->yaw, parakarry->collisionDiameter)) {
                            playerStatus->pos.y += (y - playerStatus->pos.y) / 4.0f;
                            parakarry->pos.y = playerStatus->pos.y + 32.0f;
                            y = parakarry->pos.y;
                            parakarry->pos.y = playerStatus->pos.y;
                            npc_surface_spawn_fx(parakarry, SURFACE_INTERACT_WALK);
                            parakarry->pos.y = y;

                            if (hitAbove) {
                                AbilityState = AIR_LIFT_DROP;
                                break;
                            }
                        }

                        if (phys_adjust_cam_on_landing() == LANDING_CAM_NEVER_ADJUST) {
                            gCameras[CAM_DEFAULT].moveFlags &= ~CAMERA_MOVE_NO_INTERP_Y;
                        }
                        gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
                        gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
                        gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;
                        if (!(parakarry->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD)) {
                            parakarry->duration++;
                            if (!(parakarry->planarFlyDist < 100.0f)) {
                                AbilityStateTime = 5;
                                AbilityState = AIR_LIFT_HOLD;
                            }
                            break;
                        }
                    }
                }
            }
            suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
            AbilityState = AIR_LIFT_DROP;
            break;
        case AIR_LIFT_HOLD:
            if (AbilityStateTime != 0) {
                AbilityStateTime--;
            } else {
                AbilityState = AIR_LIFT_DROP;
            }
            break;
    }

    if (AbilityState == AIR_LIFT_JUMP
     || AbilityState == AIR_LIFT_DROP
     || AbilityState == AIR_LIFT_CANCEL
    ) {
        parakarry->curAnim = ANIM_WorldParakarry_Idle;
        UsingAbility  = false;
        parakarry->jumpVel = 0.0f;
        parakarry->flags &= ~NPC_FLAG_JUMPING;
        parakarry->animationSpeed = 1.0f;
        partner_clear_player_tracking(parakarry);
        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
        enable_partner_ai();
        sfx_stop_sound(SOUND_PARAKARRY_FLAP);
        if (LockingPlayerInput) {
            enable_player_input();
        }
        if (PlayerCollisionDisabled) {
            enable_player_static_collisions();
        }
        if ((playerStatus->flags & PS_FLAG_HIT_FIRE)) {
            set_action_state(ACTION_STATE_HIT_LAVA);
        } else if (AbilityState == AIR_LIFT_JUMP) {
            start_bounce_b();
        } else if (AbilityState == AIR_LIFT_DROP) {
            start_falling();
            gravity_use_fall_parms();
            playerStatus->flags |= PS_FLAG_SCRIPTED_FALL;
        } else {
            set_action_state(ACTION_STATE_IDLE);
        }
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldParakarry_UseAbility = {
    Call(UseAbility)
    Return
    End
};

API_CALLABLE(PutAway) {
    Npc* parakarry = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(parakarry);
    }

    if (partner_put_away(parakarry)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldParakarry_PutAway = {
    Call(PutAway)
    Return
    End
};

void pre_battle(Npc* parakarry) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (UsingAbility) {
        if (PlayerCollisionDisabled) {
            enable_player_static_collisions();
        }

        if (LockingPlayerInput) {
            enable_player_input();
        }

        set_action_state(ACTION_STATE_IDLE);
        partnerStatus->npc = *parakarry;
        partnerStatus->shouldResumeAbility = true;
        partner_clear_player_tracking(parakarry);
    }

    partnerStatus->actingPartner = PARTNER_PARAKARRY;
}

void post_battle(Npc* parakarry) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (partnerStatus->shouldResumeAbility) {
        if (PlayerCollisionDisabled) {
            disable_player_static_collisions();
        }
        if (LockingPlayerInput) {
            disable_player_input();
        }

        set_action_state(ACTION_STATE_RIDE);
        *parakarry = partnerStatus->npc;
        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
        partner_clear_player_tracking(parakarry);
        partner_use_ability();
    }
}

OVL_DEF_PARTNER() = {
    .isFlying = true,
    .init = init,
    .takeOut = &EVS_WorldParakarry_TakeOut,
    .update = &EVS_WorldParakarry_Update,
    .useAbility = &EVS_WorldParakarry_UseAbility,
    .putAway = &EVS_WorldParakarry_PutAway,
    .idle = ANIM_WorldParakarry_Idle,
    .canPlayerOpenMenus = partner_is_idle,
    .preBattle = pre_battle,
    .postBattle = post_battle,
};
