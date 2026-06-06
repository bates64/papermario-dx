#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"
#include "world/partners.h"

#include "world/common/enemy/ai/MeleeAttack.inc.c"
#include "world/common/enemy/ai/States_PatrolAI.inc.c"

API_CALLABLE(N(ClubbaPatrolAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* npcAISettings = (MobileAISettings*)evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->patrol.detectShape;
    territory.pointX = enemy->territory->patrol.detectPos.x;
    territory.pointZ = enemy->territory->patrol.detectPos.z;
    territory.sizeX = enemy->territory->patrol.detectSize.x;
    territory.sizeZ = enemy->territory->patrol.detectSize.z;
    territory.halfHeight = 65.0f;
    territory.detectFlags = 0;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
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
        }

        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
    }

    // begin an attack, if able
    if (script->AI_TEMP_STATE < AI_STATE_MELEE_ATTACK_INIT
        && enemy->varTable[AI_VAR_MELEE_STATUS] == MELEE_ATTACK_PHASE_NONE
        && N(MeleeHitbox_CanTargetPlayer)(script)
    ) {
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_INIT;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_PATROL_INIT:
            N(PatrolAI_MoveInit)(script, npcAISettings, territoryPtr);
            // fallthrough
        case AI_STATE_PATROL:
            N(PatrolAI_Move)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_LOITER_INIT:
            N(PatrolAI_LoiterInit)(script, npcAISettings, territoryPtr);
            // fallthrough
        case AI_STATE_LOITER:
            N(PatrolAI_Loiter)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_LOITER_POST:
            N(PatrolAI_PostLoiter)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_ALERT_INIT:
            N(PatrolAI_JumpInit)(script, npcAISettings, territoryPtr);
            // fallthrough
        case AI_STATE_ALERT:
            N(PatrolAI_Jump)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_CHASE_INIT:
            N(PatrolAI_ChaseInit)(script, npcAISettings, territoryPtr);
            // fallthrough
        case AI_STATE_CHASE:
            N(PatrolAI_Chase)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_LOSE_PLAYER:
            N(PatrolAI_LosePlayer)(script, npcAISettings, territoryPtr);
            break;
        case AI_STATE_MELEE_ATTACK_INIT:
            N(MeleeAttacker_Init)(script);
            // fallthrough
        case AI_STATE_MELEE_ATTACK_PRE:
            N(MeleeAttacker_Pre)(script);
            if (script->AI_TEMP_STATE != AI_STATE_MELEE_ATTACK_SWING) {
                break;
            }
            // fallthrough
        case AI_STATE_MELEE_ATTACK_SWING:
            N(MeleeAttacker_Swing)(script);
            if (script->AI_TEMP_STATE != AI_STATE_MELEE_ATTACK_POST) {
                break;
            }
            // fallthrough
        case AI_STATE_MELEE_ATTACK_POST:
            N(MeleeAttacker_Post)(script);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    return ApiStatus_BLOCK;
}
