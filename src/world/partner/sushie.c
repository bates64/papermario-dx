#include "common.h"
#include "world/partners.h"
#include "npc.h"
#include "effects.h"
#include "sprite/npc/WorldSushie.h"
#include "sprite.h"
#include "sprite/player.h"

BSS f32 WaterSurfaceY;
BSS s32 DiveState;
BSS s32 DiveTime;
BSS b32 IsRiding;
BSS s32 TouchDockTime;
BSS b32 IsUnderwater;
BSS f32 InertialMoveSpeed;
BSS f32 InertialMoveAngle;
BSS f32 UnusedMoveX;
BSS f32 UnusedMoveZ;
BSS f32 ResurfaceVelY;
BSS TweesterPhysics TweesterPhysicsData;

enum {
    DIVE_STATE_NONE         = 0,
    DIVE_STATE_DELAY        = 1,
    DIVE_STATE_DIVING       = 2,
    DIVE_STATE_SURFACING    = 3,
};

f32 InputStickX = 0.0f;
f32 InputStickY = 0.0f;
f32 InertialStickX = 0.0f;
f32 InertialStickY = 0.0f;

void try_cancel_tweester(Npc* sushie);

void sync_player_position(void) {
    Npc* partnerNPC = get_npc_unsafe(NPC_PARTNER);
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[CAM_DEFAULT];
    s32 angleOffset;

    playerStatus->pos.x = partnerNPC->pos.x;
    playerStatus->pos.y = partnerNPC->pos.y + 16.0f;
    playerStatus->pos.z = partnerNPC->pos.z;
    playerStatus->targetYaw = partnerNPC->yaw;

    if (playerStatus->spriteFacingAngle < 90.0f || playerStatus->spriteFacingAngle > 270.0f) {
        angleOffset = -8;
    } else {
        angleOffset = 8;
    }

    playerStatus->pos.z -= cos_rad(DEG_TO_RAD(
        camera->curYaw + playerStatus->spriteFacingAngle - 90.0f + angleOffset)) * -4.0f;
}

void get_movement_from_input(f32* outAngle, f32* outSpeed) {
    f32 moveAngle;
    f32 moveSpeed;
    f32 stickY = gPartnerStatus.stickY;
    f32 stickX = gPartnerStatus.stickX;

    InputStickX = stickX;
    InputStickY = stickY;
    moveAngle = clamp_angle(atan2(0.0f, 0.0f, stickX, -stickY) + gCameras[CAM_DEFAULT].curYaw);
    moveSpeed = 0.0f;

    if (dist2D(0.0f, 0.0f, InputStickX, -InputStickY) >= 1.0) {
        if (SQ(InputStickX) + SQ(InputStickY) > SQ(55)) {
            if (DiveState != DIVE_STATE_NONE) {
                moveSpeed = 2.0f;
            } else {
                moveSpeed = 4.0f;
            }
        } else {
            moveSpeed = 2.0f;
        }
    }

    *outAngle = moveAngle;
    *outSpeed = moveSpeed;
}

void test_for_water_level(s32 ignoreFlags, f32 posX, f32 posY, f32 posZ, f32 yaw, f32 radius) {
    CollisionStatus* collisionStatus = &gCollisionStatus;
    f32 depth;

    posY += 100.0f;
    depth = 200.0f;

    if (!npc_raycast_down_around(ignoreFlags, &posX, &posY, &posZ, &depth, yaw, radius)) {
        collisionStatus->curFloor = NO_COLLIDER;
    } else {
        collisionStatus->curFloor = NpcHitQueryColliderID;
        WaterSurfaceY = posY;
    }
}

