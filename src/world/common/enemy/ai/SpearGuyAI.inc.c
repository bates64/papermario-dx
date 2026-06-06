#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/SpearGuy.h"

enum SpearGuyAiVars {
    AI_VAR_SPEAR_DANCE_PHASE    = 0,
    AI_VAR_SPEAR_DANCE_TIME     = 1,
};

enum SpearGuyLoiterPhase {
    SPEAR_DANCE_PHASE_INIT          = 0,
    SPEAR_DANCE_PHASE_CHANT_INIT    = 1,
    SPEAR_DANCE_PHASE_CHANT         = 2,
    SPEAR_DANCE_PHASE_SHAKE_INIT    = 3,
    SPEAR_DANCE_PHASE_SHAKE         = 4,
    SPEAR_DANCE_PHASE_SWEAT_INIT    = 5,
    SPEAR_DANCE_PHASE_SWEAT         = 6,
    SPEAR_DANCE_PHASE_DONE          = 7,
};

void N(SpearGuyAI_LoiterInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 0;
    set_npc_yaw(npc, 270.0f);
    enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_INIT;
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void N(SpearGuyAI_Loiter)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] == SPEAR_DANCE_PHASE_INIT) {
        if (rand_int(100) >= 50) {
            enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SHAKE_INIT;
        } else {
            enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_CHANT_INIT;
        }
        set_npc_yaw(npc, 270.0f);
    }

    switch (enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE]) {
        case SPEAR_DANCE_PHASE_CHANT_INIT:
            enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_CHANT;
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] = 0;
            npc->curAnim = ANIM_SpearGuy_Anim0F;
            // fallthrough
        case SPEAR_DANCE_PHASE_CHANT:
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME]++;
            if (enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] > 50) {
                enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SWEAT_INIT;
            }
            break;

        case SPEAR_DANCE_PHASE_SHAKE_INIT:
            enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SHAKE;
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] = 0;
            npc->curAnim = ANIM_SpearGuy_Anim10;
            // fallthrough
        case SPEAR_DANCE_PHASE_SHAKE:
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME]++;
            if (enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] == 25) {
                npc->yaw = 90.0f;
            }
            if (enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] > 60) {
                enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SWEAT_INIT;
            }
            break;

        case SPEAR_DANCE_PHASE_SWEAT_INIT:
            enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SWEAT;
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] = 0;
            npc->curAnim = ANIM_SpearGuy_Anim03;
            fx_sweat(0, npc->pos.x, npc->pos.y, npc->pos.z, npc->collisionHeight, 0, 10);
            // fallthrough
        case SPEAR_DANCE_PHASE_SWEAT:
            enemy->varTable[AI_VAR_SPEAR_DANCE_TIME]++;
            if (enemy->varTable[AI_VAR_SPEAR_DANCE_TIME] > 10) {
                s32 d100 = rand_int(100);
                // note: because rand_int is inclusive, there's a 5/101 chance for CHANT and a 6/101 for SHAKE
                if (d100 < 90) {
                    enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_DONE;
                } else if (d100 >= 95) { // 95, ..., 100
                    enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_SHAKE_INIT;
                } else { // 90, ..., 94
                    enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] = SPEAR_DANCE_PHASE_CHANT_INIT;
                }
            }
            break;
    }

    if (enemy->varTable[AI_VAR_SPEAR_DANCE_PHASE] == SPEAR_DANCE_PHASE_DONE) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

#include "world/common/enemy/ai/WanderMeleeAI.inc.c"

API_CALLABLE(N(SpearGuyAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);

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
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
    }

    // melee attack cannot start during an ongoing attack OR during the spear dance
    // due to overlap between AI_VAR_MELEE_STATUS and AI_VAR_SPEAR_DANCE_PHASE
    // this is probably intentional.
    if ((script->AI_TEMP_STATE < AI_STATE_MELEE_ATTACK_INIT)
        && (enemy->varTable[AI_VAR_MELEE_STATUS] == MELEE_ATTACK_PHASE_NONE)
        && N(MeleeHitbox_CanTargetPlayer)(script)
    ) {
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_INIT;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_WANDER_INIT:
            basic_ai_wander_init(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_WANDER:
            basic_ai_wander(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_LOITER_INIT:
            N(SpearGuyAI_LoiterInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_LOITER:
            N(SpearGuyAI_Loiter)(script, aiSettings, territoryPtr);
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
            break;

        case AI_STATE_LOSE_PLAYER:
            basic_ai_lose_player(script, aiSettings, territoryPtr);
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
