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

void N(ShyGuyWanderAI_TripInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->moveSpeed *= 0.6f;
    npc->curAnim = enemy->animList[AI_ANIM_SHYGUY_TRIP];
    npc->duration = 5;
    script->AI_TEMP_STATE = AI_STATE_SHYGUY_TRIP;
}

void N(ShyGuyWanderAI_Trip)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
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

void N(ShyGuyWanderAI_Fall)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
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

void N(ShyGuyWanderAI_Lay)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
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
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;
    f32 posX, posY, posZ;
    f32 hitDepth;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

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
            basic_ai_wander_init(script, settings, detect);
            // fallthrough
        case AI_STATE_WANDER:
            basic_ai_wander(script, settings, detect);
            break;

        case AI_STATE_LOITER_INIT:
            basic_ai_loiter_init(script, settings, detect);
            // fallthrough
        case AI_STATE_LOITER:
            basic_ai_loiter(script, settings, detect);
            break;

        case AI_STATE_ALERT_INIT:
            basic_ai_found_player_jump_init(script, settings, detect);
            // fallthrough
        case AI_STATE_ALERT:
            basic_ai_found_player_jump(script, settings, detect);
            break;

        case AI_STATE_CHASE_INIT:
            basic_ai_chase_init(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            basic_ai_chase(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }
            // fallthrough
        case AI_STATE_LOSE_PLAYER:
            N(ShyGuyWanderAI_TripInit)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_TRIP) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_TRIP:
            N(ShyGuyWanderAI_Trip)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_FALL) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_FALL:
            N(ShyGuyWanderAI_Fall)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_SHYGUY_LAY) {
                break;
            }
            // fallthrough
        case AI_STATE_SHYGUY_LAY:
            N(ShyGuyWanderAI_Lay)(script, settings, detect);
            break;

        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    return ApiStatus_BLOCK;
}

