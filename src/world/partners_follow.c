#include "common.h"
#include "world/partners.h"
#include "world/partners_internal.h"

void partner_flying_follow_player(Npc* partner);
void partner_move_to_goal(Npc* partner, s32 isFlying);

enum PartnerMovementStates {
    PARTNER_MOVE_FOLLOW_PLAYER      = 0,
    PARTNER_MOVE_BEGIN_JUMP         = 1,
    PARTNER_MOVE_JUMPING            = 2,
    PARTNER_MOVE_IDLE_NEAR_PLAYER   = 5,
    PARTNER_MOVE_TO_SIDE            = 15,
    PARTNER_MOVE_TO_GOAL            = 20,
    PARTNER_MOVE_DISABLE_ASAP       = 40,
    PARTNER_MOVE_DISABLED           = 50,
};

typedef struct PlayerPathElement {
    /* 0x00 */ b8 isJumping;
    /* 0x01 */ PAD(3);
    /* 0x04 */ Vec3f pos;
} PlayerPathElement; // size = 0x10

BSS PlayerPathElement PlayerMoveHistory[40];
BSS s32 PlayerMoveHistoryIndex;
BSS s32 PartnerMoveHistoryReadIndex;
BSS f32 PartnerTetherDistance;
BSS s16 PartnerFollowState;
BSS s16 PartnerForcedFollowMode;
BSS s16 PartnerFollowSubstate;
BSS b32 PartnerBlockedAbove;
BSS s32 PartnerMoveGoalX;
BSS s32 PartnerMoveGoalZ;
BSS s32 PartnerMoveTime;
BSS f32 PartnerMoveSpeed;
BSS f32 PartnerMoveYaw;
BSS s16 PartnerStuckTime;
f32 PartnerFlyingDeltaY = 0.0f;

void partner_walking_enable(Npc* partner, s32 val) {
    s32 i;

    partner->pos.x = SavedPartnerPos.x;
    partner->pos.y = SavedPartnerPos.y;
    partner->pos.z = SavedPartnerPos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++) {
        PlayerMoveHistory[i].pos.x = gPlayerStatus.pos.x;
        PlayerMoveHistory[i].pos.y = gPlayerStatus.pos.y;
        PlayerMoveHistory[i].pos.z = gPlayerStatus.pos.z;
        PlayerMoveHistory[i].isJumping = false;
    }

    PlayerMoveHistoryIndex = 0;
    PartnerMoveHistoryReadIndex = 0;
    if (val) {
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
    } else {
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    }
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;

    switch (PartnerSpawnMode) {
        case PARTNER_SPAWN_RESET:
        case PARTNER_SPAWN_SWITCH:
            PartnerSpawnMode = PARTNER_SPAWN_NONE;
            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            break;
        case PARTNER_SPAWN_INSTA:
            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            PartnerFollowState = PARTNER_MOVE_DISABLED;
            break;
    }

    PartnerFollowSubstate = 0;
    PartnerMoveTime = 16;
    PartnerTetherDistance = 40.0f;
    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
    partner_clear_collision_flags(partner);
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    partner->jumpVel = 0.0f;
    partner->flags |= NPC_FLAG_TOUCHES_GROUND | NPC_FLAG_GRAVITY | NPC_FLAG_IGNORE_CHAR_COLLISION;
    partner->jumpScale = 1.8f;
}

void partner_walking_update_player_tracking(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 isPlayerJumping;
    PlayerPathElement* currentSnapshot;

    if (playerStatus->flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING)) {
        isPlayerJumping = (playerStatus->actionState == ACTION_STATE_LAND || playerStatus->actionState == ACTION_STATE_STEP_DOWN) ^ 1;
    } else {
        isPlayerJumping = false;
    }
    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    if ((!currentSnapshot->isJumping || !isPlayerJumping) &&
        ((currentSnapshot->pos.x != playerStatus->pos.x) || (currentSnapshot->pos.y != playerStatus->pos.y)
        || (currentSnapshot->pos.z != playerStatus->pos.z))) {
        if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex + 1) {
            if (++PlayerMoveHistoryIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                PlayerMoveHistoryIndex = 0;
            }
            currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
            currentSnapshot->pos.x = playerStatus->pos.x;
            currentSnapshot->pos.y = playerStatus->pos.y;
            currentSnapshot->pos.z = playerStatus->pos.z;
            currentSnapshot->isJumping = isPlayerJumping;
        }
    }
}

