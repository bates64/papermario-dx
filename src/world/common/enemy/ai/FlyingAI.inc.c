#pragma once

// This AI is used by:
// - Paragoomba + variants
// - Paratroopa + variants
// - Sky Guy
// - Bzzap

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

enum FlyingAiStates {
    // basic flying enemies wander about and occasionally loiter
    AI_STATE_FLYING_WANDER_INIT            = 0,
    AI_STATE_FLYING_WANDER                 = 1,
    AI_STATE_FLYING_LOITER_INIT            = 2,
    AI_STATE_FLYING_LOITER                 = 3,
    // alerted flying enemies perform a short upward aerial 'hop' over 5 frames
    AI_STATE_FLYING_ALERT_INIT             = 10,
    AI_STATE_FLYING_ALERT                  = 11,
    // while chasing, flying enemies swoop toward the player (after optional delay)
    AI_STATE_FLYING_CHASE_INIT             = 12,
    AI_STATE_FLYING_CHASE_DELAY            = 13,
    AI_STATE_FLYING_CHASE                  = 14,
};

enum FlyingAiVars {
    AI_VAR_FLYING_FLAGS             = 0, // IN: see: FlyingAiFlags
    AI_VAR_FLYING_BOB_AMPLITUDE     = 1, // IN: (packed float) amplitude of bobbing during wander and loiter
    AI_VAR_FLYING_BOB_PHASE         = 2,
    AI_VAR_FLYING_HOVER_HEIGHT      = 3, // height above ground at initial position
    AI_VAR_FLYING_PREV_Y            = 4, // (packed float) prev value used for interpolation
    AI_VAR_FLYING_CHASE_VELY        = 5, // IN: (packed float) y velocity to use during chase swoop
    AI_VAR_FLYING_CHASE_ACCEL       = 6, // IN: (packed float) y acceleration to use during chase swoop
    AI_VAR_FLYING_HOVER_BASE        = 7, // (packed float) y level of ground under initial position
    AI_VAR_FLYING_DETECT_COOLDOWN   = 9, // time before next player can be detected
};

enum FlyingAiFlags {
    AI_FLYING_FLAG_INTERPY          = 0x01,
    AI_FLYING_FLAG_INTERPOLATING    = 0x10,
    AI_FLYING_FLAG_MASK             = 0x11,
};

enum FlyingAiAnims {
    AI_ANIM_FLYING_DIVE             = 8,
    AI_ANIM_FLYING_POST_DIVE        = 9,
};

f32 N(FlyingAI_JumpVels)[] = {
    4.5, 3.5, 2.6, 2.0, 1.5,
};

void N(FlyingAI_WanderInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = settings->moveTime / 2 + rand_int(settings->moveTime / 2 + 1);
    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
    } else {
        npc->yaw = clamp_angle((npc->yaw + rand_int(60)) - 30.0f);
    }
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    script->functionTemp[1] = 0;
    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = settings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
    enemy->varTable[AI_VAR_FLYING_PREV_Y] = AI_PACK_FLT(npc->pos.y);
    script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER;
}

