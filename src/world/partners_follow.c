#include "common.h"
#include "world/partners.h"
#include "world/partners_internal.h"

void partner_flying_follow_player(Npc* partner);

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
BSS f32 PartnerFlyingDeltaY;

ALWAYS_INLINE void advance_write_history(void) {
    PlayerMoveHistoryIndex++;
    if (PlayerMoveHistoryIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
        PlayerMoveHistoryIndex = 0;
    }
}

ALWAYS_INLINE void advance_read_history(void) {
    PartnerMoveHistoryReadIndex++;
    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
        PartnerMoveHistoryReadIndex = 0;
    }
}

ALWAYS_INLINE PlayerPathElement* fetch_move_history(void) {
    return &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
}

ALWAYS_INLINE b32 is_surface_dangerous(HitID colliderID) {
    s32 surfaceType = get_collider_flags(colliderID) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
    return (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA);
}

void partner_walking_enable(Npc* partner, b32 val) {
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
    PlayerPathElement* currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];

    b32 isPlayerAirborne = playerStatus->flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING);
    b32 isLanding = (playerStatus->actionState == ACTION_STATE_LAND || playerStatus->actionState == ACTION_STATE_STEP_DOWN);
    b32 isPlayerJumping = isPlayerAirborne && !isLanding;

    // do not add snapshots while the player is mid-jump/fall
    if (currentSnapshot->isJumping && isPlayerJumping) {
        return;
    }

    // do not add snapshots with identical positions
    if (currentSnapshot->pos.x == playerStatus->pos.x
        && currentSnapshot->pos.y == playerStatus->pos.y
        && currentSnapshot->pos.z == playerStatus->pos.z
    ) {
        return;
    }

    // do not add new snapshots while the ring buffer is full
    // @bug will fail if partner has just wrapped around
    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex + 1) {
        return;
    }

    advance_write_history();
    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    currentSnapshot->pos.x = playerStatus->pos.x;
    currentSnapshot->pos.y = playerStatus->pos.y;
    currentSnapshot->pos.z = playerStatus->pos.z;
    currentSnapshot->isJumping = isPlayerJumping;
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

    partner_resolve_player_screen_overlap(partner);
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

void partner_move_state_move_to_goal(Npc* partner, s32 isFlying) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 x, y, z, hitDepth;
    f32 dist;

    switch (PartnerFollowSubstate) {
        case 0:
            PartnerFollowSubstate = 1;
            partner->moveToPos.x = PartnerMoveGoalX;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = PartnerMoveGoalZ;

            PartnerMoveYaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = PartnerMoveYaw;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, 5.0f, PartnerMoveYaw);

            PartnerMoveTime = 18;
            dist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->moveSpeed = PartnerMoveSpeed = dist / PartnerMoveTime;

            if (partner->moveSpeed < 4.0) {
                 partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
            } else {
                 partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
            }
            // fallthrough
        case 1:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;

                if (!isFlying) {
                    if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                        partner->pos.y = playerStatus->pos.y;
                    }
                    // while falling, check for a floor close enough to land on
                    if (partner->jumpVel != 0.0f) {
                        partner->jumpVel -= partner->jumpScale;
                        partner->pos.y += partner->jumpVel;
                        if (partner->jumpVel <= 0.0f) {
                            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                        }

                        if (partner->jumpVel <= 0.0f) {
                            hitDepth = fabsf(partner->jumpVel) + partner->collisionHeight;
                            x = partner->pos.x;
                            y = partner->pos.y + partner->collisionHeight;
                            z = partner->pos.z;

                            if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &hitDepth,
                                    partner->yaw, partner->collisionDiameter)
                                && (hitDepth <= fabsf(partner->jumpVel) + 22.0f)
                            ) {
                                // landed, snap to the floor height and resume walking motion
                                if (partner->moveSpeed < 4.0) {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
                                } else {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
                                }

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

                    if (partner->moveSpeed < 4.0) {
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
                    } else {
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
                    }
                    npc_do_world_collision(partner);
                } else {
                    // flying partners just drift toward playerY while moving laterally to the goal
                    if (fabs(partner->pos.y - playerStatus->pos.y) > 5.0) {
                        partner->pos.y += (playerStatus->pos.y - partner->pos.y) * 0.5f;
                    }
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->yaw = PartnerMoveYaw;
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                }

                if (partner->moveSpeed < 4.0) {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_WALK);
                } else {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_RUN);
                }
            } else {
                // movement is finished. leave the partner in an inert completed
                // substate until some external caller changes the follow state.
                partner->flags &= ~NPC_FLAG_IGNORE_WORLD_COLLISION;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                PartnerFollowSubstate = 2;
            }
            break;
        case 2:
            break;
    }
}