void partner_walking_update_motion(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (!gGameStatusPtr->multiplayerEnabled
        || playerStatus->flags & (PS_FLAG_INPUT_DISABLED | PS_FLAG_NO_STATIC_COLLISION)
        || partnerStatus->inputDisabledCount != 0
        || partnerStatus->moveWithoutInput
    ) {
        if (!(playerStatus->animFlags & PA_FLAG_OPENED_HIDDEN_PANEL)) {
            partner_walking_follow_player(partner);
        }
        if (partnerStatus->pressedButtons & (BUTTON_Z | BUTTON_B | BUTTON_C_LEFT | BUTTON_C_DOWN)) {
            partnerStatus->moveWithoutInput = false;
        }
    }

    if (PartnerFollowState != PARTNER_MOVE_DISABLED && fabsf(partner->pos.y - playerStatus->pos.y) > 1000.0f) {
        partner->pos.x = playerStatus->pos.x;
        partner->pos.y = playerStatus->pos.y;
        partner->pos.z = playerStatus->pos.z;
        partner->jumpVel = 0.0f;
        partner->jumpScale = 0.0f;
        partner->flags = partner->flags & ~PA_FLAG_OPENED_HIDDEN_PANEL;
    }

    partner_do_player_collision(partner);
    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;
}

b32 partner_can_move_over_collider(s32 collisionID) {
    if (collisionID <= NO_COLLIDER) {
        return true;
    }

    if (collisionID & COLLISION_WITH_ENTITY_BIT) {
        switch (get_entity_type(collisionID)) {
            case ENTITY_TYPE_BLUE_SWITCH:
            case ENTITY_TYPE_RED_SWITCH:
            case ENTITY_TYPE_HUGE_BLUE_SWITCH:
            case ENTITY_TYPE_GREEN_STOMP_SWITCH:
            case ENTITY_TYPE_SIMPLE_SPRING:
            case ENTITY_TYPE_SCRIPT_SPRING:
            case ENTITY_TYPE_CHEST:
            case ENTITY_TYPE_BELLBELL_PLANT:
            case ENTITY_TYPE_TRUMPET_PLANT:
            case ENTITY_TYPE_MUNCHLESIA:
            case ENTITY_TYPE_CYMBAL_PLANT:
            case ENTITY_TYPE_PINK_FLOWER:
            case ENTITY_TYPE_SPINNING_FLOWER:
            case ENTITY_TYPE_3B:
            case ENTITY_TYPE_TWEESTER:
               return false;
        }
    }

    return true;
}

