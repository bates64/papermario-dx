#pragma once

#include "common.h"
#include "effects.h"
#include "world/ai.h"

#define FIRST_BULLET_NPCID  50
#define LAST_BULLET_NPCID   59

enum BulletAiStates {
    AI_STATE_BULLET_INIT        = 0,
    AI_STATE_BULLET_READY       = 1,
    AI_STATE_BULLET_FIRED       = 2,
    AI_STATE_BULLET_HIT         = 3,
};

enum BulletAiVars {
    AI_VAR_BULLET_STATUS        = 0, // see: BulletLifecycle
    AI_VAR_BULLET_PARENT        = 1, // npcID of bullet's blaster
    AI_VAR_BULLET_RANGE         = 2, // limiting x position of bullets
};

enum BulletAiAnims {
    AI_ANIM_BULLET_8            = 8,
};

enum BlasterAiStates {
    AI_STATE_BLASTER_INIT       = 0,
    AI_STATE_BLASTER_PREPARE    = 10,
    AI_STATE_BLASTER_FIRE       = 11,
    AI_STATE_BLASTER_COOLDOWN   = 12,
};

enum BlasterAiVars {
    AI_VAR_BLASTER_CHILD        = 0, // npcID of blaster's latest bullet
    AI_VAR_BLASTER_RANGE        = 1, // limiting x position of bullets
};

// coordinates state between bullets and blaster, marking bullets as either available for firing or not
enum BulletStatus {
    BULLET_STATUS_IDLE          = 0, // bullet is unoccupied and ready to be fired
    BULLET_STATUS_RESERVED      = 1, // bullet has been selected for firing, awaiting blast animation to finish
    BULLET_STATUS_FIRING        = 2,
    BULLET_STATUS_ACTIVE        = 3, // bullet has been fired and is moving
    BULLET_STATUS_DONE          = 100, // bullet has completed its motion and waiting to reset
};

s32 N(BillBlasterAI_GetIdleBulletNpcID)(void) {
    s32 i;

    for (i = FIRST_BULLET_NPCID; i <= LAST_BULLET_NPCID; i++) {
        if (get_enemy(i)->varTable[AI_VAR_BULLET_STATUS] == BULLET_STATUS_IDLE) {
            return i;
        }
    }

    return -1;
}

