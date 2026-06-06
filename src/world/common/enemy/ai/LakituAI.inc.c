#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/Lakitu.h"

// required include args
#ifndef AI_LAKITU_FIRST_SPINY_ID
#error  AI_LAKITU_FIRST_SPINY_ID must be defined for LakituAI
#define AI_LAKITU_FIRST_SPINY_ID 0
#endif
#ifndef AI_LAKITU_LAST_SPINY_ID
#error  AI_LAKITU_LAST_SPINY_ID must be defined for LakituAI
#define AI_LAKITU_LAST_SPINY_ID 0
#endif

#include "world/common/enemy/ai/SpinyAI.inc.c"
#include "world/common/enemy/ai/FlyingAI.inc.c"

enum LakituAiStates {
    AI_STATE_LAKITU_HOLD_INIT   = 30,
    AI_STATE_LAKITU_HOLD        = 31,
    AI_STATE_LAKITU_THROW       = 32,
    AI_STATE_LAKITU_COOLDOWN    = 33,
};

enum LakituAiVars {
    AI_VAR_LAKITU_HELD_SPINY    = 4, // npcID of held spiny; temporarily aliases AI_VAR_FLYING_PREV_Y during a throw
};

s32 N(LakituAI_GetAvailableSpiny)(void) {
    s32 npcID;

    for (npcID = AI_LAKITU_FIRST_SPINY_ID; npcID <= AI_LAKITU_LAST_SPINY_ID; npcID++) {
        if (get_enemy(npcID)->varTable[AI_VAR_SPINY_STATUS] == SPINY_STATUS_IDLE) {
            return npcID;
        }
    }

    return -1;
}

void N(LakituAI_Wander)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 bobAmplitude = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE]);
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 smoothY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_PREV_Y]);
    f32 x, y, z, hitDepth;
    f32 targetY, deltaY;

    if (npc->duration > 0) {
        npc->duration--;
    }

    x = npc->pos.x;
    y = npc->pos.y;
    z = npc->pos.z;
    hitDepth = 1000.0f;
    npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth);

    // bob hoverHeight units above the current ground
    npc->pos.y = y + hoverHeight + (sin_deg(enemy->varTable[AI_VAR_FLYING_BOB_PHASE]) * bobAmplitude);
    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYING_BOB_PHASE] + 12);

    if (aiSettings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = aiSettings->playerSearchInterval;
            if (basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, false)) {
                fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                hitDepth = 1000.0f;
                npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth);
                npc->moveToPos.y = y + hoverHeight;
                script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_INIT;
                return;
            }
        }
        script->functionTemp[1]--;
    }

    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
    }

    if (npc->turnAroundYawAdjustment == 0) {
        if (npc->duration > 0) {
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            if (enemy->varTable[AI_VAR_FLYING_FLAGS] & AI_FLYING_FLAG_INTERPY) {
                x = npc->pos.x;
                y = smoothY;
                z = npc->pos.z;
                hitDepth = 1000.0f;
                npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth);

                targetY = y + hoverHeight;
                deltaY = deltaY - smoothY;

                if (deltaY > 2.0) {
                    smoothY += 2.0;
                } else if (deltaY < -2.0) {
                    smoothY -= 2.0;
                } else {
                    smoothY = targetY;
                }
                enemy->varTable[AI_VAR_FLYING_PREV_Y] = AI_PACK_FLT(smoothY);
            }
        } else {
            script->AI_TEMP_STATE = AI_STATE_FLYING_LOITER_INIT;
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;
            if ((aiSettings->loiterMode <= 0) || (aiSettings->moveTime <= 0) || (script->functionTemp[1] == 0)) {
                script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
            }
        }
    }
}

void N(LakituAI_Loiter)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 bobAmplitude = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE]);
    f32 posX, posY, posZ, hitDepth;

    if (npc->duration > 0) {
        npc->duration--;
    }

    posX = npc->pos.x;
    posY = npc->pos.y;
    posZ = npc->pos.z;
    hitDepth = 1000.0f;
    npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);

    npc->pos.y = posY + hoverHeight + (sin_deg(enemy->varTable[AI_VAR_FLYING_BOB_PHASE]) * bobAmplitude);
    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYING_BOB_PHASE] + 12);

    if (basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        script->AI_TEMP_STATE = AI_STATE_FLYING_CHASE_INIT;
        return;
    }

    if ((npc->turnAroundYawAdjustment == 0) && (npc->duration <= 0)) {
        script->functionTemp[1]--;
        if (script->functionTemp[1] > 0) {
            npc->yaw = clamp_angle(npc->yaw + 180.0f);
            npc->duration = (rand_int(1000) % 11) + 5;
            return;
        }
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    }
}