void partner_walking_state_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot = fetch_move_history();
    f32 moveHistoryX = currentSnapshot->pos.x;
    f32 moveHistoryZ = currentSnapshot->pos.z;
    f32 headingYaw;
    f32 playerDist;
    f32 targetDist;
    f32 newYaw;

    // base move speed
    partner->moveSpeed = 3.0f;

    // if too far away, increase speed to catch up
    playerDist = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
    if (playerDist >= 50.0) {
        if (playerStatus->animFlags & PA_FLAG_SPINNING) {
            partner->moveSpeed = 7.0f;
        } else {
            partner->moveSpeed = 5.0f;
        }
    }

    if (PartnerTetherDistance < 20.0) {
        partner->moveSpeed = 4.0f;
    }

    if (partner->flags & NPC_FLAG_GROUNDED) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
    } else {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
    }

    // this loop finds a history snapshot to move toward. if the current one will be
    // reached this frame, consider subsequent ones until we find a useful target,
    // catch up to the player, hit a jump marker, or detect a sharp turn.
    while (true) {
        targetDist = dist2D(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
        headingYaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);

        // if the current snapshot is farther than this frame's movement, keep it as
        // our movement target unless we're already within tether range.
        if (partner->moveSpeed < targetDist) {
            // if we're too far from the player, continue along with path quickly
            playerDist = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (playerDist >= 50.0) {
                break;
            }
            // apply clamped movement speed boost when outside the tether range, even if not 'very far' away
            if (playerDist > PartnerTetherDistance) {
                partner->moveSpeed = playerDist - PartnerTetherDistance;
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
                // partner is already close enough to the player.
                // stop moving and face the player while we consume stale history.
                partner->moveSpeed = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            }
        }

        // have we caught up to the player (exhausted the history buffer)?
        if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
            headingYaw = partner->yaw;
            partner->moveSpeed = 0.0f;
            partner->jumpScale = 0.0f;
            PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            break;
        }

        advance_read_history();
        currentSnapshot = fetch_move_history();
        moveHistoryX = currentSnapshot->pos.x;
        moveHistoryZ = currentSnapshot->pos.z;
        newYaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);

        // if the next snapshot is a sharp backward turn, abandon the history
        if (fabsf(get_clamped_angle_diff(partner->yaw, newYaw)) > 90.0f) {
            PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
            break;
        }

        // start jumping if the player did at this point in the history
        if ((partner->flags & NPC_FLAG_GROUNDED) && currentSnapshot->isJumping) {
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
            break;
        }
    }

    if (!(partner->flags & NPC_FLAG_GROUNDED)) {
        partner->moveSpeed *= 0.5f;
    }

    // move toward snapshot position
    partner->yaw = headingYaw;
    npc_move_heading(partner, partner->moveSpeed, partner->yaw);

    // interesting choice: not gated behind NPC_FLAG_GROUNDED
    if (partner->moveSpeed < 4.0) {
        npc_surface_spawn_fx(partner, SURFACE_INTERACT_WALK);
    } else {
        npc_surface_spawn_fx(partner, SURFACE_INTERACT_RUN);
    }

    if (((partner->flags & NPC_FLAG_GROUNDED) && (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD))
        || is_surface_dangerous(partner->curFloor)
    ) {
        if (!partner_can_move_over_collider(partner->curWall)) {
            advance_read_history();
            currentSnapshot = fetch_move_history();
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            if (fabsf(get_clamped_angle_diff(partner->yaw, atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ))) > 90.0f) {
                PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
            }
        } else {
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
        }
    }
}

