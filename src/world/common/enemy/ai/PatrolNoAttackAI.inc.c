#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

// Basic Patrol AI follows a patrol path and will chase a player who comes within
// their detection range. This AI has no means of attacking; they can initiate
// battles on contact, but can't First Strike the player.

#include "world/common/enemy/ai/States_PatrolAI.inc.c"

API_CALLABLE(N(PatrolNoAttackAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*)evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;
    f32 posX, posY, posZ, posW;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->patrol.detectShape;
    detect->pointX = enemy->territory->patrol.detectPos.x;
    detect->pointZ = enemy->territory->patrol.detectPos.z;
    detect->sizeX = enemy->territory->patrol.detectSize.x;
    detect->sizeZ = enemy->territory->patrol.detectSize.z;
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

    if (isInitialCall || enemy->aiFlags & AI_FLAG_SUSPEND) {
        script->AI_TEMP_STATE = AI_STATE_PATROL_INIT;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];

        npc->flags &= ~NPC_FLAG_JUMPING;
        if (enemy->territory->patrol.isFlying) {
            npc->flags |= NPC_FLAG_FLYING;
            npc->flags &= ~NPC_FLAG_GRAVITY;
        } else {
            npc->flags |= NPC_FLAG_GRAVITY;
            npc->flags &= ~NPC_FLAG_FLYING;
        }

        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            script->AI_TEMP_STATE = AI_STATE_SUSPEND;
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_PATROL_INIT;
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
        }

        posX = npc->pos.x;
        posY = npc->pos.y + npc->collisionHeight;
        posZ = npc->pos.z;
        posW = 100.0f;

        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &posW)) {
            npc->pos.y = posY;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_PATROL_INIT:
            N(PatrolAI_MoveInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_PATROL:
            N(PatrolAI_Move)(script, settings, detect);
            break;
        case AI_STATE_LOITER_INIT:
            N(PatrolAI_LoiterInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_LOITER:
            N(PatrolAI_Loiter)(script, settings, detect);
            break;
        case AI_STATE_LOITER_POST:
            N(PatrolAI_PostLoiter)(script, settings, detect);
            break;
        case AI_STATE_ALERT_INIT:
            N(PatrolAI_JumpInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_ALERT:
            N(PatrolAI_Jump)(script, settings, detect);
            break;
        case AI_STATE_CHASE_INIT:
            N(PatrolAI_ChaseInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            N(PatrolAI_Chase)(script, settings, detect);
            break;
        case AI_STATE_LOSE_PLAYER:
            N(PatrolAI_LosePlayer)(script, settings, detect);
            break;
        case AI_STATE_PATROL_RESUME:
            N(PatrolAI_Resume)(script, settings, detect);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
