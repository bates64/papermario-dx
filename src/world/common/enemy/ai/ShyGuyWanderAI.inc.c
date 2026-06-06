#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

#ifndef _SHYGUY_STATES_
#define _SHYGUY_STATES_
enum ShyGuyAiStates {
    AI_STATE_SHYGUY_TRIP    = 15, // trip animation
    AI_STATE_SHYGUY_FALL    = 16, // fall animation
    AI_STATE_SHYGUY_LAY     = 17, // lay on the ground after falling
};

enum ShyGuyAiAnims {
    AI_ANIM_SHYGUY_FALL     = 11,
    AI_ANIM_SHYGUY_TRIP     = 12,
};
#endif

void N(ShyGuyWanderAI_TripInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territoryPtr) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->moveSpeed *= 0.6f;
    npc->curAnim = enemy->animList[AI_ANIM_SHYGUY_TRIP];
    npc->duration = 5;
    script->AI_TEMP_STATE = AI_STATE_SHYGUY_TRIP;
}

void N(ShyGuyWanderAI_Trip)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 yaw = npc->yaw;

    if (!ai_check_fwd_collisions(npc, npc->moveSpeed, &yaw, nullptr, nullptr, nullptr)) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }

    npc->duration--;
    if (npc->duration == 0) {
        npc->moveSpeed *= 0.6f;

        npc->curAnim = enemy->animList[AI_ANIM_SHYGUY_FALL];
        npc->duration = 10;
        script->AI_TEMP_STATE = AI_STATE_SHYGUY_FALL;
    }
}

void N(ShyGuyWanderAI_Fall)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 yaw = npc->yaw;

    if (!ai_check_fwd_collisions(npc, npc->moveSpeed, &yaw, nullptr, nullptr, nullptr)) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }

    npc->duration--;
    if (npc->duration == 0) {
        npc->duration = 30;
        script->AI_TEMP_STATE = AI_STATE_SHYGUY_LAY;
    }
}

void N(ShyGuyWanderAI_Lay)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

API_CALLABLE(N(ShyGuyWanderAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args++);
    f32 posX, posY, posZ;
    f32 hitDepth;

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 65.0f;
    territory.detectFlags = 0;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];

        npc->flags &= ~NPC_FLAG_JUMPING;
        if (enemy->territory->wander.isFlying) {
            npc->flags |= NPC_FLAG_FLYING;
            npc->flags &= ~NPC_FLAG_GRAVITY;
        } else {
            npc->flags |= NPC_FLAG_GRAVITY;
            npc->flags &= ~NPC_FLAG_FLYING;
        }

        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            script->AI_TEMP_STATE = AI_STATE_SUSPEND;
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_WANDER_INIT;
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;

        // snap to ground
        hitDepth = 100.0f;
        posX = npc->pos.x;
        posY = npc->pos.y + npc->collisionHeight;
        posZ = npc->pos.z;
        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth)) {
            npc->pos.y = posY;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_WANDER_INIT:
            basic_ai_wander_init(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_WANDER:
            basic_ai_wander(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_LOITER_INIT:
            basic_ai_loiter_init(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_LOITER:
            basic_ai_loiter(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_ALERT_INIT:
            basic_ai_found_player_jump_init(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_ALERT:
            basic_ai_found_player_jump(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_CHASE_INIT:
            basic_ai_chase_init(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_CHASE:
            basic_ai_chase(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }
            // fallthrough
        case AI_STATE_LOSE_PLAYER:
            N(ShyGuyWanderAI_TripInit)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_TRIP) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_TRIP:
            N(ShyGuyWanderAI_Trip)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_FALL) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_FALL:
            N(ShyGuyWanderAI_Fall)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_LAY) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_LAY:
            N(ShyGuyWanderAI_Lay)(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    return ApiStatus_BLOCK;
}

