#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/Spiny.h"

#include "world/common/enemy/ai/TackleWanderAI.inc.c"

#define DESPAWN_SCREEN_DIST 50

enum SpinyAiStates {
    AI_STATE_SPINY_HOLD_READY   = 100,
    AI_STATE_SPINY_THROW_READY  = 101,
    AI_STATE_SPINY_AIRBORNE     = 102,
    AI_STATE_SPINY_LANDED       = 103,
    AI_STATE_SPINY_RESET_INIT   = 110, // use if throw misses or goes off screen
    AI_STATE_SPINY_RESET        = 111, // become available to throw again
    AI_STATE_SPINY_SUSPEND      = 200,
};

enum SpinyAiVars {
    // inherits vars 2 - 9 from TackleAI
    AI_VAR_SPINY_STATUS         = 10, // see: SpinyStatus
    AI_VAR_SPINY_THROWER        = 11, // npcID of Lakitu while being held/thrown
    AI_VAR_SPINY_ZERO_FLOOR     = 13, // forces the NPC to use gravity when above y = 0, and turn it off when y <= 0
};

enum SpinyStatus {
    SPINY_STATUS_IDLE           = 0, // missile is unoccupied and ready to be thrown
    SPINY_STATUS_RESERVED       = 1, // a thrower has claimed this spiny
    SPINY_STATUS_HOLD_REQUEST   = 2, // hold requested by thrower
    SPINY_STATUS_THROW_REQUEST  = 3, // throw requested by thrower
    SPINY_STATUS_AIRBORNE       = 4, // moving through the air
    SPINY_STATUS_LANDED         = 5, // walking around on the ground
    SPINY_STATUS_RESET          = 100,
};