void partner_walking_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cameras = &gCameras[CAM_DEFAULT];
    s32 surfaceType;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    f32 x, y, z;
    f32 distance;
    f32 yaw;
    f32 temp_a3;
    f32 angle;
    PlayerPathElement* currentSnapshot;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            partner->moveSpeed = 3.0f;

            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance >= 50.0) {
                partner->moveSpeed = !(playerStatus->animFlags & PA_FLAG_SPINNING) ? 5.0f : 7.0f;
            }
            if (PartnerTetherDistance < 20.0) {
                partner->moveSpeed = 4.0f;
            }
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
            if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            while (true) {
                distance = dist2D(x, z, moveHistoryX, moveHistoryZ);
                yaw = atan2(x, z, moveHistoryX, moveHistoryZ);
                if (partner->moveSpeed < distance) {
                    distance = dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z);
                    if (distance >= 50.0) {
                        break;
                    }
                    if (PartnerTetherDistance < distance) {
                        partner->moveSpeed = distance - PartnerTetherDistance;
                        if (partner->moveSpeed > 3.0) {
                            partner->moveSpeed = 3.0f;
                            if (PartnerTetherDistance < 20.0f) {
                                partner->moveSpeed = 4.0f;
                            }
                        } else {
                            partner->moveSpeed += 1.0;
                        }
                        break;
                    } else {
                        partner->moveSpeed = 0.0f;
                        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                    }
                }
                if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                } else {
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;

                    if (fabsf(get_clamped_angle_diff(partner->yaw, atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ))) > 90.0f) {
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        break;
                    }

                    if ((partner->flags & NPC_FLAG_GROUNDED) && currentSnapshot->isJumping) {
                        PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                        break;
                    }
                }
            }

            if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                partner->moveSpeed *= 0.5f;
            }
            partner->yaw = yaw;
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
            surfaceType = get_collider_flags(partner->curFloor);
            if (surfaceType == SURFACE_TYPE_SPIKES
                || surfaceType == SURFACE_TYPE_LAVA
                || ((partner->flags & NPC_FLAG_GROUNDED) && (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD))
            ) {
                if (!partner_can_move_over_collider(partner->curWall)) {
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                    if (fabsf(get_clamped_angle_diff(partner->yaw, atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ))) > 90.0f) {
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        return;
                    }
                } else {
                    PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                    return;
                }
            }
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            surfaceType = get_collider_flags(partner->curFloor);
            if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                    moveHistoryX = partner->pos.x;
                    moveHistoryY = playerStatus->pos.y;
                    moveHistoryZ = partner->pos.z;
                    add_vec2D_polar(&moveHistoryX, &moveHistoryZ, 6.0f, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z));
                } else {
                    break;
                }
            } else {
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryY = currentSnapshot->pos.y;
                moveHistoryZ = currentSnapshot->pos.z;
            }
            partner->moveToPos.x = moveHistoryX;
            partner->moveToPos.y = moveHistoryY;
            partner->moveToPos.z = moveHistoryZ;
            partner->duration = 0;
            partner->jumpScale = 3.0f;
            partner->moveSpeed = 6.0f;
            partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            if (partner->planarFlyDist > 50.0) {
                partner->planarFlyDist = 50.0f;
            }
            distance = partner->planarFlyDist;
            y = partner->moveToPos.y - partner->pos.y;
            if (distance < PartnerTetherDistance && !(surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA)) {
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                return;
            }
            partner->duration = distance / partner->moveSpeed;
            if (partner->duration < 10) {
                partner->duration = 10;
            }
            partner->moveSpeed = partner->planarFlyDist / partner->duration;
            partner->jumpVel = (y + partner->jumpScale * partner->duration * partner->duration * 0.5f) / partner->duration;
            if (partner->jumpVel > 20.0) {
                partner->jumpVel = 20.0f;
            }
            if (partner->jumpVel < 0.0) {
                partner->jumpVel = 0.0f;
            }
            if (!(surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA)) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            } else {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].hurt;
            }

            partner->moveToPos.x = partner->pos.x;
            partner->moveToPos.y = partner->pos.y;
            partner->moveToPos.z = partner->pos.z;
            partner->flags |= NPC_FLAG_JUMPING;
            PartnerFollowState = PARTNER_MOVE_JUMPING;
            // fallthrough
        case PARTNER_MOVE_JUMPING:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            if (partner->pos.y < -2000.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->pos.x = playerStatus->pos.x;
                partner->pos.y = playerStatus->pos.y;
                partner->pos.z = playerStatus->pos.z;
                PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                return;
            }
            if (partner->jumpVel <= 0.0f) {
                distance = fabsf(partner->jumpVel) + 11.0f;
                x = partner->pos.x;
                y = partner->pos.y + distance;
                z = partner->pos.z;
                if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                    if (distance <= fabsf(partner->jumpVel) + 22.0f) {
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                        partner->flags &= ~NPC_FLAG_JUMPING;
                        partner->jumpVel = 0.0f;
                        partner->pos.y = y;
                        partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
                        npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        if (distance < 5.0) {
                            partner->pos.x = playerStatus->pos.x;
                            partner->pos.y = playerStatus->pos.y;
                            partner->pos.z = playerStatus->pos.z;
                            add_vec2D_polar(&partner->pos.x, &partner->pos.z, 5.0f, clamp_angle((cameras[CAM_DEFAULT].curYaw + 90.0f) - playerStatus->spriteFacingAngle));
                            PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        }
                        break;
                    }
                }
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            break;
        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    if (playerStatus->actionState == ACTION_STATE_TALK) {
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    }
                    surfaceType = get_collider_flags(partner->curFloor);
                    if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        return;
                    }
                } else {
                    temp_a3 = clamp_angle(cameras[CAM_DEFAULT].curYaw + (playerStatus->spriteFacingAngle < 180.0f ? 90.0f : -90.0f));
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, temp_a3);
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->moveSpeed = 2.0f;
                    if (distance > 2.0f) {
                        partner->yaw = yaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                        if (!(partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD)) {
                            PartnerStuckTime = 0;
                        } else {
                            PartnerStuckTime++;
                            if (PartnerStuckTime > 10) {
                                yaw = playerStatus->targetYaw;
                                partner->moveSpeed = 0.0f;
                                partner->jumpScale = 0.0f;
                                partner->renderYaw = yaw;
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                                }
                            }
                        }
                    } else {
                        yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        partner->yaw = yaw;
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                    partner->yaw = yaw;
                    npc_move_heading(partner, partner->moveSpeed, yaw);
                    npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
                    distance = 1000.0f;
                    x = partner->pos.x;
                    z = partner->pos.z;
                    y = partner->pos.y + partner->collisionHeight;
                    if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                        s32 surfaceType = get_collider_flags(NpcHitQueryColliderID);
                        if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                            partner->yaw = clamp_angle(yaw + 180.0f);
                            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                            partner->moveSpeed = 0.0f;
                            partner->jumpScale = 0.0f;
                            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                            if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                            } else if (playerStatus->actionState == ACTION_STATE_TALK) {
                                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                            }
                        } else if (!partner_can_move_over_collider(NpcHitQueryColliderID)) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                        }
                    }
                    break;
                }
            }
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (!partner_can_move_over_collider(NpcHitQueryColliderID)) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                }
            } else {
                while (true) {
                    if (currentSnapshot->isJumping) {
                        break;
                    }
                    yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                    if (fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f) {
                        break;
                    }
                    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                        break;
                    }
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                }
                if (!currentSnapshot->isJumping) {
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    return;
                }
                while (true) {
                    if (!currentSnapshot->isJumping) {
                        break;
                    }
                    yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                    if (fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f) {
                        break;
                    }
                    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                        break;
                    }
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                }
                PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                return;
            }
            break;
        case PARTNER_MOVE_TO_SIDE:
            switch (PartnerFollowSubstate) {
                case 0:
                    angle = clamp_angle(player_get_side_angle() + 180.0f);
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, angle);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    PartnerMoveSpeed = distance / PartnerMoveTime;
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PartnerMoveSpeed >= 4.0 ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->yaw = PartnerMoveYaw = yaw;
                    PartnerFollowSubstate++;
                    // fallthrough
                case 1:
                    if (PartnerMoveTime != 0) {
                        PartnerMoveTime--;
                        if (partner->jumpScale != 0.0f) {
                            partner->jumpVel -= partner->jumpScale;
                            partner->pos.y += partner->jumpVel;
                            if (partner->jumpVel <= 0.0f) {
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                            }
                            if (partner->jumpVel <= 0.0f) {
                                distance = fabsf(partner->jumpVel) + 11.0f;
                                x = partner->pos.x;
                                y = partner->pos.y + distance;
                                z = partner->pos.z;
                                if ((npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) && (distance <= (fabsf(partner->jumpVel) + 22.0f))) {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[partner->moveSpeed >= 4.0 ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                                    partner->jumpScale = 0.0f;
                                    partner->jumpVel = 0.0f;
                                    partner->pos.y = y;
                                    partner->flags &= ~NPC_FLAG_JUMPING;
                                }
                            }
                        }
                        partner->moveSpeed = PartnerMoveSpeed;
                        partner->yaw = PartnerMoveYaw;
                        npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                        npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
                    } else {
                        partner_clear_player_tracking(partner);
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        partner->yaw = clamp_angle((cameras[CAM_DEFAULT].curYaw + 270.0f) - playerStatus->spriteFacingAngle);
                        PartnerMoveTime = 30;
                        PartnerFollowSubstate++;
                    }
                    return;
                case 2:
                    if (PartnerMoveTime != 0) {
                        PartnerMoveTime--;
                        return;
                    }
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    PartnerFollowSubstate = 0;
            }
            break;
        case PARTNER_MOVE_TO_GOAL:
            partner_move_to_goal(partner, false);
            break;
        case PARTNER_MOVE_DISABLE_ASAP:
            if (partner->flags & NPC_FLAG_GROUNDED) {
                if (partner_can_move_over_collider(partner->curFloor)) {
                    PartnerFollowState = PARTNER_MOVE_DISABLED;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                } else {
                    PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                }
                break;
            }
            partner->jumpScale = 3.0f;
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            if (partner->pos.y < -2000.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->pos.x = playerStatus->pos.x;
                partner->pos.y = playerStatus->pos.y;
                partner->pos.z = playerStatus->pos.z;
                PartnerFollowState = PARTNER_MOVE_DISABLED;
                return;
            }
            distance = fabsf(partner->jumpVel) + 11.0f;
            x = partner->pos.x;
            y = partner->pos.y + distance;
            z = partner->pos.z;
            if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->pos.y = y;
                partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
                npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                PartnerFollowState = PARTNER_MOVE_DISABLED;
            }
            break;
        case PARTNER_MOVE_DISABLED:
            break;
    }
}

