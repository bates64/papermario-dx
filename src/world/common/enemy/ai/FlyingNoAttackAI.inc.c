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

void N(FlyingNoAttackAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 angle;
    f32 deltaAngle;

    npc->duration = (settings->chaseUpdateInterval / 2) + rand_int(settings->chaseUpdateInterval / 2 + 1);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = settings->chaseSpeed;

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

    script->AI_TEMP_STATE = AI_STATE_FNA_CHASE;
}

void N(FlyingNoAttackAI_Chase)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z, hitDepth;
    f32 distY;
    b32 hitFloor;

    if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 30;
        script->AI_TEMP_STATE = AI_STATE_FNA_LOSE_PLAYER;
        enemy->varTable[AI_VAR_FLYING_DETECT_COOLDOWN] = 30;
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

void N(FlyingNoAttackAI_LosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = 0;
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    }
}

API_CALLABLE(N(FlyingNoAttackAI_Main)) {
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
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
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
        case AI_STATE_FNA_CHASE_INIT:
            N(FlyingNoAttackAI_ChaseInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_FNA_CHASE:
            N(FlyingNoAttackAI_Chase)(script, settings, detect);
            break;
        case AI_STATE_FNA_LOSE_PLAYER:
            N(FlyingNoAttackAI_LosePlayer)(script, settings, detect);
            break;
    }

    return ApiStatus_BLOCK;
}