API_CALLABLE(N(SpinyAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;
    Npc* throwerNpc;
    s32 screenX, screenY, screenZ;
    f32 x, y, z, hitDepth;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        enemy->varTable[AI_VAR_TACKLE_HEIGHT] = npc->collisionHeight;
        enemy->aiFlags |= AI_FLAG_SKIP_EMOTE_AFTER_FLEE;
    }

    if (isInitialCall || (enemy->varTable[AI_VAR_SPINY_STATUS] == SPINY_STATUS_RESET)) {
        script->AI_TEMP_STATE = AI_STATE_SPINY_HOLD_READY;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->flags &= ~NPC_FLAG_JUMPING;
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        npc->flags &= ~NPC_FLAG_GRAVITY;
        npc->flags |= NPC_FLAG_FLYING;
        enemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_IDLE;
        enemy->varTable[AI_VAR_SPINY_THROWER] = -1;
        npc->pos.x = NPC_DISPOSE_POS_X;
        npc->pos.y = NPC_DISPOSE_POS_Y;
        npc->pos.z = NPC_DISPOSE_POS_Z;
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        npc->duration = 0;
        npc->collisionHeight = enemy->varTable[AI_VAR_TACKLE_HEIGHT];
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        if (npc->flags & NPC_FLAG_JUMPING) {
            npc->curAnim = ANIM_Spiny_Anim18;
            npc->moveSpeed = 0.0f;
            npc->jumpVel = 0.0f;
            npc->jumpScale = 1.0f;
            script->AI_TEMP_STATE = AI_STATE_SPINY_AIRBORNE;
        } else {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 40, nullptr);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
            script->AI_TEMP_STATE = AI_STATE_SPINY_SUSPEND;
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_WANDER_INIT;
        }
    }

    get_screen_coords(CAM_DEFAULT, npc->pos.x, npc->pos.y, npc->pos.z, &screenX, &screenY, &screenZ);
    if (script->AI_TEMP_STATE < AI_STATE_SPINY_HOLD_READY
            && (screenX < -DESPAWN_SCREEN_DIST || screenX > SCREEN_WIDTH + DESPAWN_SCREEN_DIST)
        ) {
        script->AI_TEMP_STATE = AI_STATE_SPINY_RESET_INIT;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_WANDER_INIT:
            basic_ai_wander_init(script, settings, detect);
            npc->collisionHeight = enemy->varTable[AI_VAR_TACKLE_HEIGHT];
            if (enemy->varTable[AI_VAR_SPINY_ZERO_FLOOR]) {
                if (npc->pos.y <= 0.0) {
                    npc->flags |= NPC_FLAG_FLYING;
                    npc->flags &= ~NPC_FLAG_GRAVITY;
                } else {
                    npc->flags |= NPC_FLAG_GRAVITY;
                    npc->flags &= ~NPC_FLAG_FLYING;
                }
            }
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

        case AI_STATE_TACKLE_INIT:
            N(TackleAI_InitTackle)(script, settings, detect);
            // fallthrough
        case AI_STATE_PRE_TACKLE:
            N(TackleAI_PreTackle)(script, settings, detect);
            npc->collisionHeight = enemy->varTable[AI_VAR_TACKLE_HEIGHT];
            break;

        case AI_STATE_TACKLE:
            N(TackleAI_Tackle)(script, settings, detect);
            break;

        case AI_STATE_POST_TACKLE:
            N(TackleAI_PostTackle)(script, settings, detect);
            break;

        case AI_STATE_SPINY_HOLD_READY:
            if (enemy->varTable[AI_VAR_SPINY_STATUS] != SPINY_STATUS_HOLD_REQUEST) {
                break;
            }
            throwerNpc = get_npc_unsafe(get_enemy(enemy->varTable[AI_VAR_SPINY_THROWER])->npcID);
            if (throwerNpc->yaw < 180.0) {
                npc->pos.x = throwerNpc->pos.x + 12.0;
            } else {
                npc->pos.x = throwerNpc->pos.x - 12.0;
            }
            npc->pos.y = throwerNpc->pos.y + 25.0;
            npc->pos.z = throwerNpc->pos.z + 1.0;
            npc->rot.y = 0.0f;
            npc->flags |= NPC_FLAG_FLYING;
            npc->flags &= ~NPC_FLAG_INVISIBLE;
            npc->flags &= ~NPC_FLAG_GRAVITY;
            npc->renderYaw = 0.0f;
            npc->curAnim = ANIM_Spiny_Anim18;
            script->AI_TEMP_STATE = AI_STATE_SPINY_THROW_READY;
            // fallthrough
        case AI_STATE_SPINY_THROW_READY:
            if (enemy->varTable[AI_VAR_SPINY_STATUS] != SPINY_STATUS_THROW_REQUEST) {
                break;
            }
            enemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_AIRBORNE;
            npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatus.pos.x, gPlayerStatus.pos.z);
            npc->moveSpeed = 2.5f;
            npc->jumpVel = 8.0f;
            npc->jumpScale = 0.8f;
            npc->flags |= NPC_FLAG_JUMPING;
            script->AI_TEMP_STATE = AI_STATE_SPINY_AIRBORNE;
            // fallthrough
        case AI_STATE_SPINY_AIRBORNE:
            if (npc->moveSpeed > 0.0) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                if (!npc_test_move_simple_with_slipping(npc->collisionChannel,
                    &x, &y, &z, npc->moveSpeed, npc->yaw, npc->collisionHeight, npc->collisionDiameter)
                ) {
                    npc_move_heading(npc, npc->moveSpeed, npc->yaw);
                } else {
                    npc->moveSpeed = 0.0f;
                }
            }
            if (npc->jumpVel < 0.0) {
                x = npc->pos.x;
                y = npc->pos.y + 13.0;
                z = npc->pos.z;
                hitDepth = fabsf(npc->jumpVel) + 16.0;
                if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth)
                    && (hitDepth <= (fabsf(npc->jumpVel) + 13.0))
                ) {
                    npc->pos.y = y;
                    enemy->territory->wander.centerPos.x = npc->pos.x;
                    enemy->territory->wander.centerPos.y = npc->pos.y;
                    enemy->territory->wander.centerPos.z = npc->pos.z;
                    enemy->territory->wander.detectPos.x = npc->pos.x;
                    enemy->territory->wander.detectPos.y = npc->pos.y;
                    enemy->territory->wander.detectPos.z = npc->pos.z;
                    enemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_LANDED;
                    if (enemy->varTable[AI_VAR_SPINY_ZERO_FLOOR]) {
                        if (npc->pos.y <= 0.0) {
                            npc->flags |= NPC_FLAG_FLYING;
                            npc->flags &= ~NPC_FLAG_GRAVITY;
                        } else {
                            npc->flags |= NPC_FLAG_GRAVITY;
                            npc->flags &= ~NPC_FLAG_FLYING;
                        }
                    } else if (enemy->territory->wander.isFlying) {
                        npc->flags |= NPC_FLAG_FLYING;
                        npc->flags &= ~NPC_FLAG_GRAVITY;
                    } else {
                        npc->flags |= NPC_FLAG_GRAVITY;
                        npc->flags &= ~NPC_FLAG_FLYING;
                    }
                    npc->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                    npc->flags &= ~NPC_FLAG_JUMPING;
                    npc->jumpVel = 0.0f;
                    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatus.pos.x, gPlayerStatus.pos.z);
                    npc->curAnim = ANIM_Spiny_Anim1A;
                    npc->duration = 3;
                    script->AI_TEMP_STATE = AI_STATE_SPINY_LANDED;
                    break;
                }
            }
            npc->pos.y += npc->jumpVel;
            npc->jumpVel -= npc->jumpScale;
            break;

        case AI_STATE_SPINY_LANDED:
            npc->duration--;
            if (npc->duration <= 0) {
                npc->flags &= ~NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                npc->curAnim = ANIM_Spiny_Anim01;
                script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
            }
            break;

        case AI_STATE_SPINY_RESET_INIT:
            npc->duration = 30;
            npc->pos.x = NPC_DISPOSE_POS_X;
            npc->pos.y = NPC_DISPOSE_POS_Y;
            npc->pos.z = NPC_DISPOSE_POS_Z;
            npc->flags |= NPC_FLAG_FLYING | NPC_FLAG_INVISIBLE;
            npc->flags &= ~NPC_FLAG_GRAVITY;
            script->AI_TEMP_STATE = AI_STATE_SPINY_RESET;
            // fallthrough
        case AI_STATE_SPINY_RESET:
            npc->duration--;
            if (npc->duration <= 0) {
                enemy->varTable[AI_VAR_SPINY_STATUS] = SPINY_STATUS_IDLE;
                script->AI_TEMP_STATE = AI_STATE_SPINY_HOLD_READY;
            }
            break;

        case AI_STATE_SPINY_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}

