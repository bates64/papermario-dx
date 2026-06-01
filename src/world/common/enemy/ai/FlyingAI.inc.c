// This AI is used by:
// - Paragoomba + variants
// - Paratroopa + variants
// - Sky Guy
// - Bzzap

#ifndef _AI_FLYING_INC_
#define _AI_FLYING_INC_ 0

#include "common.h"
#include "npc.h"
#include "effects.h"

enum AiStateFlying {
    // basic flying enemies wander about and occasionally loiter
    AI_FLYING_STATE_WANDER_INIT            = 0,
    AI_FLYING_STATE_WANDER                 = 1,
    AI_FLYING_STATE_LOITER_INIT            = 2,
    AI_FLYING_STATE_LOITER                 = 3,
    // alerted flying enemies perform a short upward aerial 'hop' over 5 frames
    AI_FLYING_STATE_ALERT_INIT             = 10,
    AI_FLYING_STATE_ALERT                  = 11,
    // while chasing, flying enemies swoop toward the player (after optional delay)
    AI_FLYING_STATE_CHASE_INIT             = 12,
    AI_FLYING_STATE_CHASE_DELAY            = 13,
    AI_FLYING_STATE_CHASE                  = 14,
};

enum AiVarsFlying {
    AI_FLYING_VAR_FLAGS             = 0,
    AI_FLYING_VAR_BOB_AMPLITUDE     = 1, // amplitude of bobbing during wander and loiter
    AI_FLYING_VAR_BOB_PHASE         = 2,
    AI_FLYING_VAR_HOVER_HEIGHT      = 3, // height above ground at initial position
    AI_FLYING_VAR_PREV_Y            = 4,
    AI_FLYING_VAR_CHASE_VELY        = 5, // y velocity to use during chase swoop
    AI_FLYING_VAR_CHASE_ACCEL       = 6, // y acceleration to use during chase swoop
    AI_FLYING_VAR_HOVER_BASE        = 7, // y level of ground under initial position
    AI_FLYING_VAR_DETECT_COOLDOWN    = 9, // unused
};

enum AiVarsFlag {
    AI_FLYING_FLAG_01           = 0x01,
    AI_FLYING_FLAG_10           = 0x10,
    AI_FLYING_FLAG_MASK         = 0x11,
};

f32 N(FlyingAI_JumpVels)[] = {
    4.5, 3.5, 2.6, 2.0, 1.5,
};

void N(FlyingAI_WanderInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = aiSettings->moveTime / 2 + rand_int(aiSettings->moveTime / 2 + 1);
    if (is_point_outside_territory(enemy->territory->wander.wanderShape,
            enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z,
            npc->pos.x, npc->pos.z,
            enemy->territory->wander.wanderSize.x, enemy->territory->wander.wanderSize.z)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
    } else {
        npc->yaw = clamp_angle((npc->yaw + rand_int(60)) - 30.0f);
    }
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    script->functionTemp[1] = 0;
    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = aiSettings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
    enemy->varTable[AI_FLYING_VAR_PREV_Y] = npc->pos.y * 100.0;
    script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER;
}