void partner_walking_state_begin_jump(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    f32 toPlayerYaw;
    b32 damagingSurface;

    damagingSurface = is_surface_dangerous(partner->curFloor);

    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
        // don't know where to jump. no newer snapshots exist yet...
        if (damagingSurface) {
            // if standing on a damaging surface, escape with a short hop toward the player
            moveHistoryX = partner->pos.x;
            moveHistoryY = playerStatus->pos.y;
            moveHistoryZ = partner->pos.z;
            toPlayerYaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            add_vec2D_polar(&moveHistoryX, &moveHistoryZ, 6.0f, toPlayerYaw);
        } else {
            // wait for new player history
            return;
        }
    } else {
        advance_read_history();
        currentSnapshot = fetch_move_history();
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

    // don't bother jumping within the tether distance, resume following instead
    if (partner->planarFlyDist < PartnerTetherDistance && !damagingSurface) {
        partner->jumpVel = 0.0f;
        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
        return;
    }

    partner->duration = partner->planarFlyDist / partner->moveSpeed;
    if (partner->duration < 10) {
        partner->duration = 10;
    }
    partner->moveSpeed = partner->planarFlyDist / partner->duration;

    partner->jumpVel = calc_projectile_v0(partner->pos.y, partner->moveToPos.y, partner->jumpScale, partner->duration);
    if (partner->jumpVel > 20.0) {
        partner->jumpVel = 20.0f;
    }
    if (partner->jumpVel < 0.0) {
        partner->jumpVel = 0.0f;
    }

    if (damagingSurface) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].hurt;
    } else {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
    }

    // once jump parameters are calculated, we use moveToPos to store original 'jumped from' position
    partner->moveToPos.x = partner->pos.x;
    partner->moveToPos.y = partner->pos.y;
    partner->moveToPos.z = partner->pos.z;
    partner->flags |= NPC_FLAG_JUMPING;
    PartnerFollowState = PARTNER_MOVE_JUMPING;
}

void partner_walking_state_jump(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
    f32 x, y, z, hitDepth;
    f32 jumpDist;
    f32 yaw;

    // integrate
    partner->jumpVel -= partner->jumpScale;
    partner->pos.y += partner->jumpVel;
    if (partner->jumpVel <= 0.0f) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
    }

    // safeguard jumping out of the world
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

    // test for landing while falling
    if (partner->jumpVel <= 0.0f) {
        hitDepth = fabsf(partner->jumpVel) + 11.0f;
        x = partner->pos.x;
        y = partner->pos.y + hitDepth;
        z = partner->pos.z;
        if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter)) {
            if (hitDepth <= fabsf(partner->jumpVel) + 22.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->pos.y = y;
                partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
                npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;

                // jumps ending close to where they began indicate a pathing failure
                // recover by warping to a position near the player
                jumpDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                if (jumpDist < 5.0) {
                    partner->pos.x = playerStatus->pos.x;
                    partner->pos.y = playerStatus->pos.y;
                    partner->pos.z = playerStatus->pos.z;
                    yaw = clamp_angle((cam->curYaw + 90.0f) - playerStatus->spriteFacingAngle);
                    add_vec2D_polar(&partner->pos.x, &partner->pos.z, 5.0f, yaw);
                    PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                }
                return;
            }
        }
    }

    // move laterally
    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
}

