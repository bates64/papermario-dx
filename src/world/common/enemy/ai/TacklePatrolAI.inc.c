#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/BonyBeetle.h"

#include "world/common/enemy/ai/PatrolNoAttackAI.inc.c"
#include "world/common/enemy/ai/States_TackleAI.inc.c"

API_CALLABLE(N(TacklePatrolAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->patrol.detectShape;
    territory.pointX = enemy->territory->patrol.detectPos.x;
    territory.pointZ = enemy->territory->patrol.detectPos.z;
    territory.sizeX = enemy->territory->patrol.detectSize.x;
    territory.sizeZ = enemy->territory->patrol.detectSize.z;
    territory.halfHeight = 100.0f;
    territory.detectFlags = 0;

    if (isInitialCall) {
        enemy->varTable[AI_VAR_TACKLE_HEIGHT] = npc->collisionHeight;
        enemy->varTable[AI_VAR_TACKLE_SPIKY] = false;
        enemy->instigatorValue = 0;
        enemy->aiFlags |= AI_FLAG_SKIP_EMOTE_AFTER_FLEE;
    }

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_PATROL_INIT;
        npc->duration = 0;
        enemy->firstStrikeActive = false;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->flags &= ~NPC_FLAG_JUMPING;
        npc->collisionHeight = enemy->varTable[AI_VAR_TACKLE_HEIGHT];
        enemy->varTable[AI_VAR_TACKLE_CHANGE_TIME] = 0;

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
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 40, nullptr);
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
        }
    }

    if (enemy->varTable[AI_VAR_TACKLE_CHANGE_TIME] > 0) {
        enemy->varTable[AI_VAR_TACKLE_CHANGE_TIME]--;
        if (enemy->varTable[AI_VAR_TACKLE_CHANGE_TIME] == 0) {
            if (npc->curAnim == ANIM_BonyBeetle_Anim2E ||
                npc->curAnim == ANIM_BonyBeetle_Anim2F)
            {
                npc->curAnim = ANIM_BonyBeetle_Anim0C;
            }
        } else {
            return ApiStatus_BLOCK;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_PATROL_INIT:
            N(PatrolAI_MoveInit)(script, aiSettings, territoryPtr);
            npc->collisionHeight = enemy->varTable[AI_VAR_TACKLE_HEIGHT];
            // fallthrough
        case AI_STATE_PATROL:
            N(PatrolAI_Move)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_LOITER_INIT:
            N(PatrolAI_LoiterInit)(script, aiSettings, territoryPtr);
            if (enemy->varTable[AI_VAR_TACKLE_TYPE] == TACKLER_BONY_BEETLE) {
                if (rand_int(100) < 33) {
                    if (enemy->varTable[AI_VAR_TACKLE_SPIKY]) {
                        enemy->varTable[AI_VAR_TACKLE_SPIKY] = false;
                        enemy->instigatorValue = 0;
                        npc->curAnim = ANIM_BonyBeetle_Anim2F;
                    } else {
                        enemy->varTable[AI_VAR_TACKLE_SPIKY] = true;
                        enemy->instigatorValue = 1;
                        npc->curAnim = ANIM_BonyBeetle_Anim2E;
                    }
                    enemy->varTable[AI_VAR_TACKLE_CHANGE_TIME] = 7;
                    return ApiStatus_BLOCK;
                }
            }
             // fallthrough
        case AI_STATE_LOITER:
            N(PatrolAI_Loiter)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_LOITER_POST:
            N(PatrolAI_PostLoiter)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_TACKLE_INIT:
            N(TackleAI_InitTackle)(script, aiSettings, territoryPtr);
             // fallthrough
        case AI_STATE_PRE_TACKLE:
            N(TackleAI_PreTackle)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_TACKLE:
            N(TackleAI_Tackle)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_POST_TACKLE:
            N(TackleAI_PostTackle)(script, aiSettings, territoryPtr);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    if (enemy->varTable[AI_VAR_TACKLE_TYPE] == TACKLER_BONY_BEETLE) {
        if (enemy->varTable[AI_VAR_TACKLE_SPIKY]) {
            enemy->instigatorValue = 1;
        } else {
            enemy->instigatorValue = 0;
        }
        if (enemy->varTable[AI_VAR_TACKLE_SPIKY]) {
            switch (npc->curAnim) {
                case ANIM_BonyBeetle_Anim04:
                case ANIM_BonyBeetle_Anim0C:
                case ANIM_BonyBeetle_Anim0E:
                case ANIM_BonyBeetle_Anim10:
                case ANIM_BonyBeetle_Anim12:
                case ANIM_BonyBeetle_Anim16:
                case ANIM_BonyBeetle_Anim18:
                    npc->curAnim++;
                    break;
            }
        }
    }

    return ApiStatus_BLOCK;
}
