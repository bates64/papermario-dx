#pragma once

#include "common.h"
#include "world/ai.h"

#include "world/common/enemy/ai/HoppingAI.inc.c"

void N(StoneChompAI_HopInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    basic_ai_wander_init(script, settings, detect);
    npc->jumpVel = rand_int(5) + 8.0;
    npc->jumpScale = 1.5f;
}

void N(StoneChompAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    basic_ai_chase_init(script, settings, detect);
    npc->jumpVel = rand_int(5) + 5.0;
    npc->jumpScale = 1.5f;
}

API_CALLABLE(N(StoneChompAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 100.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        npc->duration = 0;
        npc->flags &= ~NPC_FLAG_JUMPING;
        npc->flags &= ~NPC_FLAG_GRAVITY;
        npc->flags |= NPC_FLAG_FLYING;
        script->functionTemp[1] = 0;
        script->AI_TEMP_STATE = AI_STATE_HOP_INIT;
        if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_HOP_INIT:
            N(StoneChompAI_HopInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_HOP:
            N(HoppingAI_Hop)(script, settings, detect);
            break;
        case AI_STATE_LOITER_INIT:
            N(HoppingAI_LoiterInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_LOITER:
            N(HoppingAI_Loiter)(script, settings, detect);
            break;
        case AI_STATE_CHASE_INIT:
            N(StoneChompAI_ChaseInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            N(HoppingAI_Chase)(script, settings, detect);
            break;
        case AI_STATE_LOSE_PLAYER:
            N(HoppingAI_LosePlayer)(script, settings, detect);
            break;
    }
    return ApiStatus_BLOCK;
}
