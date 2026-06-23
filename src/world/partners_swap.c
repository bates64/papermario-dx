#include "common_structs.h"
#include "world/partners.h"
#include "world/partners_internal.h"
#include "macros.h"
#include "npc.h"

void partner_init_put_away(Npc* partner) {
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    partner->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_put_away(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 tempMoveToX;
    f32 tempMoveToY;
    f32 tempMoveToZ;
    f32 tempPosX;
    f32 tempPosZ;
    f32 tempPosY;
    f32 tempDuration;

    switch (PartnerFollowState){
        case PARTNER_MOVE_FOLLOW_PLAYER:
            tempMoveToX = partner->pos.x;
            tempMoveToY = partner->pos.y;
            tempMoveToZ = partner->pos.z;
            partner->flags &= ~NPC_FLAG_GRAVITY;
            partner->flags &= ~NPC_FLAG_FLYING;
            tempPosX = playerStatus->pos.x;
            partner->moveToPos.x = tempPosX;
            tempPosY = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            partner->moveToPos.y = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            tempPosZ = playerStatus->pos.z;
            SavedPartnerPos.x = tempMoveToX;
            SavedPartnerPos.y = tempMoveToY;
            SavedPartnerPos.z = tempMoveToZ;
            partner->moveSpeed = 4.0f;
            partner->jumpScale = 1.6f;
            partner->moveToPos.z = tempPosZ;
            partner->planarFlyDist = dist2D(tempMoveToX, tempMoveToZ, tempPosX, tempPosZ);
            partner->yaw = atan2(tempMoveToX, tempMoveToZ, tempPosX, tempPosZ);
            partner->duration = 15;
            partner->moveSpeed = partner->planarFlyDist / partner->duration;
            tempMoveToY = tempPosY - tempMoveToY;
            partner->jumpVel = (tempMoveToY + partner->jumpScale * partner->duration * partner->duration * 0.5f) / partner->duration;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            enable_npc_blur(partner);
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            tempDuration = partner->duration;
            if (partner->duration > 10.0f) {
                tempDuration = 10.0f;
            }
            partner->scale.x = tempDuration / 10.0f;
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;
            partner->duration--;
            if (partner->duration < 0) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
            }
            break;
        case PARTNER_MOVE_JUMPING:
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
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    npc->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_get_out(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 x, y, z, hitDepth;
    f32 var_f0;

    f32 moveToX, moveToY, moveToZ;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            if (clamp_angle(playerStatus->spriteFacingAngle) < 180.0f) {
                partner->yaw = clamp_angle(camera->curYaw + 90.0f);
            } else {
                partner->yaw = clamp_angle(camera->curYaw - 90.0f);
            }
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            if (ActivePartner->isFlying) {
                partner->moveToPos.y = playerStatus->pos.y;
            }
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, partner->yaw);
            moveToX = partner->moveToPos.x;
            moveToY = partner->moveToPos.y;
            moveToZ = partner->moveToPos.z;
            if (!ActivePartner->isFlying) {
                x = moveToX;
                y = moveToY + partner->collisionHeight;
                z = moveToZ;
                add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                hitDepth = 1000.0f;
                if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter)) {
                    s32 surfaceType = get_collider_flags(NpcHitQueryColliderID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;

                    if ((surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) || (hitDepth > 100.0f)) {
                        moveToX = playerStatus->pos.x;
                        moveToY = playerStatus->pos.y;
                        moveToZ = playerStatus->pos.z;
                        add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                    }
                } else {
                    moveToX = playerStatus->pos.x;
                    moveToY = playerStatus->pos.y;
                    moveToZ = playerStatus->pos.z;
                    add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                }
            }

            x = partner->pos.x = playerStatus->pos.x;
            y = partner->pos.y = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            z = partner->pos.z = playerStatus->pos.z;

            partner->moveSpeed = 4.0f;
            partner->jumpScale = 1.2f;
            partner->planarFlyDist = dist2D(x, z, moveToX, moveToZ);
            partner->yaw = atan2(x, z, moveToX, moveToZ);
            partner->duration = partner->planarFlyDist / partner->moveSpeed;
            if (partner->duration < 10) {
                partner->duration = 10;
                partner->moveSpeed = partner->planarFlyDist / partner->duration;
            }
            partner->jumpVel = (moveToY - y + (partner->jumpScale * partner->duration * partner->duration * 0.5f)) /
                                    partner->duration;
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
            y = moveToY - y;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            if (partner->jumpVel < 0.0f && npc_try_snap_to_ground(partner, fabsf(partner->jumpVel))) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
                break;
            }
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            npc_do_world_collision(partner);
            var_f0 = partner->duration;
            if (var_f0 > 10.0f) {
                var_f0 = 10.0f;
            }

            partner->scale.x = (10.0f - var_f0) / 10.0f;
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;

            partner->duration--;
            if (partner->duration < 0) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
            }
            break;
        case PARTNER_MOVE_JUMPING:
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