void partner_walking_idle_near_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
    PlayerPathElement* currentSnapshot = fetch_move_history();
    f32 moveHistoryX = currentSnapshot->pos.x;
    f32 moveHistoryZ = currentSnapshot->pos.z;
    f32 testX, testY, testZ, hitDepth;
    f32 distToPlayer;
    f32 targetDist;
    f32 besideYaw;
    f32 yawToTarget;
    f32 yawToPlayer;

    distToPlayer = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);

    if (distToPlayer <= PartnerTetherDistance) {
        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
            // if we're not being forced, then just do nothing
            partner->moveSpeed = 0.0f;
            partner->jumpScale = 0.0f;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            // except on dangerous ground, try to get off that
            if (is_surface_dangerous(partner->curFloor)) {
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                return;
            }
        } else {
            // receiving a forced-follow, choose a position beside the player and move there
            if (playerStatus->spriteFacingAngle < 180.0f) {
                besideYaw = clamp_angle(cam->curYaw + 90.0f);
            } else {
                besideYaw = clamp_angle(cam->curYaw - 90.0f);
            }
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, besideYaw);

            targetDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->moveSpeed = 2.0f;

            if (targetDist > partner->moveSpeed) {
                // we wont get to the goal position this frame
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                if (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
                    PartnerStuckTime++;
                    if (PartnerStuckTime > 10) {
                        // if stuck for a long time, give up
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->yaw = playerStatus->targetYaw;
                        partner->renderYaw = playerStatus->targetYaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;

                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                        if (playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                } else {
                    PartnerStuckTime = 0;
                }
            } else {
                // close enough, end the forced-follow
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->moveSpeed = 0.0f;
                partner->jumpScale = 0.0f;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;

                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                }
                if (playerStatus->actionState == ACTION_STATE_TALK) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                }
            }

            // move laterally
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);

            if (partner->moveSpeed < 4.0) {
                npc_surface_spawn_fx(partner, SURFACE_INTERACT_WALK);
            } else {
                npc_surface_spawn_fx(partner, SURFACE_INTERACT_RUN);
            }

            // check whether the movement put us on dangerous ground
            hitDepth = 1000.0f;
            testX = partner->pos.x;
            testZ = partner->pos.z;
            testY = partner->pos.y + partner->collisionHeight;
            if (npc_raycast_down_around(partner->collisionChannel, &testX, &testY, &testZ, &hitDepth, partner->yaw, partner->collisionDiameter) != 0) {
                if (is_surface_dangerous(NpcHitQueryColliderID)) {
                    // the floor is dangerous, undo the forced-follow and cancel it
                    partner->yaw = clamp_angle(partner->yaw + 180.0f);
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
                    // if we can't move over this collision, repeat the request next frame
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                }
            }
        }
    } else {
        // outside the tether distance
        // advance through the move history until we find one either a jump or
        // a snapshot located in roughly the direction of the player
        while (true) {
            if (currentSnapshot->isJumping) {
                break;
            }
            yawToTarget = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
            yawToPlayer = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (fabsf(get_clamped_angle_diff(yawToTarget, yawToPlayer)) < 90.0f) {
                break;
            }
            if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                break;
            }
            advance_read_history();
            currentSnapshot = fetch_move_history();
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
        }

        // if it wasn't a jump, begin moving toward it
        if (!currentSnapshot->isJumping) {
            PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            return;
        }

        // now fast-forward through the history to find somewhere to jump to
        while (true) {
            if (!currentSnapshot->isJumping) {
                break;
            }
            yawToTarget = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
            yawToPlayer = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (fabsf(get_clamped_angle_diff(yawToTarget, yawToPlayer)) < 90.0f) {
                break;
            }
            if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                break;
            }
            advance_read_history();
            currentSnapshot = fetch_move_history();
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
        }

        PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
    }
}

void partner_walking_move_to_side(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
    f32 testX, testY, testZ;
    f32 distance;
    f32 sideYaw;

    switch (PartnerFollowSubstate) {
        case 0:
            // choose a position beside the player
            sideYaw = clamp_angle(player_get_side_angle() + 180.0f);
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, sideYaw);

            distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            PartnerMoveSpeed = distance / PartnerMoveTime;
            partner->moveSpeed = PartnerMoveSpeed;

            if (partner->moveSpeed < 4.0) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
            } else {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
            }

            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            PartnerMoveYaw = partner->yaw;
            PartnerFollowSubstate = 1;
            // fallthrough
        case 1:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;
                // complete jump arc if one is in progress
                if (partner->jumpScale != 0.0f) {
                    partner->jumpVel -= partner->jumpScale;
                    partner->pos.y += partner->jumpVel;
                    if (partner->jumpVel <= 0.0f) {
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                    }
                    if (partner->jumpVel <= 0.0f) {
                        distance = fabsf(partner->jumpVel) + 11.0f;
                        testX = partner->pos.x;
                        testY = partner->pos.y + distance;
                        testZ = partner->pos.z;
                        if (npc_raycast_down_around(partner->collisionChannel, &testX, &testY, &testZ, &distance,
                            partner->yaw, partner->collisionDiameter)
                        ) {
                            if (distance <= (fabsf(partner->jumpVel) + 22.0f)) {
                                if (partner->moveSpeed < 4.0) {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
                                } else {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
                                }

                                partner->jumpScale = 0.0f;
                                partner->jumpVel = 0.0f;
                                partner->pos.y = testY;
                                partner->flags &= ~NPC_FLAG_JUMPING;
                            }
                        }
                    }
                }

                // move laterally
                partner->moveSpeed = PartnerMoveSpeed;
                partner->yaw = PartnerMoveYaw;
                npc_move_heading(partner, partner->moveSpeed, partner->yaw);

                if (partner->moveSpeed < 4.0) {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_WALK);
                } else {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_RUN);
                }
            } else {
                partner_clear_player_tracking(partner);
                partner->moveSpeed = 0.0f;
                partner->jumpScale = 0.0f;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                partner->yaw = clamp_angle((cam->curYaw + 270.0f) - playerStatus->spriteFacingAngle);
                PartnerMoveTime = 30;
                PartnerFollowSubstate = 2;
            }
            break;
        case 2:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;
                break;
            }
            PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            PartnerFollowSubstate = 0;
    }

    return;
}