void partner_flying_enable(Npc* partner, s32 val) {
    s32 i;

    partner->pos.x = SavedPartnerPos.x;
    partner->pos.y = SavedPartnerPos.y;
    partner->pos.z = SavedPartnerPos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++) {
        PlayerMoveHistory[i].pos.x = SavedPartnerPos.x;
        PlayerMoveHistory[i].pos.y = SavedPartnerPos.y;
        PlayerMoveHistory[i].pos.z = SavedPartnerPos.z;
        PlayerMoveHistory[i].isJumping = false;
    }

    PlayerMoveHistoryIndex = 0;
    PartnerMoveHistoryReadIndex = 0;

    if (!val) {
        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    } else {
        switch (PartnerSpawnMode) {
            case PARTNER_SPAWN_NONE:
                PartnerFollowState = PARTNER_MOVE_TO_SIDE;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                break;
            case PARTNER_SPAWN_RESET:
            case PARTNER_SPAWN_SWITCH:
                PartnerSpawnMode = PARTNER_SPAWN_NONE;
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                break;
            case PARTNER_SPAWN_INSTA:
                PartnerFollowState = PARTNER_MOVE_DISABLED;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                break;
        }
    }

    PartnerFollowSubstate = 0;
    PartnerMoveTime = 16;
    PartnerTetherDistance = 40.0f;

    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
    partner_clear_collision_flags(partner);
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    partner->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
    partner->flags &= ~NPC_FLAG_GRAVITY;
}

