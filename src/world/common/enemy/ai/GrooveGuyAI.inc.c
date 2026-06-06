#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/GrooveGuy.h"

enum GrooveAiVars {
    AI_VAR_GROOVE_DANCE_PHASE   = 0,
    AI_VAR_GROOVE_DANCE_TIME    = 1,
};

enum GrooveDancePhases {
    DANCE_PHASE_POINT_INIT      = 0,
    DANCE_PHASE_POINT           = 1,
    DANCE_PHASE_SPIN_INIT       = 2,
    DANCE_PHASE_SPIN            = 3,
    DANCE_PHASE_DONE            = 4,
};

void N(GrooveGuyAI_DanceInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 0;
    set_npc_yaw(npc, 270.0f);
    enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] = DANCE_PHASE_POINT_INIT;
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void N(GrooveGuyAI_Dance)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 animPart;

    switch (enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE]) {
        case DANCE_PHASE_POINT_INIT:
            enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] = DANCE_PHASE_POINT;
            enemy->varTable[AI_VAR_GROOVE_DANCE_TIME] = 0;
            npc->curAnim = ANIM_GrooveGuy_Anim0C;
            set_npc_yaw(npc, 270.0f);
            npc->rot.y = 0.0f;
            // fallthrough
        case DANCE_PHASE_POINT:
            animPart = enemy->varTable[AI_VAR_GROOVE_DANCE_TIME] % 16;
            if (animPart < 4) {
                npc->curAnim = ANIM_GrooveGuy_Anim0C;
            } else if (animPart < 8) {
                npc->curAnim = ANIM_GrooveGuy_Anim0B;
            } else if (animPart < 12) {
                npc->curAnim = ANIM_GrooveGuy_Anim0C;
            } else {
                npc->curAnim = ANIM_GrooveGuy_Anim0D;
            }
            enemy->varTable[AI_VAR_GROOVE_DANCE_TIME]++;
            if (enemy->varTable[AI_VAR_GROOVE_DANCE_TIME] > 64) {
                enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] = DANCE_PHASE_SPIN_INIT;
            }
            break;
        case DANCE_PHASE_SPIN_INIT:
            enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] = DANCE_PHASE_SPIN;
            enemy->varTable[AI_VAR_GROOVE_DANCE_TIME] = 0;
            npc->rot.y = 0.0f;
            npc->curAnim = ANIM_GrooveGuy_Anim0C;
            // fallthrough
        case DANCE_PHASE_SPIN:
            npc->rot.y += 35.0;
            if (npc->rot.y > 360.0) {
                npc->rot.y -= 360.0;
            }
            enemy->varTable[AI_VAR_GROOVE_DANCE_TIME]++;
            if (enemy->varTable[AI_VAR_GROOVE_DANCE_TIME] >= 46) {
                enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] = DANCE_PHASE_DONE;
            }
            break;
    }

    if (enemy->varTable[AI_VAR_GROOVE_DANCE_PHASE] == DANCE_PHASE_DONE) {
        npc->rot.y = 0.0f;
        set_npc_yaw(npc, 270.0f);
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

API_CALLABLE(N(GrooveGuyAI_Main)) {
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
            N(GrooveGuyAI_DanceInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_LOITER:
            N(GrooveGuyAI_Dance)(script, aiSettings, territoryPtr);
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
            basic_ai_lose_player(script, aiSettings, territoryPtr);
            break;

        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    return ApiStatus_BLOCK;
}
