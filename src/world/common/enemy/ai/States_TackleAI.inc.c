#ifndef _AI_TACKLE_STATES_INC_
#define _AI_TACKLE_STATES_INC_ 0

#include "common.h"
#include "npc.h"

// used with TacklePatrolAI, TackleAI, SpinyAI
// all functions only used here

enum AiVarsTackle {
    AI_TACKLE_VAR_PRE_DELAY = 2, // IN: delay time before dashing
    AI_TACKLE_VAR_MIN_CHASE_TIME = 3, // IN: minimum time to dash during tackle
    AI_TACKLE_VAR_CHASE_TIME = 4, // computed chase time to target
    AI_TACKLE_VAR_POST_DELAY = 5, // IN: delay time after dashing
    AI_TACKLE_VAR_HEIGHT = 6, // original collision height
    AI_TACKLE_VAR_TYPE  = 7, // IN: see TackleEnemyType
    AI_TACKLE_VAR_SPIKY = 8, // boolean tracking whether BonyBeetle spikes are extended
    AI_TACKLE_VAR_CHANGE_TIME = 9, // duration to suspend AI while BonyBeetle swaps spike state
};

enum TackleEnemyType {
    TACKLER_KOOPA_TROOPA    = 0,
    TACKLER_DARK_TROOPA     = 1,
    TACKLER_BUZZY_BEETLE    = 2,
    TACKLER_SPIKE_TOP       = 3,
    TACKLER_SPINY           = 4,
    TACKLER_KOOPATROL       = 5,
    TACKLER_BONY_BEETLE     = 6,
};

void N(TackleAI_InitTackle)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
    npc->duration = enemy->varTable[AI_TACKLE_VAR_PRE_DELAY];
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    script->AI_TEMP_STATE = AI_STATE_PRE_TACKLE;
}

void N(TackleAI_PreTackle)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 dist;

    if (npc->duration > 0) {
        npc->duration--;
    }
    if (npc->duration > 0) {
        return;
    }

    if (npc->turnAroundYawAdjustment != 0) {
        return;
    }

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_HIT];
    npc->moveSpeed = aiSettings->chaseSpeed;

    // koopa collision height is halved during the tackle
    switch (enemy->varTable[AI_TACKLE_VAR_TYPE]) {
        case TACKLER_KOOPA_TROOPA:
        case TACKLER_DARK_TROOPA:
        case TACKLER_KOOPATROL:
            npc->collisionHeight = enemy->varTable[AI_TACKLE_VAR_HEIGHT] / 2;
            break;
    }

    dist = dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->duration = (dist / npc->moveSpeed) + 0.8;
    if (npc->duration < enemy->varTable[AI_TACKLE_VAR_MIN_CHASE_TIME]) {
        npc->duration = enemy->varTable[AI_TACKLE_VAR_MIN_CHASE_TIME];
    }
    enemy->varTable[AI_TACKLE_VAR_CHASE_TIME] = npc->duration;
    script->AI_TEMP_STATE = AI_STATE_TACKLE;
}

void N(TackleAI_Tackle)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    b32 hit;
    f32 posX;
    f32 posY;
    f32 posZ;

    if (npc->duration == enemy->varTable[AI_TACKLE_VAR_CHASE_TIME] - 1) {
        enemy->attackOriginPos.x = npc->pos.x;
        enemy->attackOriginPos.y = npc->pos.y;
        enemy->attackOriginPos.z = npc->pos.z;
        enemy->firstStrikeActive = true;
    }

    posX = npc->pos.x;
    posY = npc->pos.y;
    posZ = npc->pos.z;

    hit = npc_test_move_simple_with_slipping(npc->collisionChannel, &posX, &posY, &posZ, npc->moveSpeed, npc->yaw, npc->collisionHeight, npc->collisionDiameter);
    if (!hit) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);

        if (npc->duration > 0) {
            npc->duration--;
        }
        if (npc->duration > 0) {
            return;
        }
    }

    enemy->firstStrikeActive = false;
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_TACKLE_POST];
    npc->duration = 0;
    script->AI_TEMP_STATE = AI_STATE_POST_TACKLE;
}

void N(TackleAI_PostTackle)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration++;
    if (npc->duration == 3) {
        npc->collisionHeight = enemy->varTable[AI_TACKLE_VAR_HEIGHT];
    }

    if (npc->duration < enemy->varTable[AI_TACKLE_VAR_POST_DELAY]) {
        return;
    }

    npc->collisionHeight = enemy->varTable[AI_TACKLE_VAR_HEIGHT];
    script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
}

#endif