void partner_flying_update_player_tracking(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot;
    f32 effectiveY = playerStatus->pos.y;
    b32 isPlayerJumping = false;

    if ((playerStatus->actionState == ACTION_STATE_HIT_LAVA) || (playerStatus->actionState == ACTION_STATE_HIT_FIRE)) {
        effectiveY = playerStatus->lastGoodPos.y + partner->collisionHeight + 5;
    }

    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];

    if (currentSnapshot->pos.x == playerStatus->pos.x
        && currentSnapshot->pos.y == effectiveY
        && currentSnapshot->pos.z == playerStatus->pos.z
    ) {
        return;
    }

    // interesting: isPlayerJumping is always false here
    if (currentSnapshot->isJumping && isPlayerJumping) {
        return;
    }

    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex + 1) {
        return;
    }

    PlayerMoveHistoryIndex++;
    if (PlayerMoveHistoryIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
        PlayerMoveHistoryIndex = 0;
    }

    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    currentSnapshot->pos.x = playerStatus->pos.x;
    currentSnapshot->pos.y = effectiveY;
    currentSnapshot->pos.z = playerStatus->pos.z;
    currentSnapshot->isJumping = isPlayerJumping;
}

void partner_flying_update_motion(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    f32 x, y, z, hitDepth;
    f32 targetY;

    if (!gGameStatusPtr->multiplayerEnabled
        || (playerStatus->flags & (PS_FLAG_INPUT_DISABLED | PS_FLAG_NO_STATIC_COLLISION))
        || partnerStatus->inputDisabledCount
        || partnerStatus->moveWithoutInput
    ) {
        if (!(playerStatus->animFlags & PA_FLAG_OPENED_HIDDEN_PANEL) || !PartnerBlockedAbove) {
            partner_flying_follow_player(partner);
        }
        if (partnerStatus->pressedButtons & (BUTTON_B | BUTTON_Z | BUTTON_C_DOWN | BUTTON_C_LEFT)) {
            partnerStatus->moveWithoutInput = false;
        }
    }

    if (PartnerFollowState != PARTNER_MOVE_DISABLED && fabsf(partner->pos.y - playerStatus->pos.y) > 1000.0f) {
        partner->pos.x = playerStatus->pos.x;
        partner->pos.y = playerStatus->pos.y;
        partner->pos.z = playerStatus->pos.z;
        partner->jumpVel = 0.0f;
        partner->jumpScale = 0.0f;
        partner->flags &= ~NPC_FLAG_JUMPING;
    }

    PartnerBlockedAbove = false;
    x = partner->pos.x;
    y = partner->pos.y + (partner->collisionHeight * 0.5f);
    z = partner->pos.z;
    hitDepth = partner->collisionHeight * 0.5f;

    if (npc_raycast_up(0, &x, &y, &z, &hitDepth)) {
        PartnerBlockedAbove = true;
        SavedPartnerPos.x = partner->pos.x;
        SavedPartnerPos.y = partner->pos.y;
        SavedPartnerPos.z = partner->pos.z;
        return;
    }

    partner_do_player_collision(partner);

    if (PartnerFollowState == PARTNER_MOVE_DISABLED) {
        SavedPartnerPos.x = partner->pos.x;
        SavedPartnerPos.y = partner->pos.y;
        SavedPartnerPos.z = partner->pos.z;
        return;
    }

    x = partner->pos.x;
    y = partner->pos.y;
    z = partner->pos.z;
    hitDepth = 1000.0f;

    if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter) == 0) {
        y = playerStatus->pos.y;
    }

    if (partner->pos.y <= y + partner->collisionHeight + 2.0f) {
        if (playerStatus->curSpeed != 0.0f) {
            PartnerFlyingDeltaY = ((y + (partner->collisionHeight / 2) + 2.0f) - partner->pos.y) * 0.125f;
        } else {
            if (y < playerStatus->pos.y) {
                targetY = playerStatus->pos.y + 10.0f;
            } else {
                targetY = y + 10.0f;
            }
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.25f;
        }
    } else {
        if (playerStatus->pos.y + playerStatus->colliderHeight < y) {
            targetY = y + partner->collisionHeight;
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.125f;

            if (partner->pos.y + PartnerFlyingDeltaY <= targetY) {
                PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.25f;
            }
        } else {
            targetY = playerStatus->pos.y + playerStatus->colliderHeight + 5.0f;
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.0625f;
        }
    }

    partner->pos.y += PartnerFlyingDeltaY;
    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;
}

