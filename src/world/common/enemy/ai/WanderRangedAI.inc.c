#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

// Used by:
// - Monty Mole
// - Spy Guy
// - Dry Bones
// - Hammer Bros

#include "world/common/enemy/ai/RangedAttack.inc.c"

API_CALLABLE(N(RangedAttackAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;
    f32 dist;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 40.0f;
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
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
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
            dist = dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            if (enemy->varTable[AI_VAR_RANGED_MIN_DIST] == 0 || enemy->varTable[AI_VAR_RANGED_MIN_DIST] < dist) {
                N(RangedAttack_TryTakeShot)(script, settings->chaseRadius, settings->chaseOffsetDist, detect);
                if (script->AI_TEMP_STATE != AI_STATE_CHASE_INIT) {
                    break;
                }
            }
            basic_ai_chase_init(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            basic_ai_chase(script, settings, detect);
            break;
        case AI_STATE_LOSE_PLAYER:
            basic_ai_lose_player(script, settings, detect);
            break;
        case AI_STATE_RANGED_ATTACK_FIRE:
            N(RangedAttack_Fire(script));
            break;
        case AI_STATE_RANGED_ATTACK_CANCEL:
            N(RangedAttack_Cancel(script));
            break;
        case AI_STATE_RANGED_ATTACK_AWAIT:
            N(RangedAttack_Await(script));
            break;
        case AI_STATE_RANGED_ATTACK_COOLDOWN:
            N(RangedAttack_Cooldown(script));
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
