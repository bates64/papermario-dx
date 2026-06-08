#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

// Used by:
// - Clubba + White Clubba
// - Spear Guy
// - Piranha Plant
// - Putrid Piranha + Frost Piranha

#include "world/common/enemy/ai/MeleeAttack.inc.c"

API_CALLABLE(N(WanderMeleeAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*)evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

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
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
    }

    if (script->AI_TEMP_STATE < AI_STATE_MELEE_ATTACK_INIT
            && enemy->varTable[AI_VAR_MELEE_STATUS] == MELEE_ATTACK_PHASE_NONE
            && N(MeleeHitbox_CanTargetPlayer)(script)) {
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_INIT;
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
            break;
        case AI_STATE_LOSE_PLAYER:
            basic_ai_lose_player(script, settings, detect);
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