void partner_flying_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[CAM_DEFAULT];
    f32 x, y, z;
    f32 distance;
    f32 yaw;
    f32 temp_a3;
    f32 temp_f0_15;
    f32 var_f12;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    PlayerPathElement* currentSnapshot;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            var_f12 = 0.0f;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            SavedPartnerPos.x = x;
            SavedPartnerPos.y = y;
            SavedPartnerPos.z = z;
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryY = currentSnapshot->pos.y;
            moveHistoryZ = currentSnapshot->pos.z;
            if (PartnerTetherDistance < 20.0f) {
                var_f12 = (20.0f - PartnerTetherDistance) * 0.5f;
            }
            partner->pos.y = y + (moveHistoryY + 20.0f + var_f12 - y) * 0.125f;
            partner->moveSpeed = 3.0f;
            y = partner->pos.y;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance >= 50.0) {
                if (partner->pos.y >= playerStatus->pos.y) {
                    partner->moveSpeed = distance * 0.25f;
                } else {
                    partner->moveSpeed = 8.0f;
                }
            }
            if (PartnerTetherDistance < 20.0f) {
                partner->moveSpeed = 4.0f;
            }

            while (true) {
                yaw = atan2(x, z, moveHistoryX, moveHistoryZ);
                distance = dist2D(x, z, moveHistoryX, moveHistoryZ);
                if (partner->moveSpeed < distance) {
                    if (partner->pos.y >= playerStatus->pos.y) {
                        if (partner->moveSpeed >= distance * 0.25f) {
                            partner->moveSpeed = distance * 0.25f;
                        } else {
                            partner->moveSpeed += distance * 0.0625f;
                        }
                    } else {
                        if (partner->moveSpeed > 6.0) {
                            partner->moveSpeed = 6.0f;
                        } else {
                            partner->moveSpeed += 1.0;
                        }
                    }
                    break;
                }
                if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                }
                distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                if (distance <= PartnerTetherDistance) {
                    PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                }
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryZ = currentSnapshot->pos.z;
            }
            partner->yaw = yaw;
            npc_move_heading(partner, partner->moveSpeed, yaw);
            if (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
                PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                return;
            }
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex) {
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryY = currentSnapshot->pos.y;
                moveHistoryZ = currentSnapshot->pos.z;
                partner->moveToPos.x = moveHistoryX;
                partner->moveToPos.y = moveHistoryY;
                partner->moveToPos.z = moveHistoryZ;
                partner->duration = 0;
                partner->jumpScale = 1.3f;
                if (PartnerFollowState == PARTNER_MOVE_BEGIN_JUMP) {
                    partner->moveSpeed = 6.0f;
                }
                partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                if (partner->planarFlyDist > 50.0) {
                    partner->planarFlyDist = 50.0f;
                }
                distance = partner->planarFlyDist;
                y = partner->moveToPos.y - partner->pos.y;
                if (partner->planarFlyDist < y) {
                    distance = y;
                }
                if (PartnerFollowState == PARTNER_MOVE_BEGIN_JUMP) {
                    if (distance < PartnerTetherDistance) {
                        partner->jumpVel = 0.0f;
                        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        return;
                    }
                    partner->duration = distance / partner->moveSpeed;
                    if (partner->duration < 10) {
                        partner->duration = 10;
                    }
                    partner->moveSpeed = partner->planarFlyDist / partner->duration;
                } else {
                    partner->duration = 10;
                }

                partner->jumpVel = (y + (partner->jumpScale * partner->duration * partner->duration * 0.5f)) / partner->duration;
                if (partner->jumpVel > 20.0) {
                    partner->jumpVel = 20.0f;
                }
                PartnerFollowState = PARTNER_MOVE_JUMPING;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
                partner->moveToPos.x = partner->pos.x;
                partner->moveToPos.y = partner->pos.y;
                partner->moveToPos.z = partner->pos.z;
            }
            break;
        case PARTNER_MOVE_JUMPING:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            if (partner->jumpVel <= 0.0f) {
                if (partner->pos.y < partner->moveToPos.y) {
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                    partner->jumpVel = 0.0f;
                    partner->pos.y = partner->moveToPos.y;
                    partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    if (distance < PartnerTetherDistance) {
                        PartnerFollowState = PARTNER_MOVE_TO_SIDE;
                    }
                }
            }
            break;
        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
                    partner->pos.y = y + (((playerStatus->pos.y + (playerStatus->colliderHeight - partner->collisionHeight / 2)) - partner->pos.y) * 0.03125);
                    y = partner->pos.y;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    if (playerStatus->actionState == ACTION_STATE_TALK) {
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    }
                } else {
                    temp_a3 = clamp_angle(camera->curYaw + (playerStatus->spriteFacingAngle < 180.0f ? 90.0f : -90.0f));
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, temp_a3);
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->moveSpeed = 2.0f;
                    if (distance > 2.0f) {
                        partner->yaw = yaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                        if (!(partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD)) {
                            PartnerStuckTime = 0;
                        } else {
                            PartnerStuckTime++;
                            if (PartnerStuckTime > 10) {
                                yaw = playerStatus->targetYaw;
                                partner->moveSpeed = 0.0f;
                                partner->jumpScale = 0.0f;
                                partner->renderYaw = yaw;
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                                }
                            }
                        }
                    } else {
                        yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        partner->yaw = yaw;
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                    partner->yaw = yaw;
                    npc_move_heading(partner, partner->moveSpeed, yaw);
                    return;
                }
            }

            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (!(distance <= PartnerTetherDistance)) {
                while (true) {
                    if (!currentSnapshot->isJumping) {
                        yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                        if (!(fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f)) {
                            if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex) {
                                PartnerMoveHistoryReadIndex++;
                                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                                    PartnerMoveHistoryReadIndex = 0;
                                }
                                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                                moveHistoryX = currentSnapshot->pos.x;
                                moveHistoryZ = currentSnapshot->pos.z;
                                continue;
                            }
                        }
                    }
                    break;
                }
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            }
            break;
        case PARTNER_MOVE_TO_SIDE:
            if (!(playerStatus->animFlags & PA_FLAG_CHANGING_MAP)) {
                switch (PartnerFollowSubstate) {
                    case 0:
                        temp_f0_15 = clamp_angle(player_get_side_angle() + 180.0f);
                        partner->moveToPos.x = playerStatus->pos.x;
                        partner->moveToPos.y = playerStatus->pos.y;
                        partner->moveToPos.z = playerStatus->pos.z;
                        add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, temp_f0_15);
                        distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        partner->moveSpeed = PartnerMoveSpeed = distance / PartnerMoveTime;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[(partner->moveSpeed < 4.0) ? PARTNER_ANIM_INDEX_WALK : PARTNER_ANIM_INDEX_RUN];
                        yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        partner->yaw = PartnerMoveYaw = yaw;
                        PartnerFollowSubstate = 1;
                        // fallthrough
                    case 1:
                        if (PartnerMoveTime != 0) {
                            x = partner->pos.x;
                            y = partner->pos.y + partner->collisionHeight;
                            z = partner->pos.z;
                            distance = partner->collisionHeight + 1;
                            PartnerMoveTime--;
                            if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) == 0) {
                                if (partner->collisionHeight + 5 < fabs((partner->pos.y - playerStatus->pos.y))) {
                                    partner->pos.y += (playerStatus->pos.y - partner->pos.y) / 10.0f;
                                }
                            } else {
                                partner->pos.y += (((playerStatus->pos.y + playerStatus->colliderHeight) - partner->pos.y) * 0.125f);
                            }
                            partner->moveSpeed = PartnerMoveSpeed;
                            partner->yaw = PartnerMoveYaw;
                            x = partner->pos.x;
                            y = partner->pos.y;
                            z = partner->pos.z;
                            if (npc_test_move_taller_with_slipping(0, &x, &y, &z, partner->moveSpeed, partner->yaw, partner->collisionHeight, partner->collisionDiameter)) {
                                partner->pos.x += (x - partner->pos.x) / 5.0f;
                                partner->pos.z += (z - partner->pos.z) / 5.0f;
                            } else {
                                npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                            }
                            return;
                        }
                        partner_clear_player_tracking(partner);
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        PartnerFollowSubstate = 0;
                        partner->yaw = clamp_angle((camera->curYaw + 270.0f) - playerStatus->spriteFacingAngle);
                }
            }
            break;
        case PARTNER_MOVE_TO_GOAL:
            partner_move_to_goal(partner, true);
            break;
        case PARTNER_MOVE_DISABLE_ASAP:
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            break;
        case PARTNER_MOVE_DISABLED:
            break;
    }
}