void N(FlyingAI_Wander)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    b32 shouldReturn = false;
    f32 hoverBase = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_BASE]);
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 prevY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_PREV_Y]);
    f32 bobAmplitude = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE]);
    f32 posX, posY, posZ, hitDepth;
    f32 hoverY;

    enemy->varTable[AI_VAR_FLYING_PREV_Y] = AI_PACK_FLT(npc->pos.y);

    hoverY = hoverBase + hoverHeight;

    if ((enemy->varTable[AI_VAR_FLYING_FLAGS] & AI_FLYING_FLAG_MASK) == AI_FLYING_FLAG_INTERPY) {
        if (npc->flags & NPC_FLAG_FLYING) {
            if (bobAmplitude < hoverY - npc->pos.y) {
                enemy->varTable[AI_VAR_FLYING_FLAGS] |= AI_FLYING_FLAG_INTERPOLATING;
            }
        } else {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            hitDepth = 1000.0f;
            npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
            if (bobAmplitude < (hoverHeight - hitDepth)) {
                enemy->varTable[AI_VAR_FLYING_FLAGS] |= AI_FLYING_FLAG_INTERPOLATING;
            }
        }
    }

    if ((enemy->varTable[AI_VAR_FLYING_FLAGS] & AI_FLYING_FLAG_MASK) == (AI_FLYING_FLAG_INTERPY | AI_FLYING_FLAG_INTERPOLATING)) {
        f32 targetY;

        if (npc->flags & NPC_FLAG_FLYING) {
            targetY = hoverY;
            npc->pos.y = prevY + ((targetY - prevY) * 0.09);
        } else {
            posX = npc->pos.x;
            posY = prevY;
            posZ = npc->pos.z;
            hitDepth = 1000.0f;
            npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);

            targetY = posY + hoverHeight;
            npc->pos.y = prevY + ((targetY - prevY) * 0.09);
        }

        if (fabsf(targetY - npc->pos.y) < 1.0) {
            npc->pos.y = targetY;
            enemy->varTable[AI_VAR_FLYING_FLAGS] &= ~AI_FLYING_FLAG_INTERPOLATING;
        }
    } else {
        if (enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE] > 0) {
            f32 bobAmount = sin_deg(enemy->varTable[AI_VAR_FLYING_BOB_PHASE]);
            b32 hit;

            if (npc->flags & NPC_FLAG_FLYING) {
                hit = false;
            } else {
                posX = npc->pos.x;
                posY = npc->pos.y;
                posZ = npc->pos.z;
                hitDepth = 1000.0f;
                hit = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
            }

            if (hit) {
                npc->pos.y = posY + hoverHeight + (bobAmount * bobAmplitude);
            } else {
                npc->pos.y = hoverY + (bobAmount * bobAmplitude);
            }

            enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYING_BOB_PHASE] + 10);
        }
    }

    if (enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN] <= 0) {
        if (settings->playerSearchInterval >= 0) {
            if (script->functionTemp[1] <= 0) {
                script->functionTemp[1] = settings->playerSearchInterval;
                if (gPlayerStatusPtr->pos.y < (npc->pos.y + npc->collisionHeight) + 10.0 &&
                    basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, 0))
                {
                    fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
                    npc->moveToPos.y = npc->pos.y;
                    ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);

                    if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                        script->AI_TEMP_STATE = AI_STATE_FLYING_ALERT_INIT;
                    } else {
                        script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_INIT;
                    }
                    return;
                }
            }
            script->functionTemp[1]--;
        }
    } else {
        enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN]--;
    }

    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        hitDepth = dist2D(enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z, npc->pos.x, npc->pos.z);
        if (npc->moveSpeed < hitDepth) {
            npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
            shouldReturn = true;
        }
    }

    if ((enemy->territory->wander.wanderSize.x != 0) || (enemy->territory->wander.wanderSize.z != 0) || shouldReturn) {
        if (npc->turnAroundYawAdjustment != 0) {
            return;
        }
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }

    enemy->varTable[AI_VAR_FLYING_PREV_Y] = AI_PACK_FLT(npc->pos.y);
    if (settings->moveTime > 0) {
        if (npc->duration > 0) {
            npc->duration--;
        }

        if (npc->duration <= 0) {
            script->AI_TEMP_STATE = AI_STATE_FLYING_LOITER_INIT;
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;
            if (settings->loiterMode <= 0 || settings->waitTime <= 0 || script->functionTemp[1] < 3) {
                script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
            }
        }
    }
}