void partner_walking_disable_asap(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 x, y, z, hitDepth;

    if (partner->flags & NPC_FLAG_GROUNDED) {
        if (partner_can_move_over_collider(partner->curFloor)) {
            PartnerFollowState = PARTNER_MOVE_DISABLED;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
        } else {
            // @bug this loses the disable request. BEGIN_JUMP uses the normal partner
            // follow jump path, which lands into FOLLOW_PLAYER/IDLE_NEAR_PLAYER instead of
            // returning to DISABLE_ASAP or DISABLED.
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
        }
        return;
    }

    // continue jump motion
    partner->jumpScale = 3.0f;
    partner->jumpVel -= partner->jumpScale;
    partner->pos.y += partner->jumpVel;
    if (partner->jumpVel <= 0.0f) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
    }

    // safeguard jumping out of the world
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

    // disable on landing
    hitDepth = fabsf(partner->jumpVel) + 11.0f;
    x = partner->pos.x;
    y = partner->pos.y + hitDepth;
    z = partner->pos.z;
    if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter) != 0) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
        partner->flags &= ~NPC_FLAG_JUMPING;
        partner->jumpVel = 0.0f;
        partner->pos.y = y;
        partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
        npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
        PartnerFollowState = PARTNER_MOVE_DISABLED;
    }
}

void partner_walking_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
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
            partner_walking_state_follow_player(partner);
            break;

        case PARTNER_MOVE_BEGIN_JUMP:
            partner_walking_state_begin_jump(partner);
            if (PartnerFollowState != PARTNER_MOVE_JUMPING) {
                break;
            }
            // fallthrough
        case PARTNER_MOVE_JUMPING:
            partner_walking_state_jump(partner);
            break;

        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            partner_walking_idle_near_player(partner);
            break;

        case PARTNER_MOVE_TO_SIDE:
            partner_walking_move_to_side(partner);
            break;

        case PARTNER_MOVE_TO_GOAL:
            partner_move_state_move_to_goal(partner, false);
            break;

        case PARTNER_MOVE_DISABLE_ASAP:
            partner_walking_disable_asap(partner);
            break;

        case PARTNER_MOVE_DISABLED:
            break;
    }
}