void partner_disable_ai_soon(void) {
    PartnerFollowState = PARTNER_MOVE_DISABLE_ASAP;
}

void partner_disable_ai(void) {
    PartnerFollowState = PARTNER_MOVE_DISABLED;
}

void enable_partner_ai(void) {
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    partner_clear_player_tracking(gPartnerNpc);

    if (!ActivePartner->isFlying) {
        partner_walking_enable(gPartnerNpc, false);
    } else {
        partner_flying_enable(gPartnerNpc, false);
    }
}

void partner_set_tether_distance(f32 dist) {
    PartnerTetherDistance = dist;
}

void partner_reset_tether_distance(void) {
    PartnerTetherDistance = 40.0f;
}

void partner_set_goal_pos(s32 x, s32 z) {
    PartnerMoveGoalX = x;
    PartnerMoveGoalZ = z;
}

void partner_set_forced_follow_mode(s32 mode) {
    PartnerForcedFollowMode = mode;
}

void partner_move_to_player_side(void) {
    PartnerFollowState = PARTNER_MOVE_TO_SIDE;
    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    PartnerMoveTime = 10;
    PartnerFollowSubstate = 0;
}

void partner_move_to_pos(s32 posX, s32 posZ) {
    partner_set_goal_pos(posX, posZ);
    PartnerFollowState = PARTNER_MOVE_TO_GOAL;
}

