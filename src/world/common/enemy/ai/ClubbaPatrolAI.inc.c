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
    MobileAISettings* settings = (MobileAISettings*)evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->patrol.detectShape;
    detect->pointX = enemy->territory->patrol.detectPos.x;
    detect->pointZ = enemy->territory->patrol.detectPos.z;
    detect->sizeX = enemy->territory->patrol.detectSize.x;
    detect->sizeZ = enemy->territory->patrol.detectSize.z;
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

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
