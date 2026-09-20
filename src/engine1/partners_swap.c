#include "common.h"
#include "world/partners.h"
#include "world/partners_internal.h"

BSS s16 PutAwayState;
BSS s16 GetOutState;

enum PutAwayStates {
    PUT_AWAY_INIT   = 0,
    PUT_AWAY_ARC    = 1,
    PUT_AWAY_DONE   = 2,
};

enum GetOutStates {
    GET_OUT_INIT    = 0,
    GET_OUT_ARC     = 1,
    GET_OUT_DONE    = 2,
};

void partner_init_put_away(Npc* partner) {
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    PutAwayState = PUT_AWAY_INIT;
    partner->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_put_away(Npc* partner) {
    switch (PutAwayState){
        case PUT_AWAY_INIT:
            partner->flags &= ~(NPC_FLAG_GRAVITY | NPC_FLAG_FLYING);
            partner->moveToPos.x = gPlayerStatus.pos.x;
            partner->moveToPos.y = gPlayerStatus.pos.y + (gPlayerStatus.colliderHeight / 2);
            partner->moveToPos.z = gPlayerStatus.pos.z;
            SavedPartnerPos.x = partner->pos.x;
            SavedPartnerPos.y = partner->pos.y;
            SavedPartnerPos.z = partner->pos.z;
            partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->duration = 15;
            partner->jumpScale = 1.6f;
            partner->moveSpeed = partner->planarFlyDist / partner->duration;
            partner->jumpVel = calc_projectile_v0(partner->pos.y, partner->moveToPos.y, partner->jumpScale, partner->duration);
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            enable_npc_blur(partner);
            PutAwayState = PUT_AWAY_ARC;
            break;
        case PUT_AWAY_ARC:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            partner->scale.x = MIN(1.0f, partner->duration / 10.0f);
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;
            partner->duration--;
            if (partner->duration < 0) {
                PutAwayState = PUT_AWAY_DONE;
            }
            break;
        case PUT_AWAY_DONE:
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
            partner->jumpVel = 0.0f;
            partner->pos.y = partner->moveToPos.y;
            disable_npc_blur(partner);
            return true;
    }
    return false;
}

void partner_init_get_out(Npc* npc) {
    npc->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    GetOutState = GET_OUT_INIT;
    npc->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_get_out(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 testX, testY, testZ, hitDepth;
    f32 moveToX, moveToY, moveToZ;
    b32 badLocation;

    switch (GetOutState) {
        case GET_OUT_INIT:
            if (clamp_angle(playerStatus->spriteFacingAngle) < 180.0f) {
                partner->yaw = clamp_angle(camera->curYaw + 90.0f);
            } else {
                partner->yaw = clamp_angle(camera->curYaw - 90.0f);
            }

            // find a position beside the player, using camera yaw and player collision size
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, partner->yaw);
            moveToX = partner->moveToPos.x;
            moveToY = partner->moveToPos.y;
            moveToZ = partner->moveToPos.z;

            if (!ActivePartner->isFlying) {
                badLocation = false;
                testX = moveToX;
                testY = moveToY + partner->collisionHeight;
                testZ = moveToZ;
                add_vec2D_polar(&testX, &testZ, 2.0f, gCameras[gCurrentCameraID].curYaw);
                hitDepth = 1000.0f;
                if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &testX, &testY, &testZ, &hitDepth,
                        partner->yaw, partner->collisionDiameter)
                ) {
                    s32 surfaceType = get_collider_flags(NpcHitQueryColliderID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
                    badLocation = ((hitDepth > 100.0f)
                        || surfaceType == SURFACE_TYPE_SPIKES
                        || surfaceType == SURFACE_TYPE_LAVA);
                } else {
                    badLocation = true;
                }

                if (badLocation) {
                    // use the player's location with a small visual offset
                    moveToX = playerStatus->pos.x;
                    moveToY = playerStatus->pos.y;
                    moveToZ = playerStatus->pos.z;
                    add_vec2D_polar(&moveToX, &moveToZ, 2.0f, gCameras[gCurrentCameraID].curYaw);
                }
            }

            partner->pos.x = playerStatus->pos.x;
            partner->pos.y = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            partner->pos.z = playerStatus->pos.z;

            partner->moveSpeed = 4.0f;
            partner->jumpScale = 1.2f;
            partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, moveToX, moveToZ);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, moveToX, moveToZ);
            partner->duration = partner->planarFlyDist / partner->moveSpeed;
            if (partner->duration < 10) {
                partner->duration = 10;
                partner->moveSpeed = partner->planarFlyDist / partner->duration;
            }
            partner->jumpVel = calc_projectile_v0(partner->pos.y, moveToY, partner->jumpScale, partner->duration);
            GetOutState = GET_OUT_ARC;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            break;
        case GET_OUT_ARC:
            if (partner->jumpVel < 0.0f && npc_try_snap_to_ground(partner, fabsf(partner->jumpVel))) {
                GetOutState = GET_OUT_DONE;
                break;
            }
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            npc_do_world_collision(partner);

            partner->scale.x = 1.0f - MIN(1.0f, partner->duration / 10.0f);
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;
            partner->duration--;
            if (partner->duration < 0) {
                GetOutState = GET_OUT_DONE;
            }
            break;
        case GET_OUT_DONE:
            partner->pos.y = partner->moveToPos.y;
            partner->jumpVel = 0.0f;
            partner->scale.x = 1.0f;
            partner->scale.y = 1.0f;
            partner->scale.z = 1.0f;
            partner->moveToPos.x = partner->pos.x;
            partner->moveToPos.y = partner->pos.y;
            partner->moveToPos.z = partner->pos.z;
            partner->pos.x = partner->pos.x;
            partner->pos.y = playerStatus->pos.y;
            if (ActivePartner->isFlying) {
                partner->pos.y = playerStatus->pos.y;
            }
            partner->pos.z = partner->pos.z;
            partner_clear_player_tracking(partner);
            partner->pos.x = partner->moveToPos.x;
            partner->pos.y = partner->moveToPos.y;
            partner->pos.z = partner->moveToPos.z;
            if (partner->flags & NPC_FLAG_GROUNDED) {
                if (!ActivePartner->isFlying) {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                }
            }
            return true;
    }
    return false;
}

// forces the player to complete a direction flip if they are currently performing one
// the resulting camera-relative direction is returned as a boolean 'isFacingLeft'
s32 partner_force_player_flip_done(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cameras = gCameras;
    s32 isFacingLeft;

    if (playerStatus->flipYaw[CAM_DEFAULT] == 0.0f) {
        if (!(playerStatus->spriteFacingAngle >= 90.0f) || !(playerStatus->spriteFacingAngle < 270.0f)) {
            isFacingLeft = true;
            playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw - 90.0f);
        } else {
            isFacingLeft = false;
            playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw + 90.0f);
        }
    } else if (get_clamped_angle_diff(cameras[CAM_DEFAULT].curYaw, playerStatus->targetYaw) < 0.0f) {
        isFacingLeft = true;
        playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw - 90.0f);

    } else {
        isFacingLeft = false;
        playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw + 90.0f);
    }

    playerStatus->curYaw = playerStatus->targetYaw;
    return isFacingLeft;
}