void N(FlyingAI_Wander)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 cond = false;
    f32 hoverBase = (f32)enemy->varTable[AI_FLYING_VAR_HOVER_BASE] / 100.0;
    f32 hoverHeight = (f32)enemy->varTable[AI_FLYING_VAR_HOVER_HEIGHT] / 100.0;
    f32 prevY = (f32)enemy->varTable[AI_FLYING_VAR_PREV_Y] / 100.0;
    f32 bobAmplitude = (f32)enemy->varTable[AI_FLYING_VAR_BOB_AMPLITUDE] / 100.0;
    f32 posX, posY, posZ, posW;
    f32 initialY;

    enemy->varTable[AI_FLYING_VAR_PREV_Y] = npc->pos.y * 100.0;

    initialY = hoverBase + hoverHeight;

    if ((enemy->varTable[AI_FLYING_VAR_FLAGS] & AI_FLYING_FLAG_MASK) == AI_FLYING_FLAG_01) {
        if (npc->flags & NPC_FLAG_FLYING) {
            if (bobAmplitude < initialY - npc->pos.y) {
                enemy->varTable[AI_FLYING_VAR_FLAGS] |= AI_FLYING_FLAG_10;
            }
        } else {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            posW = 1000.0f;
            npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW);
            if (bobAmplitude < (hoverHeight - posW)) {
                enemy->varTable[AI_FLYING_VAR_FLAGS] |= AI_FLYING_FLAG_10;
            }
        }
    }

    if ((enemy->varTable[AI_FLYING_VAR_FLAGS] & AI_FLYING_FLAG_MASK) == (AI_FLYING_FLAG_01 | AI_FLYING_FLAG_10)) {
        f32 yTemp;

        if (npc->flags & NPC_FLAG_FLYING) {
            yTemp = initialY;
            npc->pos.y = prevY + ((initialY - prevY) * 0.09);
        } else {
            posX = npc->pos.x;
            posY = prevY;
            posZ = npc->pos.z;
            posW = 1000.0f;
            npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW);

            yTemp = posY;
            yTemp += hoverHeight;
            npc->pos.y = prevY + ((yTemp - prevY) * 0.09);
        }

        if (fabsf(yTemp - npc->pos.y) < 1.0) {
            npc->pos.y = yTemp;
            enemy->varTable[AI_FLYING_VAR_FLAGS] &= ~AI_FLYING_FLAG_10;
        }
    } else {
        if (enemy->varTable[AI_FLYING_VAR_BOB_AMPLITUDE] > 0) {
            f32 bobAmount = sin_deg(enemy->varTable[AI_FLYING_VAR_BOB_PHASE]);
            b32 hit;

            if (npc->flags & NPC_FLAG_FLYING) {
                hit = false;
            } else {
                posX = npc->pos.x;
                posY = npc->pos.y;
                posZ = npc->pos.z;
                posW = 1000.0f;
                hit = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW);
            }

            if (hit) {
                npc->pos.y = posY + hoverHeight + (bobAmount * bobAmplitude);
            } else {
                npc->pos.y = initialY + (bobAmount * bobAmplitude);
            }

            enemy->varTable[AI_FLYING_VAR_BOB_PHASE] = clamp_angle(enemy->varTable[AI_FLYING_VAR_BOB_PHASE] + 10);
        }
    }

    if (enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN] <= 0) {
        if (aiSettings->playerSearchInterval >= 0) {
            if (script->functionTemp[1] <= 0) {
                script->functionTemp[1] = aiSettings->playerSearchInterval;
                if (gPlayerStatusPtr->pos.y < (npc->pos.y + npc->collisionHeight) + 10.0 &&
                    basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, 0))
                {
                    EffectInstance* emoteTemp;
                    fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, &emoteTemp);
                    npc->moveToPos.y = npc->pos.y;
                    ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);

                    if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                        script->AI_TEMP_STATE = AI_FLYING_STATE_ALERT_INIT;
                    } else {
                        script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE_INIT;
                    }
                    return;
                }
            }
            script->functionTemp[1]--;
        }
    } else {
        enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN]--;
    }

    if (is_point_outside_territory(enemy->territory->wander.wanderShape,
                               enemy->territory->wander.centerPos.x,
                               enemy->territory->wander.centerPos.z,
                               npc->pos.x, npc->pos.z,
                               enemy->territory->wander.wanderSize.x, enemy->territory->wander.wanderSize.z)) {
        posW = dist2D(enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z, npc->pos.x, npc->pos.z);
        if (npc->moveSpeed < posW) {
            npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
            cond = true;
        }
    }

    if (enemy->territory->wander.wanderSize.x | enemy->territory->wander.wanderSize.z | cond) {
        if (npc->turnAroundYawAdjustment != 0) {
            return;
        }
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }

    enemy->varTable[AI_FLYING_VAR_PREV_Y] = npc->pos.y * 100.0;
    if (aiSettings->moveTime > 0) {
        if ((npc->duration <= 0) || (--npc->duration <= 0)) {
            script->AI_TEMP_STATE = AI_FLYING_STATE_LOITER_INIT;
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;
            if (aiSettings->loiterMode <= 0 || aiSettings->waitTime <= 0 || script->functionTemp[1] < 3) {
                script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
            }
        }
    }
}