API_CALLABLE(N(BulletBillAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *script->ptrReadPos);
    b32 reachedRangeLimit = false;
    b32 done = false;
    Npc* blasterNpc;
    f32 nextX, nextZ;
    f32 deltaY;

    if (isInitialCall || enemy->varTable[AI_VAR_BULLET_STATUS] == BULLET_STATUS_DONE) {
        script->AI_TEMP_STATE = AI_STATE_BULLET_INIT;
        npc->duration = 0;
        enemy->aiFlags |= AI_FLAG_SKIP_EMOTE_AFTER_FLEE;
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        npc->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
        enemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_IDLE;
        enemy->varTable[AI_VAR_BULLET_PARENT] = -1;
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_BULLET_INIT:
            npc->pos.x = NPC_DISPOSE_POS_X;
            npc->pos.y = NPC_DISPOSE_POS_Y;
            npc->pos.z = NPC_DISPOSE_POS_Z;
            npc->rot.y = 0.0f;
            npc->duration = 0;
            npc->flags |= NPC_FLAG_INVISIBLE;
            npc->flags &= ~NPC_FLAG_DONT_UPDATE_SHADOW_Y;
            disable_npc_shadow(npc);
            enemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_IDLE;
            script->AI_TEMP_STATE = AI_STATE_BULLET_READY;
            // fallthrough
        case AI_STATE_BULLET_READY:
            // do nothing until a blaster has reserved this bullet and set status to firing
            if (enemy->varTable[AI_VAR_BULLET_STATUS] != BULLET_STATUS_FIRING) {
                break;
            }
            enemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_ACTIVE;
            blasterNpc = get_npc_unsafe(get_enemy(enemy->varTable[AI_VAR_BULLET_PARENT])->npcID);
            npc->flags &= ~NPC_FLAG_INVISIBLE;
            npc->pos.x = blasterNpc->pos.x;
            npc->pos.y = blasterNpc->pos.y + 11.0;
            npc->pos.z = blasterNpc->pos.z + 1.0;
            npc->yaw = blasterNpc->yaw;
            npc->moveSpeed = aiSettings->chaseSpeed;
            add_vec2D_polar(&npc->pos.x, &npc->pos.z, 25.0f, npc->yaw);
            if (npc->yaw < 180.0f) {
                npc->renderYaw = 180.0f;
            } else {
                npc->renderYaw = 0.0f;
            }
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
            npc->duration = 300;
            npc->flags |= (NPC_FLAG_DIRTY_SHADOW | NPC_FLAG_DONT_UPDATE_SHADOW_Y);
            enable_npc_shadow(npc);
            script->AI_TEMP_STATE = AI_STATE_BULLET_FIRED;
            // fallthrough
        case AI_STATE_BULLET_FIRED:
            deltaY = (npc->pos.y - gPlayerStatusPtr->pos.y);
            if ((deltaY > 190.0) || (deltaY < -120.0)) {
                done = true;
                break;
            }

            nextX = npc->pos.x;
            nextZ = npc->pos.z;
            add_vec2D_polar(&nextX, &nextZ, npc->moveSpeed, npc->yaw);
            if (npc->yaw < 180.0f) {
                if (enemy->varTable[AI_VAR_BULLET_RANGE] <= nextX) {
                    reachedRangeLimit = true;
                }
            } else {
                if (nextX <= enemy->varTable[AI_VAR_BULLET_RANGE]) {
                    reachedRangeLimit = true;
                }
            }

            if (reachedRangeLimit) {
                npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_HIT];
                ai_enemy_play_sound(npc, SOUND_SEQ_BULLET_BILL_EXPLODE, 0);
                fx_ring_blast(0, npc->pos.x, npc->pos.y + 5.0f, npc->pos.z + 1.0f, 0.05f, 20);
                fx_smoke_burst(0, npc->pos.x, npc->pos.y + 5.0f, npc->pos.z + 0.0f, 1.2f, 25);
                npc->duration = 1;
                script->AI_TEMP_STATE = AI_STATE_BULLET_HIT;
            } else {
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            }

            if (script->AI_TEMP_STATE != AI_STATE_BULLET_HIT) {
                break;
            }
            // fallthrough
        case AI_STATE_BULLET_HIT:
            npc->duration--;
            if (npc->duration <= 0) {
                done = true;
            }
            break;
    }
    if (done) {
        enemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_DONE;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(N(BillBlasterAI_Main)) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);
    s32 bulletNpcID;
    Enemy* bulletEnemy;
    f32 deltaY;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_BLASTER_INIT;
        npc->duration = 30;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        disable_npc_shadow(npc);
    }

    deltaY = npc->pos.y - gPlayerStatusPtr->pos.y;
    if ((deltaY > 190.0) || (deltaY < -80.0)) {
        return ApiStatus_BLOCK;
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_BLASTER_INIT:
            npc->duration--;
            if (npc->duration <= 0) {
                script->AI_TEMP_STATE = AI_STATE_BLASTER_PREPARE;
            }
            break;
        case AI_STATE_BLASTER_PREPARE:
            bulletNpcID = N(BillBlasterAI_GetIdleBulletNpcID)();
            enemy->varTable[AI_VAR_BLASTER_CHILD] = bulletNpcID;
            if (bulletNpcID > 0) {
                bulletEnemy = get_enemy(bulletNpcID);
                bulletEnemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_RESERVED;
                bulletEnemy->varTable[AI_VAR_BULLET_PARENT] = enemy->npcID;
                bulletEnemy->varTable[AI_VAR_BULLET_RANGE] = enemy->varTable[AI_VAR_BLASTER_RANGE];
                npc->curAnim = enemy->animList[AI_ANIM_BULLET_8];
                npc->duration = 10;
                script->AI_TEMP_STATE = AI_STATE_BLASTER_FIRE;
            } else {
                // no idle bullets available, sleep for 40-100 frames
                npc->duration = (rand_int(1000) % 60) + 40;
                script->AI_TEMP_STATE = AI_STATE_BLASTER_INIT;
            }
            break;
        case AI_STATE_BLASTER_FIRE:
            npc->duration--;
            if (npc->duration > 0) {
                break;
            }
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
            bulletEnemy = get_enemy(enemy->varTable[AI_VAR_BLASTER_CHILD]);
            bulletEnemy->varTable[AI_VAR_BULLET_STATUS] = BULLET_STATUS_FIRING;
            ai_enemy_play_sound(npc, SOUND_BLASTER_FIRE, SOUND_PARAM_MORE_QUIET);
            npc->duration = 5;
            script->AI_TEMP_STATE = AI_STATE_BLASTER_COOLDOWN;
            // fallthrough
        case AI_STATE_BLASTER_COOLDOWN:
            npc->duration--;
            if (npc->duration <= 0) {
                npc->duration = (rand_int(1000) % 60) + 40;
                script->AI_TEMP_STATE = AI_STATE_BLASTER_INIT;
            }
            break;
    }
    return ApiStatus_BLOCK;
}