void partner_reset_ai_state(void) {
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    PartnerFollowSubstate = 0;
}

void partner_clear_player_tracking(Npc* partner) {
    PlayerPathElement* it = PlayerMoveHistory;
    s32 i;

    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++, it++) {
        it->pos.x = SavedPartnerPos.x;
        it->pos.y = SavedPartnerPos.y;
        it->pos.z = SavedPartnerPos.z;
        it->isJumping = false;
    }
}

void partner_do_player_collision(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 playerScreenX;
    f32 playerScreenY;
    f32 playerScreenZ;
    f32 partnerScreenX;
    f32 partnerScreenY;
    f32 partnerScreenZ;
    f32 W;

    transform_point(gCameras[CAM_DEFAULT].mtxPerspective,
                    playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z, 1.0f,
                    &playerScreenX, &playerScreenY, &playerScreenZ, &W);
    transform_point(gCameras[CAM_DEFAULT].mtxPerspective, partner->pos.x, partner->pos.y, partner->pos.z, 1.0f,
                    &partnerScreenX, &partnerScreenY, &partnerScreenZ, &W);
    playerScreenX = fabsf(playerScreenX - partnerScreenX);
    playerScreenY = fabsf(playerScreenY - partnerScreenY);
    playerScreenZ = fabsf(playerScreenZ - partnerScreenZ);
    if (playerScreenX <= (partner->collisionDiameter + playerStatus->colliderDiameter) * 0.9f &&
        playerScreenY <= partner->collisionHeight + playerStatus->colliderHeight && playerScreenZ <= 4.0)
    {
        npc_move_heading(partner, 1.0f,
                         atan2(playerStatus->pos.x, playerStatus->pos.z, partner->pos.x, partner->pos.z));
        add_vec2D_polar(&partner->pos.x, &partner->pos.z, 2.0f, gCameras[gCurrentCameraID].curYaw);
    }
}

void partner_move_to_goal(Npc* partner, s32 isFlying) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 x, y, z, temp;

    switch (PartnerFollowSubstate) {
        case 0:
            PartnerFollowSubstate++;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.x = PartnerMoveGoalX;
            partner->moveToPos.z = PartnerMoveGoalZ;
            PartnerMoveYaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = PartnerMoveYaw;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, 5.0f, PartnerMoveYaw);
            PartnerMoveTime = 18;
            temp = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->moveSpeed = PartnerMoveSpeed = temp / PartnerMoveTime;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
        case 1:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;
                if (!isFlying) {
                    if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                        partner->pos.y = playerStatus->pos.y;
                    }
                    if (partner->jumpVel != 0.0f) {
                        partner->jumpVel -= partner->jumpScale;
                        partner->pos.y += partner->jumpVel;
                        if (partner->jumpVel <= 0.0f) {
                            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                        }

                        if (partner->jumpVel <= 0.0f) {
                            temp = fabsf(partner->jumpVel) + partner->collisionHeight;
                            y = partner->pos.y + partner->collisionHeight;
                            x = partner->pos.x;
                            z = partner->pos.z;

                            if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &temp,
                                                       partner->yaw, partner->collisionDiameter) &&
                                (temp <= fabsf(partner->jumpVel) + 22.0f))
                            {
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                                    (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                                partner->jumpScale = 0.0f;
                                partner->jumpVel = 0.0f;
                                partner->pos.y = y;
                                partner->flags &= ~NPC_FLAG_JUMPING;
                            }
                        }
                    }
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->yaw = PartnerMoveYaw;
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                        (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                    npc_do_world_collision(partner);
                } else {
                    if (fabs(partner->pos.y - playerStatus->pos.y) > 5.0) {
                        partner->pos.y += (playerStatus->pos.y - partner->pos.y) * 0.5f;
                    }
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->yaw = PartnerMoveYaw;
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                }

                npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
            } else {
                partner->flags &= ~NPC_FLAG_IGNORE_WORLD_COLLISION;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                PartnerFollowSubstate++;
            }
            break;
        case 2:
            break;
    }
}
