#include "common.h"
#include "world/partners.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/player.h"
#include "effects.h"

s32 entity_try_partner_interaction_trigger(s32);
s32 test_item_entity_position(f32, f32, f32, f32);
void auto_collect_item_entity(s32);

BSS s32 ShellTossHoldTime;
BSS s32 TriggeredBattle;
BSS s32 PlayerWasFacingLeft;
BSS s32 D_802BEC5C;
BSS s32 ShellTossKickFalling;
BSS b32 LockingPlayerInput;
BSS s32 HeldItemIdx;
BSS s32 CollectingItem;
BSS f32 ShellTossPosX;
BSS f32 ShellTossPosY;
BSS f32 ShellTossPosZ;

enum {
    SHELL_TOSS_HITBOX_DISABLED      = 0,
    SHELL_TOSS_HITBOX_ENABLED       = 1,
    SHELL_TOSS_HITBOX_HIT_ENEMY     = 2,
};

s32 ShellTossHitboxState = SHELL_TOSS_HITBOX_DISABLED;

s32 lateral_hit_interactable_entity(Npc* npc) {
    if (NpcHitQueryColliderID < 0) {
        return false;
    }

    if (!(NpcHitQueryColliderID & COLLISION_WITH_ENTITY_BIT)) {
        return false;
    }

    return entity_try_partner_interaction_trigger(NpcHitQueryColliderID & ~COLLISION_WITH_ENTITY_BIT);
}

void vertical_hit_interactable_entity(Npc* kooper) {
    if (NpcHitQueryColliderID < 0) {
        return;
    }

    if (!(NpcHitQueryColliderID & COLLISION_WITH_ENTITY_BIT)) {
        return;
    }

    entity_try_partner_interaction_trigger(NpcHitQueryColliderID & ~COLLISION_WITH_ENTITY_BIT);
}

s32 check_for_item_collision(Npc* kooper) {
    HeldItemIdx = test_item_entity_position(kooper->pos.x, kooper->pos.y, kooper->pos.z, kooper->collisionDiameter);

    if (HeldItemIdx < 0) {
        return false;
    }

    CollectingItem = true;
    gOverrideFlags |= GLOBAL_OVERRIDES_40;
    set_item_entity_flags(HeldItemIdx, ITEM_ENTITY_FLAG_PARTNER_COLLECTING);
    return true;
}

void init(Npc* kooper) {
    kooper->collisionHeight = 37;
    kooper->collisionDiameter = 24;
    kooper->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    TriggeredBattle = false;
}