API_CALLABLE(N(LakituAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args);
    Enemy* spinyEnemy;

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
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    }
    npc->verticalRenderOffset = -3;

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_FLYING_WANDER_INIT:
            N(FlyingAI_WanderInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FLYING_WANDER:
            N(LakituAI_Wander)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_FLYING_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FLYING_LOITER:
            N(LakituAI_Loiter)(script, aiSettings, territoryPtr);
            break;
    }

    if (script->AI_TEMP_STATE == AI_STATE_FLYING_CHASE_INIT) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        enemy->varTable[AI_VAR_LAKITU_HELD_SPINY] = N(LakituAI_GetAvailableSpiny)();
        if (enemy->varTable[AI_VAR_LAKITU_HELD_SPINY] >= 0) {
            // found a spiny, reserve it and play lifting animation
            spinyEnemy = get_enemy(enemy->varTable[AI_VAR_LAKITU_HELD_SPINY]);
            spinyEnemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_RESERVED;
            spinyEnemy->varTable[AI_VAR_SPINY_THROWER] = enemy->npcID;
            npc->duration = 15;
            npc->curAnim = ANIM_Lakitu_Anim14;
            script->AI_TEMP_STATE = AI_STATE_LAKITU_HOLD_INIT;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_FLYING_CHASE_INIT:
            N(FlyingAI_ChaseInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FLYING_CHASE_DELAY:
            N(FlyingAI_ChaseDelay)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_FLYING_CHASE:
            N(FlyingAI_Chase)(script, aiSettings, territoryPtr);
            break;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_LAKITU_HOLD_INIT:
            npc->duration--;
            if (npc->duration > 0) {
                break;
            }
            spinyEnemy = get_enemy(enemy->varTable[AI_VAR_LAKITU_HELD_SPINY]);
            spinyEnemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_HOLD_REQUEST;
            npc->duration = 5;
            script->AI_TEMP_STATE = AI_STATE_LAKITU_HOLD;
            // fallthrough
        case AI_STATE_LAKITU_HOLD:
            npc->duration--;
            if (npc->duration > 0) {
                break;
            }
            npc->curAnim = ANIM_Lakitu_Anim15;
            spinyEnemy = get_enemy(enemy->varTable[AI_VAR_LAKITU_HELD_SPINY]);
            spinyEnemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_THROW_REQUEST;
            npc->duration = 10;
            script->AI_TEMP_STATE = AI_STATE_LAKITU_THROW;
            // fallthrough
        case AI_STATE_LAKITU_THROW:
            npc->duration--;
            if (npc->duration > 0) {
                break;
            }
            npc->duration = 3;
            script->AI_TEMP_STATE = AI_STATE_LAKITU_COOLDOWN;
            // fallthrough
        case AI_STATE_LAKITU_COOLDOWN:
            npc->duration--;
            if (npc->duration <= 0) {
                script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
            }
            break;
    }

    if (script->AI_TEMP_STATE == AI_STATE_LAKITU_HOLD_INIT || script->AI_TEMP_STATE == AI_STATE_LAKITU_HOLD) {
        f32 playerDist;
        f32 lerpDist;

        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        playerDist = dist2D(gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z, npc->pos.x, npc->pos.z);
        if (!is_point_outside_detect_territory(territoryPtr, npc->pos.x, npc->pos.z)) {
            if ((playerDist > 30.0) && (npc->turnAroundYawAdjustment == 0)) {
                lerpDist = playerDist - 20.0;
                if (lerpDist < 0.0) {
                    lerpDist = 0.0f;
                }
                if (lerpDist > 200.0) {
                    lerpDist = 200.0f;
                }
                npc->moveSpeed = update_lerp(EASING_LINEAR, aiSettings->moveSpeed, aiSettings->chaseSpeed, lerpDist, 200);
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            }
        }
    }

    return ApiStatus_BLOCK;
}