void N(FlyingAI_LoiterInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (settings->waitTime / 2) + rand_int((settings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_FLYING_LOITER;
}

void N(FlyingAI_Loiter)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 hoverBase = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_BASE]);
    f32 posX, posY, posZ, hitDepth;

    if (npc->duration > 0) {
        npc->duration--;
    }

    // calculate new height with bobbing added in
    if (enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE] > 0) {
        f32 bobAmplitude = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE]);
        f32 bobAmount = sin_deg(enemy->varTable[AI_VAR_FLYING_BOB_PHASE]);
        b32 hasCollision;

        if (npc->flags & NPC_FLAG_FLYING) {
            hasCollision = false;
        } else {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            hitDepth = 1000.0f;
            hasCollision = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
        }

        if (hasCollision) {
            npc->pos.y = posY + hoverHeight + (bobAmount * bobAmplitude);
        } else {
            npc->pos.y = hoverBase + hoverHeight + (bobAmount * bobAmplitude);
        }

        enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYING_BOB_PHASE] + 10);
    }

    // try player detection
    if (enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN] <= 0) {
        if ((gPlayerStatusPtr->pos.y < npc->pos.y + npc->collisionHeight + 10.0)
            && basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
            fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
            npc->moveToPos.y = npc->pos.y;
            ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
            if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                script->AI_TEMP_STATE = AI_STATE_FLYING_ALERT_INIT;
            } else {
                script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_INIT;
            }
            return;
        }
    } else {
        enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN]--;
    }

    // try looking around
    if ((npc->turnAroundYawAdjustment == 0) && (npc->duration <= 0)) {
        script->functionTemp[1]--;
        if (script->functionTemp[1] > 0) {
            if (!(enemy->npcSettings->actionFlags & AI_ACTION_LOOK_AROUND_DURING_LOITER)) {
                npc->yaw = clamp_angle(npc->yaw + 180.0f);
            }
            npc->duration = (rand_int(1000) % 11) + 5;
        } else {
            script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
        }
    }
}

void N(FlyingAI_JumpInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 0;
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->curAnim = enemy->animList[AI_ANIM_FLYING_DIVE];
    script->AI_TEMP_STATE = AI_STATE_FLYING_ALERT;
}

void N(FlyingAI_Jump)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->pos.y += N(FlyingAI_JumpVels)[npc->duration++];
    if (npc->duration >= ARRAY_COUNT(N(FlyingAI_JumpVels))) {
        script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_INIT;
    }
}

void N(FlyingAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 jumpVel = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_CHASE_VELY]);
    f32 jumpScale = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_CHASE_ACCEL]);

    npc->curAnim = enemy->animList[AI_ANIM_FLYING_DIVE];
    npc->jumpVel = jumpVel;
    npc->jumpScale = jumpScale;
    npc->moveSpeed = settings->chaseSpeed;
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);

    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = 0;

    if (enemy->npcSettings->actionFlags & AI_ACTION_NO_FIRST_STRIKE) {
        npc->duration = 3;
        script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_DELAY;
    } else {
        npc->duration = 1;
        script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE;
        enemy->attackOriginPos.x = npc->pos.x;
        enemy->attackOriginPos.y = npc->pos.y;
        enemy->attackOriginPos.z = npc->pos.z;
        enemy->firstStrikeActive = true;
    }
}

void N(FlyingAI_ChaseDelay)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    if (npc->duration > 0) {
        npc->duration--;
    }

    if (npc->duration <= 0) {
        if (npc->turnAroundYawAdjustment == 0) {
            npc->duration = 0;
            script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE;
        }
    }
}