void partner_flying_enable(Npc* partner, b32 val) {
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

    if (val) {
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
    } else {
        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
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
    PlayerPathElement* currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    f32 effectiveY = playerStatus->pos.y;
    b32 isPlayerJumping = false;

    if ((playerStatus->actionState == ACTION_STATE_HIT_LAVA) || (playerStatus->actionState == ACTION_STATE_HIT_FIRE)) {
        effectiveY = playerStatus->lastGoodPos.y + partner->collisionHeight + 5;
    }

    // do not add snapshots with identical positions
    if (currentSnapshot->pos.x == playerStatus->pos.x
        && currentSnapshot->pos.y == effectiveY
        && currentSnapshot->pos.z == playerStatus->pos.z
    ) {
        return;
    }

    // note: isPlayerJumping is always false here
    if (currentSnapshot->isJumping && isPlayerJumping) {
        return;
    }

    // do not add new snapshots while the ring buffer is full
    // @bug will fail if partner has just wrapped around
    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex + 1) {
        return;
    }

    advance_write_history();
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

    partner_resolve_player_screen_overlap(partner);

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

void partner_flying_state_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    f32 headingYaw;
    f32 distance;

    f32 tetherOffsetY = 0.0f;

    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;

    currentSnapshot = fetch_move_history();
    moveHistoryX = currentSnapshot->pos.x;
    moveHistoryY = currentSnapshot->pos.y;
    moveHistoryZ = currentSnapshot->pos.z;

    // when the tether is very short, fly slightly higher to stay out of the way
    if (PartnerTetherDistance < 20.0f) {
        tetherOffsetY = (20.0f - PartnerTetherDistance) * 0.5f;
    }

    // smoothly approach a height above the current target
    partner->pos.y += ((moveHistoryY - partner->pos.y) + 20.0f + tetherOffsetY) * 0.125f;

    // set base move speed
    partner->moveSpeed = 3.0f;

    // if too far away, increase speed to catch up
    distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
    if (distance >= 50.0) {
        if (partner->pos.y >= playerStatus->pos.y) {
            partner->moveSpeed = distance * 0.25f;
        } else {
            partner->moveSpeed = 8.0f;
        }
    }

    // use a faster fixed speed when tether is short
    if (PartnerTetherDistance < 20.0f) {
        partner->moveSpeed = 4.0f;
    }

    // find a history snapshot to move toward. if the current one will be reached
    // this frame, consume history until we find a useful target, catch up to the
    // player, or enter idle near the player.
    while (true) {
        distance = dist2D(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
        headingYaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);

        // if the current snapshot is farther than this frame's movement, keep it
        // as our movement target and adjust speed for flying catch-up.
        if (partner->moveSpeed < distance) {
            if (partner->pos.y >= playerStatus->pos.y) {
                // while above the player, scale speed with distance
                if (partner->moveSpeed >= distance * 0.25f) {
                    partner->moveSpeed = distance * 0.25f;
                } else {
                    partner->moveSpeed += distance * 0.0625f;
                }
            } else {
                // while below the player, catch up more aggressively
                if (partner->moveSpeed > 6.0) {
                    partner->moveSpeed = 6.0f;
                } else {
                    partner->moveSpeed += 1.0;
                }
            }
            break;
        }

        // no more history to consume
        if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
            headingYaw = partner->yaw;
            partner->moveSpeed = 0.0f;
            partner->jumpScale = 0.0f;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            break;
        }

        // if we're back inside tether range, stop following history and idle
        distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
        if (distance <= PartnerTetherDistance) {
            PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
            headingYaw = partner->yaw;
            partner->moveSpeed = 0.0f;
            partner->jumpScale = 0.0f;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            break;
        }

        // try the next snapshot
        advance_read_history();
        currentSnapshot = fetch_move_history();
        moveHistoryX = currentSnapshot->pos.x;
        moveHistoryZ = currentSnapshot->pos.z;
    }

    // move laterally toward the selected history snapshot
    partner->yaw = headingYaw;
    npc_move_heading(partner, partner->moveSpeed, partner->yaw);

    if (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
        PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
        return;
    }
}

// flying partners use PARTNER_MOVE_BEGIN_JUMP to resolve collisions while pathing,
// not in response to the player jumping.
void partner_flying_state_begin_jump(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot;
    f32 deltaY;
    f32 distance;

    // wait for a new snapshot if none are available
    // we need one to use as the destination for our jump
    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
        return;
    }

    advance_read_history();
    currentSnapshot = fetch_move_history();
    partner->moveToPos.x = currentSnapshot->pos.x;
    partner->moveToPos.y = currentSnapshot->pos.y;
    partner->moveToPos.z = currentSnapshot->pos.z;

    partner->duration = 0;
    partner->jumpScale = 1.3f;
    partner->moveSpeed = 6.0f;

    // determine lateral jump length
    partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
    partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
    if (partner->planarFlyDist > 50.0f) {
        partner->planarFlyDist = 50.0f;
    }

    // use whichever is larger: horizontal distance or upward height delta
    distance = partner->planarFlyDist;
    deltaY = partner->moveToPos.y - partner->pos.y;
    if (partner->planarFlyDist < deltaY) {
        distance = deltaY;
    }

    // if the jump target is already inside tether range, cancel the jump and idle
    if (distance < PartnerTetherDistance) {
        partner->jumpVel = 0.0f;
        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
        return;
    }

    // solve a duration and speed for the jump, imposing a minimum duration
    partner->duration = distance / partner->moveSpeed;
    if (partner->duration < 10) {
        partner->duration = 10;
    }
    partner->moveSpeed = partner->planarFlyDist / partner->duration;

    partner->jumpVel = calc_projectile_v0(partner->pos.y, partner->moveToPos.y, partner->jumpScale, partner->duration);
    if (partner->jumpVel > 20.0) {
        partner->jumpVel = 20.0f;
    }

    partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;

    // store starting location in moveToPos, ready to jump
    partner->moveToPos.x = partner->pos.x;
    partner->moveToPos.y = partner->pos.y;
    partner->moveToPos.z = partner->pos.z;
    PartnerFollowState = PARTNER_MOVE_JUMPING;
}