void N(FlyingAI_LoiterInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (aiSettings->waitTime / 2) + rand_int((aiSettings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_FLYING_STATE_LOITER;
}

void N(FlyingAI_Loiter)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 hoverHeight = enemy->varTable[AI_FLYING_VAR_HOVER_HEIGHT] / 100.0;
    f32 hoverBase = enemy->varTable[AI_FLYING_VAR_HOVER_BASE] / 100.0;
    f32 posX, posY, posZ, posW;
    EffectInstance* emoteTemp;

    if (npc->duration > 0) {
        npc->duration--;
    }

    // calculate new height with bobbing added in
    if (enemy->varTable[AI_FLYING_VAR_BOB_AMPLITUDE] > 0) {
        f32 bobAmplitude = enemy->varTable[AI_FLYING_VAR_BOB_AMPLITUDE] / 100.0;
        f32 bobAmount = sin_deg(enemy->varTable[AI_FLYING_VAR_BOB_PHASE]);
        b32 hasCollision;

        if (npc->flags & NPC_FLAG_FLYING) {
            hasCollision = false;
        } else {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            posW = 1000.0f;
            hasCollision = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW);
        }

        if (hasCollision) {
            npc->pos.y = posY + hoverHeight + (bobAmount * bobAmplitude);
        } else {
            npc->pos.y = hoverBase + hoverHeight + (bobAmount * bobAmplitude);
        }

        enemy->varTable[AI_FLYING_VAR_BOB_PHASE] = clamp_angle(enemy->varTable[AI_FLYING_VAR_BOB_PHASE] + 10);
    }

    // try player detection
    if (enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN] <= 0) {
        if ((gPlayerStatusPtr->pos.y < npc->pos.y + npc->collisionHeight + 10.0)
            && basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, true)) {
            fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, &emoteTemp);
            npc->moveToPos.y = npc->pos.y;
            ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
            if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                script->AI_TEMP_STATE = AI_FLYING_STATE_ALERT_INIT;
            } else {
                script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE_INIT;
            }
            return;
        }
    } else {
        enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN]--;
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
            script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
        }
    }
}

void N(FlyingAI_JumpInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    PlayerStatus* playerStatus = gPlayerStatusPtr;

    npc->duration = 0;
    npc->yaw = atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
    script->AI_TEMP_STATE = AI_FLYING_STATE_ALERT;
}

void N(FlyingAI_Jump)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->pos.y += N(FlyingAI_JumpVels)[npc->duration++];
    if (npc->duration >= ARRAY_COUNT(N(FlyingAI_JumpVels))) {
        script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE_INIT;
    }
}

void N(FlyingAI_ChaseInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 jumpVel = enemy->varTable[AI_FLYING_VAR_CHASE_VELY] / 100.0;
    f32 jumpScale = enemy->varTable[AI_FLYING_VAR_CHASE_ACCEL] / 100.0;

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
    npc->jumpVel = jumpVel;
    npc->jumpScale = jumpScale;
    npc->moveSpeed = aiSettings->chaseSpeed;
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);

    enemy->varTable[AI_FLYING_VAR_BOB_PHASE] = 0;

    if (enemy->npcSettings->actionFlags & AI_ACTION_CANT_FIRST_STRIKE) {
        npc->duration = 3;
        script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE_DELAY;
    } else {
        npc->duration = 1;
        script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE;
        enemy->attackOriginPos.x = npc->pos.x;
        enemy->attackOriginPos.y = npc->pos.y;
        enemy->attackOriginPos.z = npc->pos.z;
        enemy->firstStrikeActive = true;
    }
}