void N(FlyingAI_Chase)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ, hitDepth;
    f32 deltaAngle;
    b32 hasGroundBelow;
    f32 angle;
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 hoverBase = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_BASE]);

    npc->jumpVel += npc->jumpScale;
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    if (npc->jumpVel >= 0.0) {
        npc->pos.y += npc->jumpVel;
        npc->curAnim = enemy->animList[AI_ANIM_FLYING_POST_DIVE];
        enemy->firstStrikeActive = false;
        if (!(npc->flags & NPC_FLAG_FLYING)) {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            hitDepth = 1000.0f;
            hasGroundBelow = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
        } else {
            hasGroundBelow = false;
        }
        if (hasGroundBelow) {
            if (posY + hoverHeight <= npc->pos.y) {
                npc->pos.y = posY + hoverHeight;
                script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
            }
        } else if (npc->pos.y >= npc->moveToPos.y) {
            script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
        }
    } else if (npc->jumpVel < 0.0) {
        npc->duration++;
        if (npc->duration >= settings->chaseUpdateInterval) {
            npc->duration = 0;

            angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            deltaAngle = get_clamped_angle_diff(npc->yaw, angle);

            // cap the turn rate
            if (settings->chaseTurnRate < fabsf(deltaAngle)) {
                if (deltaAngle < 0.0f) {
                    angle = npc->yaw - settings->chaseTurnRate;
                } else {
                    angle = npc->yaw + settings->chaseTurnRate;
                }
            }
            npc->yaw = clamp_angle(angle);
        }

        if (npc->flags & NPC_FLAG_FLYING) {
            if (npc->pos.y + npc->jumpVel < hoverBase) {
                npc->pos.y = hoverBase;
                npc->jumpVel = 0.0f;
            } else {
                npc->pos.y += npc->jumpVel;
            }
            return;
        }

        posX = npc->pos.x;
        posY = npc->pos.y + npc->collisionHeight;
        posZ = npc->pos.z;
        hitDepth = (fabsf(npc->jumpVel) + npc->collisionHeight) + 10.0;
        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth)) {
            if (hitDepth <= (npc->collisionHeight + fabsf(npc->jumpVel))) {
                npc->jumpVel = 0.0f;
                npc->pos.y = posY;
            } else {
                npc->pos.y += npc->jumpVel;
            }
            return;
        } else if (fabsf(npc->jumpVel) < ((npc->pos.y - hoverBase) + npc->collisionHeight)) {
            npc->pos.y = npc->pos.y + npc->jumpVel;
            return;
        }
        npc->jumpVel = 0.0f;
    }
}

void N(FlyingAI_Init)(Npc* npc, Enemy* enemy, Evt* script, MobileAISettings* settings) {
    f32 posX, posY, posZ, depth;

    script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    npc->duration = 0;

    npc->flags &= ~NPC_FLAG_GRAVITY;
    npc->flags |= NPC_FLAG_JUMPING;
    if (enemy->territory->wander.isFlying) {
        npc->flags |= NPC_FLAG_FLYING;
    } else {
        npc->flags &= ~NPC_FLAG_FLYING;
    }

    posX = npc->pos.x;
    posY = npc->pos.y;
    posZ = npc->pos.z;
    depth = 1000.0f;
    npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &depth);

    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = 0;
    enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN] = 0;
    enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT] = AI_CEIL_FLT(depth);
    enemy->varTable[AI_VAR_FLYING_HOVER_BASE] = AI_CEIL_FLT(posY);
    script->functionTemp[1] = settings->playerSearchInterval;
    enemy->aiFlags |= AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE;
}

API_CALLABLE(N(FlyingAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 120.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        N(FlyingAI_Init)(npc, enemy, script, settings);
    }

    npc->verticalRenderOffset = -2;

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_FLYING_WANDER_INIT:
            N(FlyingAI_WanderInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_FLYING_WANDER:
            N(FlyingAI_Wander)(script, settings, detect);
            break;

        case AI_STATE_FLYING_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_FLYING_LOITER:
            N(FlyingAI_Loiter)(script, settings, detect);
            break;

        case AI_STATE_FLYING_ALERT_INIT:
            N(FlyingAI_JumpInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_FLYING_ALERT:
            N(FlyingAI_Jump)(script, settings, detect);
            break;

        case AI_STATE_FLYING_CHASE_INIT:
            N(FlyingAI_ChaseInit)(script, settings, detect);
            break;

        case AI_STATE_FLYING_CHASE_DELAY:
            N(FlyingAI_ChaseDelay)(script, settings, detect);
            break;

        case AI_STATE_FLYING_CHASE:
            N(FlyingAI_Chase)(script, settings, detect);
            break;
    }

    return ApiStatus_BLOCK;
}