void update_riding_physics(Npc* sushie) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;
    f32 moveSpeedDamping;
    f32 moveAngle, moveSpeed;
    f32 sinAngle, cosAngle;
    f32 x, y, z;
    f32 depth;

    // PART 1:
    // determine movement speed and direction from input and inertia

     get_movement_from_input(&moveAngle, &moveSpeed);

    if (DiveState != DIVE_STATE_NONE) {
        moveSpeedDamping = 80.0f;
    } else {
        moveSpeedDamping = 32.0f;
    }

    if (moveSpeed != 0.0f) {
        f32 changeDirDamping =  8.0f;
        f32 sameDirDamping   = 32.0f;

        if (InputStickX * InertialStickX > 0.0f) {
            InertialStickX += InputStickX / sameDirDamping;
        } else {
            InertialStickX += InputStickX / changeDirDamping;
        }
        if (InputStickX > 0.0f) {
            if (InputStickX < InertialStickX) {
                InertialStickX = InputStickX;
            }
        } else {
            if (InertialStickX < InputStickX) {
                InertialStickX = InputStickX;
            }
        }

        if (InputStickY * InertialStickY > 0.0f) {
            InertialStickY += InputStickY / sameDirDamping;
        } else {
            InertialStickY += InputStickY / changeDirDamping;
        }
        if (InputStickY > 0.0f) {
            if (InputStickY < InertialStickY) {
                InertialStickY = InputStickY;
            }
        } else {
            if (InertialStickY < InputStickY) {
                InertialStickY = InputStickY;
            }
        }

        moveAngle = clamp_angle(atan2(0.0f, 0.0f, InertialStickX, -InertialStickY) + gCameras[CAM_DEFAULT].curYaw);
        if (InertialMoveSpeed <= moveSpeed) {
            InertialMoveSpeed += (moveSpeed - InertialMoveSpeed) / moveSpeedDamping;
            if (InertialMoveSpeed > moveSpeed) {
                InertialMoveSpeed = moveSpeed;
            }
        } else {
            InertialMoveSpeed += (moveSpeed - InertialMoveSpeed) / moveSpeedDamping;
        }
        moveSpeed = InertialMoveSpeed;
        InertialMoveAngle = moveAngle;
        sin_cos_rad(DEG_TO_RAD(moveAngle), &sinAngle, &cosAngle);
        UnusedMoveX += ( moveSpeed * sinAngle) / moveSpeedDamping;
        UnusedMoveZ += (-moveSpeed * cosAngle) / moveSpeedDamping;
    } else {
        InertialMoveSpeed -= 0.15;
        if (InertialMoveSpeed < 0.0f) {
            InertialMoveSpeed = 0.0f;
            InertialStickY = 0.0f;
            InertialStickX = 0.0f;
        }
        moveSpeed = InertialMoveSpeed;
        moveAngle = InertialMoveAngle;
        sin_cos_rad(DEG_TO_RAD(InertialMoveAngle), &sinAngle, &cosAngle);
        UnusedMoveX =  moveSpeed * sinAngle;
        UnusedMoveZ = -moveSpeed * cosAngle;
    }

    // PART 2:
    // apply movement speed and direction to sushie

    sushie->moveSpeed = moveSpeed;
    if (moveSpeed != 0.0f) {
        sushie->yaw = moveAngle;
        x = sushie->pos.x;
        z = sushie->pos.z;
        y = sushie->moveToPos.y + -6.0f;
        depth = (sushie->collisionHeight * 0.5f) + (playerStatus->colliderHeight * 0.8f);
        if (npc_test_move_taller_with_slipping(sushie->collisionChannel, &x, &y, &z,
                sushie->moveSpeed, moveAngle, depth, sushie->collisionDiameter))
        {
            collisionStatus->pushingAgainstWall = NpcHitQueryColliderID;
            if ((get_collider_flags(NpcHitQueryColliderID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK) == SURFACE_TYPE_DOCK_WALL) {
                TouchDockTime++;
            } else {
                TouchDockTime = 0;
            }
            sushie->pos.x += (x - sushie->pos.x) * 0.5f;
            sushie->pos.z += (z - sushie->pos.z) * 0.5f;
        } else {
            npc_move_heading(sushie, moveSpeed, moveAngle);
            collisionStatus->pushingAgainstWall = NO_COLLIDER;
        }
        moveSpeed = 2.0f;
        moveAngle = clamp_angle(sushie->yaw - 30.0f);
        x = sushie->pos.x;
        z = sushie->pos.z;
        y = sushie->moveToPos.y + -6.0f;
        depth = (sushie->collisionHeight * 0.5f) + (playerStatus->colliderHeight * 0.8f);
        if (npc_test_move_taller_with_slipping(sushie->collisionChannel, &x, &y, &z,
                moveSpeed, moveAngle, depth, sushie->collisionDiameter))
        {
            sushie->pos.x += (x - sushie->pos.x) / 5.0f;
            sushie->pos.z += (z - sushie->pos.z) / 5.0f;
        }
        moveAngle = clamp_angle(sushie->yaw + 30.0f);
        x = sushie->pos.x;
        z = sushie->pos.z;
        y = sushie->moveToPos.y + -6.0f;
        depth = (sushie->collisionHeight * 0.5f) + (playerStatus->colliderHeight * 0.8f);
        if (npc_test_move_taller_with_slipping(sushie->collisionChannel, &x, &y, &z,
                moveSpeed, moveAngle, depth, sushie->collisionDiameter))
        {
            sushie->pos.x += (x - sushie->pos.x) / 5.0f;
            sushie->pos.z += (z - sushie->pos.z) / 5.0f;
        }
    }

    // PART 3:
    // update diving state

    if (DiveState == DIVE_STATE_NONE) {
        test_for_water_level(sushie->collisionChannel, sushie->pos.x, sushie->pos.y, sushie->pos.z,
                sushie->yaw, sushie->collisionDiameter * 0.5f);
        if (DiveState == DIVE_STATE_NONE) {
            sushie->moveSpeed = 3.0f;
            sushie->moveToPos.y = WaterSurfaceY - (sushie->collisionHeight * 0.5f);
            DiveTime = 0;
            if (partnerStatus->pressedButtons & BUTTON_C_DOWN) {
                DiveState = DIVE_STATE_DELAY;
                sushie->moveSpeed = 2.0f;
            } else {
                return;
            }
        }
    }
    if (DiveState == DIVE_STATE_DELAY) {
        if ((partnerStatus->curButtons & BUTTON_C_DOWN) && DiveTime == 0) {
            DiveState = DIVE_STATE_DIVING;
        }
    }
    DiveTime++;
    if (DiveState == DIVE_STATE_DIVING) {
        x = sushie->pos.x;
        y = sushie->pos.y;
        z = sushie->pos.z;
        depth = sushie->collisionHeight;
        if (npc_raycast_down_around(sushie->collisionChannel, &x, &y, &z, &depth, sushie->yaw, sushie->collisionDiameter)) {
            moveSpeedDamping = ((WaterSurfaceY - (playerStatus->colliderHeight * 2)) - sushie->moveToPos.y) * 0.1f;
            sushie->moveToPos.y += moveSpeedDamping;
            if (sushie->moveToPos.y < y + 5.0f) {
                sushie->moveToPos.y = y + 5.0f;
            }
        } else {
            moveSpeedDamping = ((WaterSurfaceY - (playerStatus->colliderHeight * 2)) - sushie->moveToPos.y) * 0.1f;
            sushie->moveToPos.y += moveSpeedDamping;
        }
        if (DiveTime % 6 == 0) {
            fx_rising_bubble(0, sushie->pos.x, sushie->moveToPos.y + (sushie->collisionHeight * 0.5f), sushie->pos.z,
                             (WaterSurfaceY - sushie->moveToPos.y) - (sushie->collisionHeight * 0.5f));
        }
        if (DiveTime == 1) {
            suggest_player_anim_always_forward(ANIM_MarioW2_DiveSushie);
            sushie->curAnim = ANIM_WorldSushie_Ride;
        }
        if (!IsUnderwater && (playerStatus->pos.y + (playerStatus->colliderHeight * 0.5f) < WaterSurfaceY)) {
            IsUnderwater = true;
            playerStatus->renderMode = RENDER_MODE_ALPHATEST;
            set_player_imgfx_all(playerStatus->trueAnimation, IMGFX_SET_WAVY, 2, 0, 0, 0, 0);
            npc_set_imgfx_params(sushie, IMGFX_SET_WAVY, 2, 0, 0, 0, 0);
        }
        if (DiveTime >= 10) {
            if (!(partnerStatus->curButtons & BUTTON_C_DOWN) || DiveTime >= 30) {
                sushie->curAnim = ANIM_WorldSushie_Rise;
                sfx_play_sound_at_npc(SOUND_SUSHIE_DIVE | SOUND_ID_TRIGGER_CHANGE_SOUND, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                DiveState = DIVE_STATE_SURFACING;
            }
        }
    }

    x = sushie->pos.x;
    y = sushie->moveToPos.y;
    z = sushie->pos.z;
    depth = (sushie->collisionHeight * 0.5f) + playerStatus->colliderHeight;
    if (npc_raycast_up_corners(sushie->collisionChannel, &x, &y, &z, &depth, sushie->yaw, sushie->collisionDiameter * 0.3f) > NO_COLLIDER) {
#if VERSION_JP
        sushie->moveToPos.y = y;
#else
        sushie->moveToPos.y += (((sushie->moveToPos.y - y) + depth) - ((sushie->collisionHeight * 0.5f) + playerStatus->colliderHeight)) * 0.2f;
#endif
        if (DiveTime % 9 == 0) {
            fx_rising_bubble(0, sushie->pos.x, sushie->moveToPos.y + (sushie->collisionHeight * 0.5f), sushie->pos.z,
                (WaterSurfaceY - sushie->moveToPos.y) - (sushie->collisionHeight * 0.5f));
        }
    } else if (DiveState == DIVE_STATE_SURFACING) {
        ResurfaceVelY += 0.14;
        if (ResurfaceVelY > 1.8) {
            ResurfaceVelY = 1.8f;
        }
        sushie->moveToPos.y += ResurfaceVelY;
        if (DiveTime % 9 == 0) {
            fx_rising_bubble(0, sushie->pos.x, sushie->moveToPos.y + sushie->collisionHeight * 0.5f, sushie->pos.z,
                (WaterSurfaceY - sushie->moveToPos.y) - sushie->collisionHeight * 0.5f);
        }
        if ((WaterSurfaceY - sushie->moveToPos.y) - (sushie->collisionHeight * 0.5f) <= 0.0f) {
            if (IsUnderwater) {
                IsUnderwater = false;
                set_player_imgfx_all(ANIM_Mario1_Idle, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                npc_set_imgfx_params(sushie, IMGFX_CLEAR, 0, 0, 0, 0, 0);
            }
            DiveState = DIVE_STATE_NONE;
            sushie->curAnim = ANIM_WorldSushie_Ride;
            sushie->moveToPos.y = WaterSurfaceY - (sushie->collisionHeight * 0.5f);
            suggest_player_anim_always_forward(ANIM_MarioW2_RideSushie);
        }
    }
}

HitID test_ray_to_wall_center(s32 unused, f32* x, f32* y, f32* z, f32 length, f32 radius, f32* yaw) {
    f32 sinAngle, cosAngle, totalLength;
    f32 hitX, hitY, hitZ;
    f32 hitNx, hitNy, hitNz;
    s32 hitID;

    sin_cos_rad(DEG_TO_RAD(*yaw), &sinAngle, &cosAngle);
    cosAngle = -cosAngle;
    totalLength = radius + length;
    hitID = test_ray_colliders(COLLIDER_FLAG_IGNORE_PLAYER, *x, *y, *z, sinAngle, 0.0f, cosAngle,
        &hitX, &hitY, &hitZ, &totalLength, &hitNx, &hitNy, &hitNz);

    if (hitID > NO_COLLIDER) {
        *yaw = atan2(0.0f, 0.0f, hitNx, hitNz);
    }

    return hitID;
}

API_CALLABLE(UseAbility) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerData* playerData = &gPlayerData;
    CollisionStatus* collisionStatus = &gCollisionStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    Npc* sushie = script->owner2.npc;
    s32 surfaceType;
    f32 x, y, z, dist;
    f32 angle, speed;
    f32 sinAngle, cosAngle;
    s32 collider = NO_COLLIDER;

    #define USE_STATE functionTemp[0]
    enum {
        SWIM_STATE_INIT         = 0,
        SWIM_STATE_BEGIN        = 20,
        SWIM_STATE_ENTER_WATER  = 21,
        SWIM_STATE_EMBARK_1     = 22,
        SWIM_STATE_EMBARK_2     = 23,
        SWIM_STATE_EMBARK_3     = 24,
        SWIM_STATE_EMBARK_4     = 25,
        SWIM_STATE_RIDING       = 1,
        SWIM_STATE_DISEMBARK_1  = 3,
        SWIM_STATE_DISEMBARK_2  = 4,
        SWIM_STATE_DISEMBARK_3  = 5,
        SWIM_STATE_EXIT_WATER   = 10,
    };

    if (isInitialCall) {
        try_cancel_tweester(sushie);
        InertialMoveAngle = 0.0f;
        InertialMoveSpeed = 0.0f;
        UnusedMoveX = 0.0f;
        UnusedMoveZ = 0.0f;
        ResurfaceVelY = 0.0f;
        script->USE_STATE = SWIM_STATE_INIT;
    }
    playerData->partnerUsedTime[PARTNER_SUSHIE]++;
    playerStatus->animFlags &= ~PA_FLAG_RIDING_PARTNER;

    switch (script->USE_STATE) {
        case SWIM_STATE_INIT:
            if (!gGameStatusPtr->keepUsingPartnerOnMapChange) {
                // are we colliding with a solid (non-entity) wall?
                collider = collisionStatus->curWall;
                if (collider <= NO_COLLIDER || collider & COLLISION_WITH_ENTITY_BIT) {
                    return ApiStatus_DONE1;
                }
                // is it a dock wall
                collider = get_collider_flags(collider) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
                if (collider != SURFACE_TYPE_DOCK_WALL) {
                    return ApiStatus_DONE1;
                }
                script->USE_STATE = SWIM_STATE_BEGIN;
            } else {
                // resume riding state from previous map
                sushie->moveToPos.y = sushie->pos.y;
                playerStatus->pos.y = sushie->moveToPos.y + 16.0f;
                IsRiding = true;
                sushie->flags |= NPC_FLAG_FLYING;
                sushie->flags &= ~NPC_FLAG_GRAVITY;
                sushie->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
                suggest_player_anim_always_forward(ANIM_MarioW2_RideSushie);
                disable_player_shadow();
                disable_npc_shadow(sushie);
                npc_set_imgfx_params(sushie, IMGFX_SET_WAVY, 2, 0, 0, 0, 0);
                sushie->curAnim = ANIM_WorldSushie_Ride;
                sushie->moveSpeed = playerStatus->runSpeed;
                sushie->jumpScale = 0.0f;
                partnerStatus->partnerActionState = PARTNER_ACTION_USE;
                gGameStatusPtr->keepUsingPartnerOnMapChange = false;
                partnerStatus->actingPartner = PARTNER_SUSHIE;
                DiveState = DIVE_STATE_NONE;
                DiveTime = 0;
                script->functionTemp[2] = 0;
                script->USE_STATE = SWIM_STATE_RIDING;
            }
            break;

        case SWIM_STATE_BEGIN:
            if (collisionStatus->curWall <= NO_COLLIDER) {
                return ApiStatus_DONE1;
            }
            // check for obstructions between player and center of current wall
            get_collider_center(collisionStatus->curWall, &x, &y, &z);
            angle = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
            x = playerStatus->pos.x;
            y = playerStatus->pos.y;
            z = playerStatus->pos.z;
            collider = test_ray_to_wall_center(0, &x, &y, &z,
                    playerStatus->colliderDiameter * 0.5f, 2.0f * playerStatus->colliderDiameter, &angle);
            // check surface type for wall
            surfaceType = SURFACE_TYPE_INVALID;
            if (collider > NO_COLLIDER) {
                surfaceType = get_collider_flags(collider) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
            }
            if (surfaceType != SURFACE_TYPE_DOCK_WALL) {
                return ApiStatus_DONE1;
            }

            IsRiding = true;
            set_action_state(ACTION_STATE_RIDE);
            disable_player_static_collisions();
            disable_player_input();
            sushie->collisionChannel = COLLIDER_FLAG_DOCK_WALL;
            sushie->moveToPos.x = playerStatus->pos.x;
            sushie->moveToPos.y = playerStatus->pos.y;
            sushie->moveToPos.z = playerStatus->pos.z;
            sushie->yaw = angle;
            playerStatus->targetYaw = angle;
            sushie->renderYaw = 90.0f;
            add_vec2D_polar(&sushie->moveToPos.x, &sushie->moveToPos.z, 40.0f, sushie->yaw);
            x = sushie->moveToPos.x;
            y = sushie->moveToPos.y;
            z = sushie->moveToPos.z;
            dist = 100.0f;
            collider = npc_raycast_down_around(sushie->collisionChannel, &x, &y, &z, &dist,
                    sushie->yaw, sushie->collisionDiameter);
            sushie->curAnim = ANIM_WorldSushie_Run;
            sushie->duration = 12;
            sushie->moveToPos.y = y - (sushie->collisionHeight * 0.5f);
            suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
            script->USE_STATE++; // SWIM_STATE_ENTER_WATER
            break;

        case SWIM_STATE_ENTER_WATER:
            sushie->pos.x += (sushie->moveToPos.x - sushie->pos.x) / sushie->duration;
            sushie->pos.y += (sushie->moveToPos.y - sushie->pos.y) / sushie->duration;
            sushie->pos.z += (sushie->moveToPos.z - sushie->pos.z) / sushie->duration;
            sushie->duration--;
            if (sushie->duration != 0) {
                if (sushie->duration == 2) {
                    sfx_play_sound_at_npc(SOUND_QUICK_PLAYER_JUMP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                    suggest_player_anim_allow_backward(ANIM_Mario1_BeforeJump);
                }
                break;
            }
            sushie->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
            sushie->flags |= NPC_FLAG_FLYING;
            sushie->flags &= ~(NPC_FLAG_GRAVITY | NPC_FLAG_IGNORE_WORLD_COLLISION);
            disable_npc_shadow(sushie);
            npc_set_imgfx_params(sushie, IMGFX_SET_WAVY, 2, 0, 0, 0, 0);
            sushie->curAnim = ANIM_WorldSushie_Ride;
            playerStatus->flags |= PS_FLAG_MOVEMENT_LOCKED;
            dist = dist2D(playerStatus->pos.x, playerStatus->pos.z, sushie->moveToPos.x, sushie->moveToPos.z);
            sushie->jumpVel = 5.0f;
            sushie->jumpScale = 0.6f;
            y = sushie->moveToPos.y - playerStatus->pos.y;
            sushie->duration = (2.0f * sushie->jumpVel) / 0.6f;
            sushie->moveSpeed = dist / sushie->duration;
            sushie->jumpVel += y / sushie->duration;
            suggest_player_anim_allow_backward(ANIM_Mario1_Jump);
            script->USE_STATE++; // SWIM_STATE_EMBARK_1
            fx_rising_bubble(0, sushie->pos.x, sushie->moveToPos.y + (sushie->collisionHeight * 0.5f), sushie->pos.z, 0.0f);
            break;

        case SWIM_STATE_EMBARK_2:
            fx_rising_bubble(0, sushie->pos.x, sushie->moveToPos.y + (sushie->collisionHeight * 0.5f), sushie->pos.z, 0.0f);
            // fallthrough
        case SWIM_STATE_EMBARK_1:
        case SWIM_STATE_EMBARK_3:
            script->USE_STATE++;
            // fallthrough
        case SWIM_STATE_EMBARK_4:
            playerStatus->pos.y += sushie->jumpVel;
            sushie->jumpVel -= sushie->jumpScale;
            add_vec2D_polar(&playerStatus->pos.x, &playerStatus->pos.z, sushie->moveSpeed, sushie->yaw);
            if (sushie->jumpVel <= 0.0f) {
                suggest_player_anim_allow_backward(ANIM_Mario1_Fall);
            }
            gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
            gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
            gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;

            if (sushie->duration != 0) {
                sushie->duration--;
                break;
            }
            set_action_state(ACTION_STATE_RIDE);
            disable_player_shadow();
            playerStatus->flags &= ~PS_FLAG_MOVEMENT_LOCKED;
            suggest_player_anim_always_forward(ANIM_MarioW2_RideSushie);
            sfx_play_sound_at_npc(SOUND_SUSHIE_EMBARK, SOUND_SPACE_DEFAULT, NPC_PARTNER);
            playerStatus->pos.x = sushie->pos.x;
            playerStatus->pos.y = sushie->pos.y;
            playerStatus->pos.z = sushie->pos.z;
            playerStatus->targetYaw = sushie->yaw;
            sushie->moveSpeed = 3.0f;
            partnerStatus->partnerActionState = PARTNER_ACTION_USE;
            gGameStatusPtr->keepUsingPartnerOnMapChange = false;
            partnerStatus->actingPartner = PARTNER_SUSHIE;
            DiveState = DIVE_STATE_NONE;
            DiveTime = 0;
            script->functionTemp[2] = 0;
            script->USE_STATE = SWIM_STATE_RIDING;
            break;

        case SWIM_STATE_RIDING:
            playerStatus->animFlags |= PA_FLAG_RIDING_PARTNER;
            update_riding_physics(sushie);
            if (DiveState == DIVE_STATE_NONE) {
                script->functionTemp[2]++;
                if (script->functionTemp[2] > 20) {
                    script->functionTemp[2] -= 40;
                }
                sushie->pos.y = sushie->moveToPos.y + abs(script->functionTemp[2]) / 8.0f;
                if (script->functionTemp[2] == 5) {
                    get_movement_from_input(&angle, &speed);
                    if (DiveState == DIVE_STATE_NONE) {
                        if (speed != 0.0f) {
                            sfx_play_sound_at_npc(SOUND_SUSHIE_RIDE_MOVING, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                        } else {
                            sfx_play_sound_at_npc(SOUND_SUSHIE_RIDE_IDLE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                        }
                    }
                }
                if (InertialMoveSpeed == 0.0f && !((gGameStatusPtr->frameCounter % 10) & 0xFFFF)) {
                    fx_rising_bubble(0,
                        sushie->pos.x,
                        sushie->moveToPos.y + (sushie->collisionHeight * 0.5f),
                        sushie->pos.z,
                        0);
                }
            } else {
                sushie->pos.y = sushie->moveToPos.y;
            }
            if (!(playerStatus->animFlags & PA_FLAG_RIDING_PARTNER)) {
                sync_player_position();
            }

            if (DiveState == DIVE_STATE_DELAY) {
                if (!(gGameStatusPtr->frameCounter % 19)) {
                    fx_rising_bubble(0,
                        sushie->pos.x,
                        sushie->moveToPos.y + (sushie->collisionHeight * 0.5f),
                        sushie->pos.z,
                        WaterSurfaceY - sushie->pos.y);
                }
            } else if (InertialMoveSpeed != 0.0f && DiveState < DIVE_STATE_DIVING) {
                if (!(gGameStatusPtr->frameCounter % 7)) {
                    fx_rising_bubble(0,
                        sushie->pos.x,
                        sushie->moveToPos.y + (sushie->collisionHeight * 0.5f),
                        sushie->pos.z,
                        DiveState != DIVE_STATE_NONE ? WaterSurfaceY - sushie->pos.y : 0);
                }
            }

            gCameras[CAM_DEFAULT].targetPos.x = sushie->pos.x;
            gCameras[CAM_DEFAULT].targetPos.y = WaterSurfaceY;
            gCameras[CAM_DEFAULT].targetPos.z = sushie->pos.z;
            if ((partnerStatus->pressedButtons & (BUTTON_B | BUTTON_C_DOWN)) || TouchDockTime >= 30) {
                if (IsUnderwater) {
                    break;
                }
                x = sushie->pos.x;
                y = sushie->moveToPos.y + sushie->collisionHeight;
                z = sushie->pos.z;

                if (npc_test_move_taller_with_slipping(sushie->collisionChannel, &x, &y, &z, 10.0f,
                        sushie->yaw, sushie->collisionHeight, sushie->collisionDiameter)
                ) {
                    collisionStatus->pushingAgainstWall = sushie->curWall = NpcHitQueryColliderID;
                } else {
                    collisionStatus->pushingAgainstWall = NO_COLLIDER;
                }

                if (sushie->curWall < 0 || sushie->curWall & COLLISION_WITH_ENTITY_BIT) {
                    if (DiveState == DIVE_STATE_DIVING && DiveTime == 1) {
                        sfx_play_sound_at_npc(SOUND_SUSHIE_DIVE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                    }
                    break;
                }
                collider = get_collider_flags(sushie->curWall) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
                if (collider != SURFACE_TYPE_DOCK_WALL) {
                    if (DiveState == DIVE_STATE_DIVING && DiveTime == 1) {
                        sfx_play_sound_at_npc(SOUND_SUSHIE_DIVE, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                    }
                    break;
                }
                TouchDockTime = 0;
                x = sushie->pos.x;
                z = sushie->pos.z;
                y = sushie->moveToPos.y + 100.0f;
                add_vec2D_polar(&x, &z, 40.0f, sushie->yaw);
                dist = 100.0f;
                // this var is a condition here
                collider = npc_raycast_down_around(sushie->collisionChannel, &x, &y, &z, &dist, sushie->yaw, 0.0f);
                if (collider) {
                    get_collider_center(sushie->curWall, &x, &y, &z);
                    dist = dist2D(sushie->pos.x, sushie->pos.z, x, z);
                    sin_cos_rad(DEG_TO_RAD(atan2(sushie->pos.x, sushie->pos.z, x, z)), &sinAngle, &cosAngle);
                    x = sushie->pos.x + ((sinAngle * dist) * 0.6);
                    z = sushie->pos.z - ((cosAngle * dist) * 0.6);
                    dist = 100.0f;
                    npc_raycast_down_around(sushie->collisionChannel, &x, &y, &z, &dist, sushie->yaw, 0.0f);
                    sushie->moveToPos.y = y;
                    sushie->moveToPos.x = x;
                    sushie->moveToPos.z = z;
                    playerStatus->targetYaw = atan2(playerStatus->pos.x, playerStatus->pos.z, x, z);
                    sushie->yaw = playerStatus->targetYaw;
                    dist = dist2D(playerStatus->pos.x, playerStatus->pos.z, sushie->moveToPos.x, sushie->moveToPos.z);
                    sushie->jumpVel = 5.0f;
                    sushie->jumpScale = 0.6f;
                    sushie->duration = (2.0f * sushie->jumpVel) / 0.6f;
                    sushie->moveSpeed = dist / sushie->duration;
                    sushie->jumpVel += (sushie->moveToPos.y - playerStatus->pos.y) / sushie->duration;
                    sfx_play_sound_at_npc(SOUND_QUICK_PLAYER_JUMP, SOUND_SPACE_DEFAULT, NPC_PARTNER);
                    suggest_player_anim_allow_backward(ANIM_Mario1_BeforeJump);
                    enable_player_shadow();
                    playerStatus->flags |= PS_FLAG_MOVEMENT_LOCKED;
                    script->USE_STATE = SWIM_STATE_DISEMBARK_1;
                }
            }
            break;
        case SWIM_STATE_DISEMBARK_1:
            suggest_player_anim_allow_backward(ANIM_Mario1_Jump);
            script->USE_STATE++;
            // fallthrough
        case SWIM_STATE_DISEMBARK_2:
            if (sushie->jumpVel <= 0.0f) {
                suggest_player_anim_allow_backward(ANIM_Mario1_Fall);
                script->USE_STATE++;
            }
            // fallthrough
        case SWIM_STATE_DISEMBARK_3:
            if (sushie->jumpVel <= 0.0f) {
                playerStatus->pos.y = y = player_check_collision_below(sushie->jumpVel, &collider);
                if (collider > 0) {
                    suggest_player_anim_allow_backward(ANIM_Mario1_Land);
                }
            } else {
                playerStatus->pos.y += sushie->jumpVel;
            }
            sushie->jumpVel -= sushie->jumpScale;
            gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
            gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
            gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;
            if (sushie->duration != 0) {
                add_vec2D_polar(&playerStatus->pos.x, &playerStatus->pos.z, sushie->moveSpeed, sushie->yaw);
                sushie->duration--;
                break;
            }
            if (collider >= 0) {
                playerStatus->flags &= ~PS_FLAG_MOVEMENT_LOCKED;
                suggest_player_anim_allow_backward(ANIM_Mario1_Idle);
                sushie->flags |= NPC_FLAG_IGNORE_WORLD_COLLISION;
                dist = dist2D(sushie->pos.x, sushie->pos.z, sushie->moveToPos.x, sushie->moveToPos.z) +
                            (playerStatus->colliderDiameter * 0.5f);
                sushie->jumpVel = 8.0f;
                sushie->jumpScale = 1.0f;
                sushie->moveSpeed = 4.0f;
                y = sushie->moveToPos.y - sushie->pos.y;
                sushie->duration = (2.0f * sushie->jumpVel) / sushie->jumpScale;
                sushie->moveSpeed = dist / sushie->duration;
                sushie->jumpVel += y / sushie->duration;
                script->USE_STATE = SWIM_STATE_EXIT_WATER;
            }
            break;
        case SWIM_STATE_EXIT_WATER:
            sushie->pos.y += sushie->jumpVel;
            sushie->jumpVel -= sushie->jumpScale;
            add_vec2D_polar(&sushie->pos.x, &sushie->pos.z, sushie->moveSpeed, sushie->yaw);
            if (sushie->duration == 0) {
                enable_player_static_collisions();
                enable_player_input();
                set_action_state(ACTION_STATE_IDLE);
                enable_npc_shadow(sushie);
                partner_clear_player_tracking(sushie);
                IsRiding = false;
                sushie->flags &= ~NPC_FLAG_FLYING;
                sushie->flags |= NPC_FLAG_GRAVITY;
                sushie->flags &= ~NPC_FLAG_IGNORE_WORLD_COLLISION;
                gGameStatusPtr->keepUsingPartnerOnMapChange = false;
                partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
                partnerStatus->actingPartner = 0;
                set_player_imgfx_all(ANIM_Mario1_Idle, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                npc_set_imgfx_params(sushie, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                return ApiStatus_DONE1;
            }
            sushie->duration--;
            break;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldSushie_UseAbility = {
    Call(UseAbility)
    Return
    End
};

void init(Npc* sushie) {
    sushie->collisionHeight = 24;
    sushie->collisionDiameter = 36;
    sushie->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    IsRiding = false;
    DiveState = DIVE_STATE_NONE;
    DiveTime = 0;
    TouchDockTime = 0;
    IsUnderwater = false;
}

API_CALLABLE(TakeOut) {
    Npc* sushie = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(sushie);
    }

    if (partner_get_out(sushie)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldSushie_TakeOut = {
    Call(TakeOut)
    Return
    End
};

TweesterPhysics* TweesterPhysicsPtr = &TweesterPhysicsData;

API_CALLABLE(Update) {
    Npc* sushie = script->owner2.npc;
    f32 sinAngle, cosAngle, liftoffVelocity;
    Entity* entity;

    if (isInitialCall) {
        partner_walking_enable(sushie, true);
        mem_clear(TweesterPhysicsPtr, sizeof(TweesterPhysics));
        TweesterTouchingPartner = nullptr;
    }

    entity = TweesterTouchingPartner;

    if (entity == nullptr) {
        partner_walking_update_player_tracking(sushie);
        partner_walking_update_motion(sushie);
        return ApiStatus_BLOCK;
    }

    switch (TweesterPhysicsPtr->state) {
        case TWEESTER_PARTNER_INIT:
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_ATTRACT;
            TweesterPhysicsPtr->prevFlags = sushie->flags;
            TweesterPhysicsPtr->radius = fabsf(dist2D(sushie->pos.x, sushie->pos.z,
                                                     entity->pos.x, entity->pos.z));
            TweesterPhysicsPtr->angle = atan2(entity->pos.x, entity->pos.z, sushie->pos.x, sushie->pos.z);
            TweesterPhysicsPtr->angularVel = 6.0f;
            TweesterPhysicsPtr->liftoffVelPhase = 50.0f;
            TweesterPhysicsPtr->countdown = 120;
            sushie->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_FLYING;
            sushie->flags &= ~NPC_FLAG_GRAVITY;
        case TWEESTER_PARTNER_ATTRACT:
            sin_cos_rad(DEG_TO_RAD(TweesterPhysicsPtr->angle), &sinAngle, &cosAngle);
            sushie->pos.x = entity->pos.x + (sinAngle * TweesterPhysicsPtr->radius);
            sushie->pos.z = entity->pos.z - (cosAngle * TweesterPhysicsPtr->radius);
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

            sushie->pos.y += liftoffVelocity;
            sushie->renderYaw = clamp_angle(360.0f - TweesterPhysicsPtr->angle);
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
            sushie->flags = TweesterPhysicsPtr->prevFlags;
            TweesterPhysicsPtr->countdown = 30;
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_RELEASE;
            break;
        case TWEESTER_PARTNER_RELEASE:
            partner_walking_update_player_tracking(sushie);
            partner_walking_update_motion(sushie);

            TweesterPhysicsPtr->countdown--;
            if (TweesterPhysicsPtr->countdown == 0) {
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
                TweesterTouchingPartner = nullptr;
            }
            break;
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldSushie_Update = {
    Call(Update)
    Return
    End
};

void try_cancel_tweester(Npc* sushie) {
    if (TweesterTouchingPartner != nullptr) {
        TweesterTouchingPartner = nullptr;
        sushie->flags = TweesterPhysicsPtr->prevFlags;
        TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
        partner_clear_player_tracking(sushie);
    }
}

API_CALLABLE(PutAway) {
    Npc* sushie = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(sushie);
        gPlayerStatusPtr->animFlags &= ~PA_FLAG_RIDING_PARTNER;
    }

    if (partner_put_away(sushie)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldSushie_PutAway = {
    Call(PutAway)
    Return
    End
};

void pre_battle(Npc* sushie) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (IsRiding) {
        partnerStatus->npc = *sushie;
        partnerStatus->shouldResumeAbility = true;
        enable_player_static_collisions();
        enable_player_input();
        set_action_state(ACTION_STATE_IDLE);
        partner_clear_player_tracking(sushie);
    }

    partnerStatus->actingPartner = PARTNER_SUSHIE;
}

void post_battle(Npc* sushie) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (partnerStatus->shouldResumeAbility) {
        *sushie = partnerStatus->npc;
        partner_use_ability();
    }
}

API_CALLABLE(EnterMap) {
    Npc* partnerNPC = get_npc_unsafe(NPC_PARTNER);
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
        WaterSurfaceY = playerStatus->pos.y;
    }

    switch (script->functionTemp[0]) {
        case 0:
            gGameStatusPtr->keepUsingPartnerOnMapChange = true;
            disable_player_static_collisions();
            disable_player_input();
            partnerNPC->pos.x = playerStatus->pos.x;
            partnerNPC->pos.z = playerStatus->pos.z;
            partnerNPC->pos.y = playerStatus->pos.y;
            test_for_water_level(partnerNPC->collisionChannel, partnerNPC->pos.x, partnerNPC->pos.y, partnerNPC->pos.z,
                                partnerNPC->yaw, partnerNPC->collisionDiameter * 0.5f);
            partnerNPC->pos.y = WaterSurfaceY - (partnerNPC->collisionHeight * 0.5f);
            partnerNPC->yaw = atan2(partnerNPC->pos.x, partnerNPC->pos.z, script->varTable[1], script->varTable[3]);
            partnerNPC->curAnim = ANIM_WorldSushie_Ride;
            partnerNPC->jumpScale = 0.0f;
            partnerNPC->moveSpeed = 3.0f;
            partnerNPC->moveToPos.x = partnerNPC->pos.x;
            partnerNPC->moveToPos.y = partnerNPC->pos.y;
            partnerNPC->moveToPos.z = partnerNPC->pos.z;
            partnerNPC->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_FLYING;
            partnerNPC->flags &= ~NPC_FLAG_GRAVITY;
            disable_npc_shadow(partnerNPC);
            disable_player_shadow();

            if (script->varTable[12] == 0) {
                partner_kill_ability_script();
            } else {
                suggest_player_anim_always_forward(ANIM_MarioW2_RideSushie);
                if ((partnerNPC->yaw >= 0.0f) && (partnerNPC->yaw <= 180.0f)) {
                    partnerNPC->yawCamOffset = partnerNPC->yaw;
                    partnerNPC->isFacingAway = true;
                }
            }
            script->functionTemp[1] = 25;
            script->functionTemp[0] = 1;
            break;
        case 1:
            npc_move_heading(partnerNPC, partnerNPC->moveSpeed, partnerNPC->yaw);
            sync_player_position();

            if (!(script->functionTemp[1] & 3)) {
                fx_rising_bubble(0, partnerNPC->pos.x, partnerNPC->moveToPos.y +
                        (partnerNPC->collisionHeight * 0.5f), partnerNPC->pos.z, 0);
            }

            script->functionTemp[1]--;
            if (script->functionTemp[1] == 0) {
                if (script->varTable[12] == 1) {
                    set_action_state(ACTION_STATE_RIDE);
                    partner_use_ability();
                } else {
                    enable_player_static_collisions();
                    enable_player_input();
                }
                return ApiStatus_DONE2;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldSushie_EnterMap = {
    Call(EnterMap)
    Return
    End
};

WORLD_PARTNER_ENTRY = {
    .isFlying = false,
    .init = init,
    .takeOut = &EVS_WorldSushie_TakeOut,
    .update = &EVS_WorldSushie_Update,
    .useAbility = &EVS_WorldSushie_UseAbility,
    .putAway = &EVS_WorldSushie_PutAway,
    .idle = ANIM_WorldSushie_Idle,
    .canPlayerOpenMenus = world_partner_can_open_menus_default,
    .preBattle = pre_battle,
    .postBattle = post_battle,
    .onEnterMap = &EVS_WorldSushie_EnterMap,
    .syncPlayerPosition = sync_player_position,
};
