#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

// This AI is used by:
// - Lava Bubble
// - Ruff Puff
// - Ember

#include "world/common/enemy/ai/FlyingAI.inc.c"

enum {
    AI_STATE_FNA_CHASE_INIT     = 12,
    AI_STATE_FNA_CHASE          = 13,
    AI_STATE_FNA_LOSE_PLAYER    = 20,
};

void N(FlyingNoAttackAI_ChaseInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 angle;
    f32 deltaAngle;

    npc->duration = (aiSettings->chaseUpdateInterval / 2) + rand_int(aiSettings->chaseUpdateInterval / 2 + 1);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = aiSettings->chaseSpeed;

    angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    deltaAngle = get_clamped_angle_diff(npc->yaw, angle);

    // cap the turn rate
    if (aiSettings->chaseTurnRate < fabsf(deltaAngle)) {
        if (deltaAngle < 0.0f) {
            angle = npc->yaw - aiSettings->chaseTurnRate;
        } else {
            angle = npc->yaw + aiSettings->chaseTurnRate;
        }
    }
    npc->yaw = clamp_angle(angle);

    script->AI_TEMP_STATE = AI_STATE_FNA_CHASE;
}

void N(FlyingNoAttackAI_Chase)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z, hitDepth;
    f32 distY;
    b32 hitFloor;

    if (!basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 30;
        script->AI_TEMP_STATE = AI_STATE_FNA_LOSE_PLAYER;
        enemy->varTable[AI_FLYING_VAR_DETECT_COOLDOWN] = 30;
        return;
    }

    npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    hitFloor = false;
    if (!(npc->flags & NPC_FLAG_FLYING)) {
        x = npc->pos.x;
        y = npc->pos.y + npc->collisionHeight;
        z = npc->pos.z;
        hitDepth = npc->collisionHeight + 3.0; // test a length slightly taller than the npc
        if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth) && (hitDepth < npc->collisionHeight)) {
            hitFloor = true;
        }
    }

    if (hitFloor) {
        npc->pos.y = y + 1.0;
    } else {
        // interp to player y-position
        distY = npc->pos.y - (gPlayerStatusPtr->pos.y + 6.0);
        if ((distY < 0.0) || (distY > 4.0)) {
            npc->pos.y += -distY * 0.06;
        }
    }
    if (npc->duration > 0) {
        npc->duration--;
        return;
    }
    script->AI_TEMP_STATE = AI_STATE_FNA_CHASE_INIT;
}

void N(FlyingNoAttackAI_LosePlayer)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->varTable[AI_FLYING_VAR_BOB_PHASE] = 0;
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
    }
}

API_CALLABLE(N(FlyingNoAttackAI_Main)) {
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
        script->AI_TEMP_STATE = AI_FLYING_STATE_WANDER_INIT;
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
            // fallthrough
        case AI_FLYING_STATE_WANDER:
            N(FlyingAI_Wander)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_FLYING_STATE_LOITER:
            N(FlyingAI_Loiter)(script, aiSettings, territoryPtr);
            break;
        case AI_FLYING_STATE_ALERT_INIT:
            N(FlyingAI_JumpInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_FLYING_STATE_ALERT:
            N(FlyingAI_Jump)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_FNA_CHASE_INIT:
            N(FlyingNoAttackAI_ChaseInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FNA_CHASE:
            N(FlyingNoAttackAI_Chase)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_FNA_LOSE_PLAYER:
            N(FlyingNoAttackAI_LosePlayer)(script, aiSettings, territoryPtr);
            break;
    }

    return ApiStatus_BLOCK;
}

