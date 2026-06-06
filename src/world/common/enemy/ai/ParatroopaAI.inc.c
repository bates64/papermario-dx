#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

#include "world/common/enemy/ai/FlyingAI.inc.c"

enum ParatroopaAiStates {
    AI_STATE_PARATROOPA_WINDUP          = 12,
    AI_STATE_PARATROOPA_DIVE            = 13,
    AI_STATE_PARATROOPA_OVERSHOOT       = 14,
    AI_STATE_PARATROOPA_RESET           = 15,
};

enum ParatroopaAiVars {
    AI_VAR_PARATROOPA_HEIGHT            = 8, // original collision height
};

enum ParatroopaAiAnims {
    AI_ANIM_PARATROOPA_SHELL_DIVE       = 9,
    AI_ANIM_PARATROOPA_SHELL_IDLE       = 10,
    AI_ANIM_PARATROOPA_SHELL_EXIT       = 11,
};

void N(ParatroopaAI_Windup)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->curAnim = enemy->animList[AI_ANIM_PARATROOPA_SHELL_DIVE];
    npc->jumpVel = -5.0f;
    npc->jumpScale = 0.15f;

    // withdraw into shell, reducing hitbox size, just like in TackleAI
    npc->collisionHeight = enemy->varTable[AI_VAR_PARATROOPA_HEIGHT] / 2;

    npc->moveSpeed = 7.0f;
    enemy->attackOriginPos.x = npc->pos.x;
    enemy->attackOriginPos.y = npc->pos.y;
    enemy->attackOriginPos.z = npc->pos.z;
    enemy->firstStrikeActive = true;

    ai_enemy_play_sound(npc, SOUND_PARAGOOMBA_DIVE, 0);
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->duration = 12;
    script->AI_TEMP_STATE = AI_STATE_PARATROOPA_DIVE;
}

void N(ParatroopaAI_Dive)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->jumpVel += npc->jumpScale;
    npc->pos.y += npc->jumpVel;
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->firstStrikeActive = false;
        npc->jumpScale = 0.3f;
        npc->jumpVel = 0.0f;
        npc->moveSpeed = 3.0f;
        npc->curAnim = enemy->animList[AI_ANIM_PARATROOPA_SHELL_IDLE];
        script->AI_TEMP_STATE = AI_STATE_PARATROOPA_OVERSHOOT;
    }
}

void N(ParatroopaAI_Overshoot)(Evt* script, MobileAISettings *arg1, EnemyDetectVolume *arg2)
{
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 posX, posY, posZ, hitDepth;
    f32 targetHoverY;

    npc->jumpVel += npc->jumpScale;
    npc->pos.y += npc->jumpVel;
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    posX = npc->pos.x;
    posY = npc->pos.y;
    posZ = npc->pos.z;
    hitDepth = 1000.0f;
    if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth)) {
        targetHoverY = posY + hoverHeight;
    } else {
        targetHoverY = hoverHeight;
    }

    if (npc->pos.y >= targetHoverY) {
        npc->duration = 10;
        npc->curAnim = enemy->animList[AI_ANIM_PARATROOPA_SHELL_EXIT];
        // restore original hitbox size
        npc->collisionHeight = enemy->varTable[AI_VAR_PARATROOPA_HEIGHT];
        script->AI_TEMP_STATE = AI_STATE_PARATROOPA_RESET;
    }
}

void N(ParatroopaAI_Reset)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    }
}

API_CALLABLE(N(ParatroopaAI_Main)) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyDetectVolume territory;
    EnemyDetectVolume* territoryPtr = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 120.0f;
    territory.detectFlags = 0;

    if (isInitialCall) {
        N(FlyingAI_Init)(npc, enemy, script, aiSettings);
        enemy->varTable[AI_VAR_PARATROOPA_HEIGHT] = npc->collisionHeight;
        script->AI_TEMP_STATE = AI_STATE_FLYING_WANDER_INIT;
    }

    npc->verticalRenderOffset = -3;

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_FLYING_WANDER_INIT:
            N(FlyingAI_WanderInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FLYING_WANDER:
            N(FlyingAI_Wander)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_FLYING_LOITER_INIT) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYING_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, aiSettings, territoryPtr);
            // fallthrough
        case AI_STATE_FLYING_LOITER:
            N(FlyingAI_Loiter)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_FLYING_ALERT_INIT) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYING_ALERT_INIT:
            N(FlyingAI_JumpInit)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_FLYING_ALERT) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYING_ALERT:
            N(FlyingAI_Jump)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_FLYING_CHASE_INIT) {
                break;
            }
            // fallthrough
        case AI_STATE_PARATROOPA_WINDUP:
            N(ParatroopaAI_Windup)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PARATROOPA_DIVE) {
                break;
            }
            // fallthrough
        case AI_STATE_PARATROOPA_DIVE:
            N(ParatroopaAI_Dive)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PARATROOPA_OVERSHOOT) {
                break;
            }
            // fallthrough
        case AI_STATE_PARATROOPA_OVERSHOOT:
            N(ParatroopaAI_Overshoot)(script, aiSettings, territoryPtr);
            if (script->AI_TEMP_STATE != AI_STATE_PARATROOPA_RESET) {
                break;
            }
            // fallthrough
        case AI_STATE_PARATROOPA_RESET:
            N(ParatroopaAI_Reset)(script, aiSettings, territoryPtr);
            break;
    }

    return ApiStatus_BLOCK;
}