void partner_flying_state_jump(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 moveDist;

    // integrate
    partner->jumpVel -= partner->jumpScale;
    partner->pos.y += partner->jumpVel;

    if (partner->jumpVel <= 0.0f) {
        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
    }

    // move laterally
    npc_move_heading(partner, partner->moveSpeed, partner->yaw);

    // check for jump completion
    if (partner->jumpVel <= 0.0f) {
        if (partner->pos.y < partner->moveToPos.y) {
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
            partner->jumpVel = 0.0f;
            partner->pos.y = partner->moveToPos.y;
            partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;

            // jumps ending close to where they began indicate a pathing failure
            // recover by warping to a position near the player
            moveDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            if (moveDist < PartnerTetherDistance) {
                PartnerFollowState = PARTNER_MOVE_TO_SIDE;
            }
        }
    }
}

void partner_flying_state_idle_near_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
    PlayerPathElement* currentSnapshot = fetch_move_history();
    f32 moveHistoryX = currentSnapshot->pos.x;
    f32 moveHistoryZ = currentSnapshot->pos.z;
    f32 targetY;
    f32 distToPlayer;
    f32 targetDist;
    f32 besideYaw;
    f32 yawToTarget;
    f32 yawToPlayer;

    distToPlayer = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);

    if (distToPlayer <= PartnerTetherDistance) {
        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
            // hover near the player's upper body while idling
            targetY = playerStatus->pos.y + (playerStatus->colliderHeight - partner->collisionHeight / 2);
            partner->pos.y += (targetY - partner->pos.y) * 0.03125;
            partner->moveSpeed = 0.0f;
            partner->jumpScale = 0.0f;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            if (playerStatus->actionState == ACTION_STATE_TALK) {
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            }
        } else {
            // move beside the player in forced-follow mode
            if (playerStatus->spriteFacingAngle < 180.0f) {
                besideYaw = clamp_angle(cam->curYaw + 90.0f);
            } else {
                besideYaw = clamp_angle(cam->curYaw - 90.0f);
            }
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, besideYaw);

            targetDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->moveSpeed = 2.0f;

            if (targetDist > partner->moveSpeed) {
                // we wont get to the goal position this frame
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                if (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
                    PartnerStuckTime++;
                    if (PartnerStuckTime > 10) {
                        // if stuck for a long time, give up
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->yaw = playerStatus->targetYaw;
                        partner->renderYaw = playerStatus->targetYaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;

                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                        if (playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                } else {
                    PartnerStuckTime = 0;
                }
            } else {
                // close enough, end the forced-follow
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->moveSpeed = 0.0f;
                partner->jumpScale = 0.0f;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;

                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                }
                if (playerStatus->actionState == ACTION_STATE_TALK) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                }
            }

            // move laterally
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
        }
    } else {
        // outside the tether distance
        // advance through the move history until we find one either a jump or
        // a snapshot located in roughly the direction of the player
        while (true) {
            if (currentSnapshot->isJumping) {
                break;
            }
            yawToTarget = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
            yawToPlayer = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (fabsf(get_clamped_angle_diff(yawToTarget, yawToPlayer)) < 90.0f) {
                break;
            }
            if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                break;
            }
            advance_read_history();
            currentSnapshot = fetch_move_history();
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
        }

        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    }
}