API_CALLABLE(TakeOut) {
    Npc* kooper = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(kooper);
    }

    if (partner_get_out(kooper)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldKooper_TakeOut = {
    Call(TakeOut)
    Return
    End
};

BSS TweesterPhysics TweesterPhysicsData;
TweesterPhysics* TweesterPhysicsPtr = &TweesterPhysicsData;

API_CALLABLE(Update) {
    PlayerData* playerData = &gPlayerData;
    Npc* kooper = script->owner2.npc;
    f32 sinAngle, cosAngle, liftoffVelocity;
    Entity* entity;

    if (isInitialCall) {
        partner_walking_enable(kooper, true);
        mem_clear(TweesterPhysicsPtr, sizeof(TweesterPhysics));
        TweesterTouchingPartner = nullptr;
    }

    playerData->partnerUsedTime[PARTNER_KOOPER]++;
    entity = TweesterTouchingPartner;

    if (entity == nullptr) {
        partner_walking_update_player_tracking(kooper);
        partner_walking_update_motion(kooper);
        return ApiStatus_BLOCK;
    }

    switch (TweesterPhysicsPtr->state) {
        case TWEESTER_PARTNER_INIT:
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_ATTRACT;
            TweesterPhysicsPtr->prevFlags = kooper->flags;
            TweesterPhysicsPtr->radius = fabsf(dist2D(kooper->pos.x, kooper->pos.z,
                                                     entity->pos.x, entity->pos.z));
            TweesterPhysicsPtr->angle = atan2(entity->pos.x, entity->pos.z, kooper->pos.x, kooper->pos.z);
            TweesterPhysicsPtr->angularVel = 6.0f;
            TweesterPhysicsPtr->liftoffVelPhase = 50.0f;
            TweesterPhysicsPtr->countdown = 120;
            kooper->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_FLYING;
            kooper->flags &= ~NPC_FLAG_GRAVITY;
        case TWEESTER_PARTNER_ATTRACT:
            sin_cos_rad(DEG_TO_RAD(TweesterPhysicsPtr->angle), &sinAngle, &cosAngle);

            kooper->pos.x = entity->pos.x + (sinAngle * TweesterPhysicsPtr->radius);
            kooper->pos.z = entity->pos.z - (cosAngle * TweesterPhysicsPtr->radius);

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
            kooper->pos.y += liftoffVelocity;

            kooper->renderYaw = clamp_angle(360.0f - TweesterPhysicsPtr->angle);
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
            kooper->flags = TweesterPhysicsPtr->prevFlags;
            TweesterPhysicsPtr->countdown = 30;
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_RELEASE;
            break;
        case TWEESTER_PARTNER_RELEASE:
            partner_walking_update_player_tracking(kooper);
            partner_walking_update_motion(kooper);

            TweesterPhysicsPtr->countdown--;
            if (TweesterPhysicsPtr->countdown == 0) {
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
                TweesterTouchingPartner = nullptr;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

void try_cancel_tweester(Npc* kooper) {
    if (TweesterTouchingPartner != nullptr) {
        TweesterTouchingPartner = nullptr;
        kooper->flags = TweesterPhysicsPtr->prevFlags;
        TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
        partner_clear_player_tracking(kooper);
    }
}

EvtScript EVS_WorldKooper_Update = {
    Call(Update)
    Return
    End
};

API_CALLABLE(UseAbility) {
    ItemEntity* heldItem;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* kooper = script->owner2.npc;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;
    f32 posX, posY, posZ, hitLength;
    f32 testLength;
    s32 actionState;
    f32 moveAngle;
    f32 angleToStartPos;

    #define USE_STATE functionTemp[0]
    enum {
        SHELL_TOSS_STATE_BEGIN      = 20,
        SHELL_TOSS_STATE_GATHER     = 21,
        SHELL_TOSS_STATE_JUMP       = 2,
        SHELL_TOSS_STATE_KICK       = 3,
        SHELL_TOSS_STATE_PICKUP     = 4,
        SHELL_TOSS_STATE_HOLD       = 5,
        SHELL_TOSS_STATE_RETURN     = 7,
        SHELL_TOSS_STATE_FINISH     = 0,
    };

    if (currentEncounter->battleTransitionState != BATTLE_TRANSITION_STATE_STARTED) {
        return ApiStatus_BLOCK;
    }

    if (isInitialCall) {
        try_cancel_tweester(kooper);
        if (playerStatus->animFlags & PA_FLAG_CHANGING_MAP) {
            return ApiStatus_DONE2;
        }

        if (!TriggeredBattle) {
            actionState = playerStatus->actionState;
            if (actionState == ACTION_STATE_IDLE
             || actionState == ACTION_STATE_WALK
             || actionState == ACTION_STATE_RUN
            ) {
                script->USE_STATE = SHELL_TOSS_STATE_BEGIN;
            } else {
                return ApiStatus_DONE2;
            }
        } else if (partnerStatus->partnerActionState == PARTNER_ACTION_NONE) {
            partnerStatus->partnerActionState = PARTNER_ACTION_KOOPER_GATHER;
            partnerStatus->actingPartner = PARTNER_KOOPER;
            script->USE_STATE = SHELL_TOSS_STATE_HOLD;
            kooper->curAnim = ANIM_WorldKooper_SpinShell;
            ShellTossHoldTime = 30;
        }
    }

    switch (script->USE_STATE) {
        case SHELL_TOSS_STATE_BEGIN:
            if (playerStatus->inputDisabledCount != 0
             || playerStatus->timeInAir != 0
             || !(kooper->flags & NPC_FLAG_GROUNDED)
            ) {
                return ApiStatus_DONE2;
            }

            disable_player_input();
            script->functionTemp[2] = playerStatus->inputDisabledCount;
            LockingPlayerInput = true;
            ShellTossHitboxState = SHELL_TOSS_HITBOX_DISABLED;
            CollectingItem = false;
            kooper->flags &= ~(NPC_FLAG_GRAVITY | NPC_FLAG_JUMPING | NPC_FLAG_FLYING);
            kooper->flags |= (NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION);
            partnerStatus->actingPartner = PARTNER_KOOPER;
            partnerStatus->partnerActionState = PARTNER_ACTION_KOOPER_GATHER;
            PlayerWasFacingLeft = partner_force_player_flip_done();
            enable_npc_blur(kooper);
            kooper->duration = 4;
            kooper->yaw = atan2(kooper->pos.x, kooper->pos.z,
                                playerStatus->pos.x, playerStatus->pos.z);
            script->USE_STATE++;
            break;

        case SHELL_TOSS_STATE_GATHER:
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
             || playerStatus->actionState == ACTION_STATE_HIT_LAVA
             || playerStatus->timeInAir != 0
            ) {
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                script->USE_STATE = SHELL_TOSS_STATE_FINISH;
                break;
            }

            suggest_player_anim_allow_backward(ANIM_Mario1_BeforeJump);
            kooper->moveToPos.x = ShellTossPosX = playerStatus->pos.x;
            kooper->moveToPos.y = ShellTossPosY = playerStatus->pos.y;
            kooper->moveToPos.z = ShellTossPosZ = playerStatus->pos.z;
            kooper->curAnim = ANIM_WorldKooper_Run;
            add_vec2D_polar(&kooper->moveToPos.x, &kooper->moveToPos.z,
                            playerStatus->colliderDiameter / 3, playerStatus->targetYaw);
            moveAngle = clamp_angle(playerStatus->targetYaw + (PlayerWasFacingLeft ? 90.0f : -90.0f));
            add_vec2D_polar(&kooper->moveToPos.x, &kooper->moveToPos.z,
                            playerStatus->colliderDiameter / 4, moveAngle);
            kooper->pos.x += (kooper->moveToPos.x - kooper->pos.x) / kooper->duration;
            kooper->pos.y += (kooper->moveToPos.y - kooper->pos.y) / kooper->duration;
            kooper->pos.z += (kooper->moveToPos.z - kooper->pos.z) / kooper->duration;

            kooper->duration--;
            if (kooper->duration != 0) {
                break;
            }

            disable_npc_blur(kooper);
            if (script->functionTemp[2] < playerStatus->inputDisabledCount) {
                if (!(playerStatus->animFlags & PA_FLAG_CHANGING_MAP)) {
                    suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                } else {
                    suggest_player_anim_allow_backward(ANIM_Mario1_Run);
                }
                script->USE_STATE = SHELL_TOSS_STATE_FINISH;
                break;
            }

            kooper->yaw = playerStatus->targetYaw;
            kooper->jumpVel = 18.0f;
            kooper->jumpScale = 3.0f;
            kooper->curAnim = ANIM_WorldKooper_EnterShell;
            kooper->collisionHeight = 12;

            kooper->moveToPos.y = playerStatus->pos.y;
            kooper->moveToPos.z = playerStatus->pos.y + playerStatus->colliderHeight / 3;
            playerStatus->flags |= PS_FLAG_JUMPING;
            gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_IGNORE_PLAYER_Y;

#if VERSION_PAL
            playerStatus->gravityIntegrator[0] = 0;
            playerStatus->gravityIntegrator[1] = 0;
            playerStatus->gravityIntegrator[2] = 0;
            playerStatus->gravityIntegrator[3] = 0;
#endif

            suggest_player_anim_allow_backward(ANIM_Mario1_Jump);
            ShellTossKickFalling = false;
            sfx_play_sound_at_npc(SOUND_QUICK_PLAYER_JUMP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
            script->USE_STATE = SHELL_TOSS_STATE_JUMP;
            // fallthrough

        case SHELL_TOSS_STATE_JUMP:
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
             || playerStatus->actionState == ACTION_STATE_HIT_LAVA
            ) {
                script->USE_STATE = SHELL_TOSS_STATE_FINISH;
                break;
            }

            kooper->jumpVel -= kooper->jumpScale;
            playerStatus->pos.y += kooper->jumpVel;
            if (kooper->jumpVel < 0.0f) {
                if (!ShellTossKickFalling) {
                    ShellTossKickFalling = true;
                    suggest_player_anim_allow_backward(ANIM_Mario1_Fall);
                }
            }

            posX = playerStatus->pos.x;
            posY = (playerStatus->pos.y + playerStatus->colliderHeight / 2) - kooper->jumpVel;
            posZ = playerStatus->pos.z;
            testLength = hitLength = playerStatus->colliderHeight / 2;

            if ((npc_raycast_up(COLLIDER_FLAG_IGNORE_PLAYER, &posX, &posY, &posZ, &hitLength)) && (hitLength < testLength)) {
                collisionStatus->curCeiling = NpcHitQueryColliderID;
                playerStatus->pos.y = posY - playerStatus->colliderHeight;
                vertical_hit_interactable_entity(kooper);
            }

            if (!(kooper->jumpVel > 0.0f) && (playerStatus->pos.y < kooper->moveToPos.z)) {
                D_802BEC5C = 0;
                kooper->flags &= ~NPC_FLAG_IGNORE_CHAR_COLLISION;
                partnerStatus->actingPartner = PARTNER_KOOPER;
                partnerStatus->partnerActionState = PARTNER_ACTION_KOOPER_TOSS;
                kooper->rot.z = 0.0f;
                kooper->planarFlyDist = 0.0f;
                kooper->moveSpeed = 8.0f;
                kooper->curAnim = ANIM_WorldKooper_SpinShell;
                ShellTossHitboxState = SHELL_TOSS_HITBOX_ENABLED;
                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                        sin_deg(playerStatus->targetYaw), -1.0f, -cos_deg(playerStatus->targetYaw), 3);
                start_bounce_b();

                if (LockingPlayerInput) {
                    enable_player_input();
                    LockingPlayerInput = false;
                }

                script->USE_STATE = SHELL_TOSS_STATE_KICK;
                ShellTossKickFalling = false;
                gCameras[CAM_DEFAULT].moveFlags |= CAMERA_MOVE_IGNORE_PLAYER_Y;
                sfx_play_sound_at_npc(SOUND_KOOPER_SHELL_KICK, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                sfx_play_sound_at_npc(SOUND_KOOPER_SHELL_SWIRL, SOUND_SPACE_DEFAULT, NPC_PARTNER);
            }
            break;

        case SHELL_TOSS_STATE_KICK:
            if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
             || playerStatus->actionState == ACTION_STATE_KNOCKBACK
            ) {
                script->USE_STATE = SHELL_TOSS_STATE_FINISH;
                break;
            }

            // check the forward collision for kooper
            #define TEST_COLLISION_AT_ANGLE(testAngle) \
                ( \
                posX = kooper->pos.x, \
                posY = kooper->pos.y, \
                posZ = kooper->pos.z, \
                npc_test_move_taller_with_slipping(COLLIDER_FLAG_IGNORE_SHELL, \
                    &posX, &posY, &posZ, kooper->moveSpeed, testAngle,  \
                    kooper->collisionHeight, kooper->collisionDiameter / 2) \
                )

            if (TEST_COLLISION_AT_ANGLE(kooper->yaw - 20.0f)) {
                if (!lateral_hit_interactable_entity(kooper)) {
                    sfx_play_sound_at_npc(SOUND_IMMUNE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                }

                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                        sin_deg(kooper->yaw), -1.0f, -cos_deg(kooper->yaw), 1);
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
                break;
            }

            if (TEST_COLLISION_AT_ANGLE(kooper->yaw + 20.0f)) {
                if (!lateral_hit_interactable_entity(kooper)) {
                    sfx_play_sound_at_npc(SOUND_IMMUNE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                }

                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                        sin_deg(kooper->yaw), -1.0f, -cos_deg(kooper->yaw), 1);
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
                break;
            }

             if (TEST_COLLISION_AT_ANGLE(kooper->yaw)) {
                if (!lateral_hit_interactable_entity(kooper)) {
                    sfx_play_sound_at_npc(SOUND_IMMUNE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                }

                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                        sin_deg(kooper->yaw), -1.0f, -cos_deg(kooper->yaw), 1);
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
                break;
            }

            kooper->pos.x = posX;
            kooper->pos.y = posY;
            kooper->pos.z = posZ;
            kooper->planarFlyDist += kooper->moveSpeed;
            npc_surface_spawn_fx(kooper, SURFACE_INTERACT_RUN);

            kooper->moveSpeed += 2.0;
            if (kooper->moveSpeed > 14.0) {
                kooper->moveSpeed = 14.0f;
            }

            if (!(npc_try_snap_to_ground(kooper, 6.0f) || playerStatus->flags & (PS_FLAG_JUMPING | PS_FLAG_FALLING))) {
                kooper->pos.y += (playerStatus->pos.y - kooper->pos.y) / 10.0f;
            }

            npc_do_other_npc_collision(kooper);

            if ((kooper->flags & NPC_FLAG_COLLIDING_WITH_NPC)) {
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
                kooper->moveSpeed = 0.0f;
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                break;
            }

            if (check_for_item_collision(kooper)) {
                sfx_play_sound_at_npc(SOUND_KOOPER_PICKUP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                    sin_deg(kooper->yaw), -1.0f, -cos_deg(kooper->yaw), 1);
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                script->USE_STATE = SHELL_TOSS_STATE_PICKUP;
                ShellTossHoldTime = 8;
                kooper->moveSpeed -= 4.0;
                if (kooper->moveSpeed < 0.01) {
                    kooper->moveSpeed = 0.01f;
                    kooper->planarFlyDist += 1.0;
                }
            } else if (ShellTossHitboxState == SHELL_TOSS_HITBOX_HIT_ENEMY) {
                sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                script->USE_STATE = SHELL_TOSS_STATE_HOLD;
                ShellTossHoldTime = 30;
                kooper->moveSpeed = 0.0f;
            } else {
                if (kooper->planarFlyDist > 140.0f) {
                    script->USE_STATE = SHELL_TOSS_STATE_RETURN;
                    kooper->moveSpeed = 0.0f;
                    sfx_play_sound_at_npc(SOUND_NONE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                } else if (kooper->planarFlyDist > 105.0f) {
                    kooper->moveSpeed -= 4.0;
                    if (kooper->moveSpeed < 0.01) {
                        kooper->moveSpeed = 0.01f;
                        kooper->planarFlyDist += 1.0;
                    }
                }
            }
            break;

        case SHELL_TOSS_STATE_PICKUP:
            posX = kooper->pos.x;
            posY = kooper->pos.y;
            posZ = kooper->pos.z;

            npc_test_move_taller_with_slipping(COLLIDER_FLAG_IGNORE_SHELL,
                &posX, &posY, &posZ, kooper->moveSpeed, kooper->yaw,
                kooper->collisionHeight, ( kooper->collisionDiameter / 2));

            kooper->pos.x = posX;
            kooper->pos.y = posY;
            kooper->pos.z = posZ;

            kooper->planarFlyDist += kooper->moveSpeed;
            npc_surface_spawn_fx(kooper, SURFACE_INTERACT_RUN);
            kooper->moveSpeed -= 6.0;

            if (kooper->moveSpeed < 0.01) {
                kooper->moveSpeed = 0.01f;
                kooper->planarFlyDist += 1.0;
            }

            if (ShellTossHoldTime == 0) {
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
            }
            ShellTossHoldTime--;
            break;

        case SHELL_TOSS_STATE_HOLD:
            if (ShellTossHoldTime != 0) {
                ShellTossHoldTime--;
            } else {
                script->USE_STATE = SHELL_TOSS_STATE_RETURN;
            }
            break;
        }

    if (script->USE_STATE == SHELL_TOSS_STATE_RETURN) {
        kooper->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
        if (playerStatus->actionState == ACTION_STATE_HIT_FIRE
            || playerStatus->actionState == ACTION_STATE_KNOCKBACK
        ) {
            script->USE_STATE = SHELL_TOSS_STATE_FINISH;
        } else {
            angleToStartPos = atan2(ShellTossPosX, ShellTossPosZ, kooper->pos.x, kooper->pos.z);
            kooper->yaw = angleToStartPos + get_clamped_angle_diff(kooper->yaw, angleToStartPos) * 0.125f;
            npc_move_heading(kooper, -kooper->moveSpeed, kooper->yaw);
            kooper->planarFlyDist -= kooper->moveSpeed;
            npc_surface_spawn_fx(kooper, SURFACE_INTERACT_RUN);
            kooper->moveSpeed += 4.0/3.0;

            if (kooper->moveSpeed > 14.0) {
                kooper->moveSpeed = 14.0f;
            }

            if (npc_try_snap_to_ground(kooper, 6.0f) == 0) {
                kooper->pos.y += (playerStatus->pos.y - kooper->pos.y) / 10.0f;
            }

            posX = kooper->pos.x;
            posY = kooper->pos.y;
            posZ = kooper->pos.z;

            if (npc_test_move_taller_with_slipping(COLLIDER_FLAG_IGNORE_SHELL,
                &posX, &posY, &posZ, kooper->moveSpeed, clamp_angle(kooper->yaw + 180.0f),
                kooper->collisionHeight, kooper->collisionDiameter)
            ) {
                kooper->pos.x = posX;
                kooper->pos.y = posY;
                kooper->pos.z = posZ;
                sfx_play_sound_at_npc(SOUND_IMMUNE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                testLength = sin_deg(kooper->yaw + 180.0f);
                fx_damage_stars(FX_DAMAGE_STARS_3, kooper->pos.x, kooper->pos.y + kooper->collisionHeight, kooper->pos.z,
                        testLength, -1.0f, -cos_deg(kooper->yaw + 180.0f), 1);
                script->USE_STATE = SHELL_TOSS_STATE_FINISH;
            } else {
                if (CollectingItem) {
                    heldItem = get_item_entity(HeldItemIdx);
                    posX = kooper->pos.x;
                    posY = kooper->pos.y + 8.0f;
                    posZ = kooper->pos.z;

                    moveAngle = clamp_angle(playerStatus->targetYaw - (PlayerWasFacingLeft ? 90.0f : -90.0f));

                    add_vec2D_polar(&posX, &posZ, 4.0f, moveAngle);
                    heldItem->pos.x = posX;
                    heldItem->pos.y = posY;
                    heldItem->pos.z = posZ;
                }

                if (kooper->planarFlyDist + 15.0f < kooper->moveSpeed) {
                    script->USE_STATE = SHELL_TOSS_STATE_FINISH;
                } else if (kooper->planarFlyDist + 15.0f < 35.0f) {
                    kooper->moveSpeed -= 4.0;
                    if (kooper->moveSpeed < 4.0) {
                        kooper->moveSpeed = 4.0;
                    }
                }
            }
        }
    }

    if (script->USE_STATE == SHELL_TOSS_STATE_FINISH) {
        if (LockingPlayerInput) {
            enable_player_input();
            LockingPlayerInput = false;
        }

        ShellTossHitboxState = SHELL_TOSS_HITBOX_DISABLED;
        kooper->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
        kooper->flags &= ~(NPC_FLAG_JUMPING | NPC_FLAG_IGNORE_WORLD_COLLISION);
        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
        kooper->jumpVel = 0.0f;
        kooper->collisionHeight = 24;
        kooper->curAnim = ANIM_WorldKooper_Walk;
        sfx_stop_sound(SOUND_KOOPER_SHELL_SWIRL);
        disable_npc_blur(kooper);

        if (CollectingItem) {
            auto_collect_item_entity(HeldItemIdx);
            CollectingItem = false;
        }

        TriggeredBattle = false;
        partner_clear_player_tracking(kooper);
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldKooper_UseAbility = {
    Call(UseAbility)
    Return
    End
};

API_CALLABLE(PutAway) {
    Npc* kooper = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(kooper);
    }

    if (partner_put_away(kooper)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldKooper_PutAway = {
    Call(PutAway)
    Return
    End
};

s32 test_first_strike(Npc* kooper, Npc* enemy) {
    f32 xTemp, yTemp, zTemp;
    f32 enemyX, enemyY, enemyZ;
    f32 kooperX;
    f32 kooperZ;
    f32 enemyCollHeight;
    f32 kooperY;
    f32 kooperCollHeight;
    f32 enemyCollRadius;
    f32 kooperCollRadius;
    f32 angleToEnemy;
    f32 distToEnemy;

    if (ShellTossHitboxState != SHELL_TOSS_HITBOX_DISABLED) {
        enemyX = enemy->pos.x;
        enemyY = enemy->pos.y;
        enemyZ = enemy->pos.z;

        kooperX = kooper->pos.x;
        kooperY = kooper->pos.y;
        kooperZ = kooper->pos.z;

        enemyCollHeight = enemy->collisionHeight;
        enemyCollRadius = enemy->collisionDiameter * 0.55;

        kooperCollHeight = kooper->collisionHeight;
        kooperCollRadius = kooper->collisionDiameter * 0.8;

        angleToEnemy = atan2(enemyX, enemyZ, kooperX, kooperZ);
        distToEnemy = dist2D(enemyX, enemyZ, kooperX, kooperZ);

        xTemp = kooper->pos.x;
        yTemp = kooper->pos.y;
        zTemp = kooper->pos.z;

        if (npc_test_move_taller_with_slipping(0, &xTemp, &yTemp, &zTemp, distToEnemy, angleToEnemy,
            kooperCollHeight, kooperCollRadius + enemyCollRadius)
        ) {
            return false;
        }

        if (kooperY > enemyY + enemyCollHeight) {
            return false;
        }

        if (enemyY > kooperY + kooperCollHeight) {
            return false;
        }

        kooperX = enemyX - kooperX;
        kooperZ = enemyZ - kooperZ;
        distToEnemy = SQ(kooperX) + SQ(kooperZ);

        if (!(SQ(kooperCollRadius) + SQ(enemyCollRadius) <= distToEnemy)) {
            ShellTossHitboxState = SHELL_TOSS_HITBOX_HIT_ENEMY;
            return true;
        }
    }
    return false;
}

void pre_battle(Npc* kooper) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    TriggeredBattle = false;

    if (partnerStatus->partnerActionState != PARTNER_ACTION_NONE) {
        if (partnerStatus->partnerActionState == PARTNER_ACTION_KOOPER_TOSS) {
            TriggeredBattle = true;
        }

        if (LockingPlayerInput) {
            enable_player_input();
            LockingPlayerInput = false;
        }

        ShellTossHitboxState = SHELL_TOSS_HITBOX_DISABLED;
        playerStatus->flags &= ~PS_FLAG_JUMPING;

        kooper->jumpVel = 0.0f;
        kooper->flags &= ~NPC_FLAG_JUMPING;
        kooper->flags &= ~NPC_FLAG_IGNORE_WORLD_COLLISION;

        sfx_stop_sound(SOUND_KOOPER_SHELL_SWIRL);
        set_action_state(ACTION_STATE_IDLE);
        partner_clear_player_tracking(kooper);
        disable_npc_blur(kooper);

        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
    }
}

void post_battle(Npc* npc) {
    if (TriggeredBattle) {
        partner_clear_player_tracking(npc);
        partner_use_ability();
    }
}

OVL_DEF_PARTNER() = {
    .isFlying = false,
    .init = init,
    .takeOut = &EVS_WorldKooper_TakeOut,
    .update = &EVS_WorldKooper_Update,
    .useAbility = &EVS_WorldKooper_UseAbility,
    .putAway = &EVS_WorldKooper_PutAway,
    .idle = ANIM_WorldKooper_Idle,
    .testFirstStrike = test_first_strike,
    .canUseAbility = partner_is_idle,
    .canPlayerOpenMenus = partner_is_idle,
    .preBattle = pre_battle,
    .postBattle = post_battle,
};