void N(FlyingAI_ChaseDelay)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    if ((npc->duration <= 0) || (--npc->duration <= 0)) {
        if (npc->turnAroundYawAdjustment == 0) {
            npc->duration = 0;
            script->AI_TEMP_STATE = AI_FLYING_STATE_CHASE;
        }
    }
}

void N(FlyingAI_Chase)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ, posW;
    f32 deltaAngle;
    f32 temp_f2;
    s32 hitBelow;
    f32 angle;
    f32 hoverHeight = enemy->varTable[AI_FLYING_VAR_HOVER_HEIGHT] / 100.0;
    f32 hoverBase = enemy->varTable[AI_FLYING_VAR_HOVER_BASE] / 100.0;

    npc->jumpVel += npc->jumpScale;
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    if (npc->jumpVel >= 0.0) {
        npc->pos.y += npc->jumpVel;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_HIT];
        enemy->firstStrikeActive = false;
        if (!(npc->flags & NPC_FLAG_FLYING)) {
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            posW = 1000.0f;
            hitBelow = npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW);
        } else {
            hitBelow = false;
        }
        if (hitBelow) {
            temp_f2 = posY + hoverHeight;
            if (temp_f2 <= npc->pos.y) {
                npc->pos.y = temp_f2;
                script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
            }
        } else if (npc->pos.y >= npc->moveToPos.y) {
            script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
        }
    } else if (npc->jumpVel < 0.0) {
        npc->duration++;
        if (npc->duration >= aiSettings->chaseUpdateInterval) {
            npc->duration = 0;
            angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            deltaAngle = get_clamped_angle_diff(npc->yaw, angle);
            if (aiSettings->chaseTurnRate < fabsf(deltaAngle)) {
                angle = npc->yaw;
                if (deltaAngle < 0.0f) {
                    angle += -aiSettings->chaseTurnRate;
                } else {
                    angle += aiSettings->chaseTurnRate;
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
        posW = (fabsf(npc->jumpVel) + npc->collisionHeight) + 10.0;
        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW)) {
            if (posW <= (npc->collisionHeight + fabsf(npc->jumpVel))) {
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

void N(FlyingAI_Init)(Npc* npc, Enemy* enemy, Evt* script, MobileAISettings* aiSettings) {
    f32 posX, posY, posZ, depth;

    script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
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
    enemy->varTable[AI_FLYING_VAR_BOB_PHASE] = 0;
    enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN] = 0;
    enemy->varTable[AI_FLYING_VAR_HOVER_HEIGHT] = (depth * 100.0) + 0.5;
    enemy->varTable[AI_FLYING_VAR_HOVER_BASE] = (posY * 100.0) + 0.5;
    script->functionTemp[1] = aiSettings->playerSearchInterval;
    enemy->aiFlags |= AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE;
}

API_CALLABLE(N(FlyingAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 120.0f;
    territory.detectFlags = 0;

    if (isInitialCall) {
        N(FlyingAI_Init)(npc, enemy, script, aiSettings);
    }

    npc->verticalRenderOffset = -2;

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_FLYING_STATE_WANDER_INIT:
            N(FlyingAI_WanderInit)(script, aiSettings, territoryPtr);
        case AI_FLYING_STATE_WANDER:
            N(FlyingAI_Wander)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, aiSettings, territoryPtr);
        case AI_FLYING_STATE_LOITER:
            N(FlyingAI_Loiter)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_ALERT_INIT:
            N(FlyingAI_JumpInit)(script, aiSettings, territoryPtr);
        case AI_FLYING_STATE_ALERT:
            N(FlyingAI_Jump)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_CHASE_INIT:
            N(FlyingAI_ChaseInit)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_CHASE_DELAY:
            N(FlyingAI_ChaseDelay)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_CHASE:
            N(FlyingAI_Chase)(script, aiSettings, territoryPtr);
            break;
    }

    return ApiStatus_BLOCK;
}

#endif