void partner_flying_state_move_to_side(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cam = &gCameras[CAM_DEFAULT];
    f32 testX, testY, testZ;
    f32 distance;
    f32 sideYaw;

    if (playerStatus->animFlags & PA_FLAG_CHANGING_MAP) {
        return;
    }

    switch (PartnerFollowSubstate) {
        case 0:
            // choose a position beside the player
            sideYaw = clamp_angle(player_get_side_angle() + 180.0f);
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, sideYaw);

            distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            PartnerMoveSpeed = distance / PartnerMoveTime;
            partner->moveSpeed = PartnerMoveSpeed;

            if (partner->moveSpeed < 4.0) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_WALK];
            } else {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PARTNER_ANIM_INDEX_RUN];
            }

            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            PartnerMoveYaw = partner->yaw;
            PartnerFollowSubstate = 1;
            // fallthrough
        case 1:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;

                // adjust height while moving
                testX = partner->pos.x;
                testY = partner->pos.y + partner->collisionHeight;
                testZ = partner->pos.z;
                distance = partner->collisionHeight + 1;
                if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &testX, &testY, &testZ, &distance, partner->yaw, partner->collisionDiameter)) {
                    // if there is floor below, drift toward the player's upper body
                    partner->pos.y += ((playerStatus->pos.y + playerStatus->colliderHeight) - partner->pos.y) * 0.125f;
                } else {
                    // if there is no nearby floor below, only drift toward the player's Y when the partner is far from it
                    if (partner->collisionHeight + 5 < fabs((partner->pos.y - playerStatus->pos.y))) {
                        partner->pos.y += (playerStatus->pos.y - partner->pos.y) / 10.0f;
                    }
                }

                // use the precomputed lateral movement by default
                partner->moveSpeed = PartnerMoveSpeed;
                partner->yaw = PartnerMoveYaw;

                // try a taller collision sweep, limiting the motion if it hits
                testX = partner->pos.x;
                testY = partner->pos.y;
                testZ = partner->pos.z;
                if (npc_test_move_taller_with_slipping(0, &testX, &testY, &testZ, partner->moveSpeed, partner->yaw, partner->collisionHeight, partner->collisionDiameter)) {
                    partner->pos.x += (testX - partner->pos.x) / 5.0f;
                    partner->pos.z += (testZ - partner->pos.z) / 5.0f;
                } else {
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                }
            } else {
                partner_clear_player_tracking(partner);
                partner->moveSpeed = 0.0f;
                partner->jumpScale = 0.0f;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                PartnerFollowSubstate = 0;
                partner->yaw = clamp_angle((cam->curYaw + 270.0f) - playerStatus->spriteFacingAngle);
            }
    }
}

void partner_flying_follow_player(Npc* partner) {
    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            partner_flying_state_follow_player(partner);
            break;

        case PARTNER_MOVE_BEGIN_JUMP:
            partner_flying_state_begin_jump(partner);
            break;

        case PARTNER_MOVE_JUMPING:
            partner_flying_state_jump(partner);
            break;

        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            partner_flying_state_idle_near_player(partner);
            break;

        case PARTNER_MOVE_TO_SIDE:
            partner_flying_state_move_to_side(partner);
            break;

        case PARTNER_MOVE_TO_GOAL:
            partner_move_state_move_to_goal(partner, true);
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

    if (ActivePartner->isFlying) {
        partner_flying_enable(gPartnerNpc, false);
    } else {
        partner_walking_enable(gPartnerNpc, false);
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
    s32 i;

    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++) {
        PlayerMoveHistory[i].pos.x = SavedPartnerPos.x;
        PlayerMoveHistory[i].pos.y = SavedPartnerPos.y;
        PlayerMoveHistory[i].pos.z = SavedPartnerPos.z;
        PlayerMoveHistory[i].isJumping = false;
    }
}

// computes screen space positions of the player and partner, nudging the partner away from the player if they overlap
void partner_resolve_player_screen_overlap(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 playerScreenX, playerScreenY, playerScreenZ;
    f32 partnerScreenX, partnerScreenY, partnerScreenZ;
    f32 awayPlayerYaw;
    f32 W;

    transform_point(gCameras[CAM_DEFAULT].mtxPerspective,
        playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z, 1.0f,
        &playerScreenX, &playerScreenY, &playerScreenZ, &W);

    transform_point(gCameras[CAM_DEFAULT].mtxPerspective,
        partner->pos.x, partner->pos.y, partner->pos.z, 1.0f,
        &partnerScreenX, &partnerScreenY, &partnerScreenZ, &W);

    playerScreenX = fabsf(playerScreenX - partnerScreenX);
    playerScreenY = fabsf(playerScreenY - partnerScreenY);
    playerScreenZ = fabsf(playerScreenZ - partnerScreenZ);

    if (playerScreenX <= (partner->collisionDiameter + playerStatus->colliderDiameter) * 0.9f
        && playerScreenY <= partner->collisionHeight + playerStatus->colliderHeight
        && playerScreenZ <= 4.0
    ) {
        awayPlayerYaw = atan2(playerStatus->pos.x, playerStatus->pos.z, partner->pos.x, partner->pos.z);
        npc_move_heading(partner, 1.0f, awayPlayerYaw);
        add_vec2D_polar(&partner->pos.x, &partner->pos.z, 2.0f, gCameras[gCurrentCameraID].curYaw);
    }
}
