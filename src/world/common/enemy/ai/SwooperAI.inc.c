#pragma once

#include "common.h"
#include "npc.h"

enum AiStateSwooper {
    AI_STATE_SWOOPER_HANG_INIT      = 0,
    AI_STATE_SWOOPER_HANG_IDLE      = 1,  // hang and periodically search for player
    AI_STATE_SWOOPER_DETACH_INIT    = 10, // compute jump params to leap from perch (covers 30% of distance to goal)
    AI_STATE_SWOOPER_DETACH         = 11, // execute detach motion
    AI_STATE_SWOOPER_ARC_INIT       = 12, // compute jump params to complete dive toward target
    AI_STATE_SWOOPER_ARC            = 13, // execute dive motion
    AI_STATE_SWOOPER_REATTACH       = 14, // reattach to perch after parabolic motion is complete
    AI_STATE_SWOOPER_COOLDOWN       = 15, // time after reattaching before detection is possible again
};

enum AiVarsSwooper {
    AI_VAR_SWOOPER_UNUSED_TIME      = 0,
    AI_VAR_SWOOPER_FLOOR_Y          = 1,
};

API_CALLABLE(N(SwooperAI_Main)) {
    EnemyDetectVolume detectVolume;
    PlayerStatus* playerStatus = &gPlayerStatus;
    EnemyDetectVolume* detectVolumePtr = &detectVolume;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);
    f32 x, y, z, hitDepth;
    f32 floorY;

    detectVolumePtr->skipPlayerDetectChance = 0;
    detectVolumePtr->shape = enemy->territory->wander.detectShape;
    detectVolumePtr->pointX = enemy->territory->wander.detectPos.x;
    detectVolumePtr->pointZ = enemy->territory->wander.detectPos.z;
    detectVolumePtr->sizeX = enemy->territory->wander.detectSize.x;
    detectVolumePtr->sizeZ = enemy->territory->wander.detectSize.z;
    detectVolumePtr->halfHeight = 500.0f;
    detectVolumePtr->detectFlags = 0;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_SWOOPER_HANG_INIT;
        npc->duration = 0;
        enemy->aiFlags |= AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE;
        hitDepth = 1000.0f;
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;
        npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth);
        enemy->varTable[AI_VAR_SWOOPER_FLOOR_Y] = y;
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_SWOOPER_HANG_INIT:
            npc->curAnim = enemy->animList[0];
            npc->verticalRenderOffset = npc->collisionHeight;
            npc->flags |= NPC_FLAG_UPSIDE_DOWN;
            script->functionTemp[1] = 0;
            script->AI_TEMP_STATE = AI_STATE_SWOOPER_HANG_IDLE;
            // fallthrough
        case AI_STATE_SWOOPER_HANG_IDLE:
            if (aiSettings->playerSearchInterval >= 0) {
                if (script->functionTemp[1] <= 0) {
                    script->functionTemp[1] = aiSettings->playerSearchInterval;
                    if (basic_ai_check_player_dist(detectVolumePtr, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, false)) {
                        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                        script->AI_TEMP_STATE = AI_STATE_SWOOPER_DETACH_INIT;
                    }
                }
                script->functionTemp[1]--;
            }
            if (script->AI_TEMP_STATE != AI_STATE_SWOOPER_DETACH_INIT) {
                break;
            }
            // fallthrough
        case AI_STATE_SWOOPER_DETACH_INIT:
            npc->curAnim = enemy->animList[3];
            npc->yaw = atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            npc->jumpScale = 1.3f;
            npc->jumpVel = 0.0f;
            npc->moveSpeed = aiSettings->moveSpeed;
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            hitDepth = 1000.0f;
            if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth)) {
                floorY = enemy->varTable[AI_VAR_SWOOPER_FLOOR_Y];
                npc->moveToPos.y = floorY + ((npc->pos.y - floorY) * 0.7);
            } else {
                npc->moveToPos.y = playerStatus->pos.y + ((npc->pos.y - playerStatus->pos.y) * 0.7);
            }
            // save detach y height -- note we use z component here
            npc->moveToPos.z = npc->pos.y;
            script->AI_TEMP_STATE = AI_STATE_SWOOPER_DETACH;
            // fallthrough
        case AI_STATE_SWOOPER_DETACH:
            if (npc->moveSpeed > 0.0) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, npc->moveSpeed, npc->yaw, npc->collisionHeight, npc->collisionDiameter)) {
                    npc->moveSpeed = 0.0f;
                }
                npc->yaw = atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            }

            npc->jumpVel -= npc->jumpScale;
            npc->pos.y += npc->jumpVel;
            if (npc->pos.y < npc->moveToPos.y) {
                npc->pos.y = npc->moveToPos.y;
                script->AI_TEMP_STATE = AI_STATE_SWOOPER_ARC_INIT;
            } else {
                break;
            }
            // fallthrough
        case AI_STATE_SWOOPER_ARC_INIT:
            npc->planarFlyDist = dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (npc->planarFlyDist < 60.0f) {
                npc->planarFlyDist = 60.0f;
            }

            floorY = enemy->varTable[AI_VAR_SWOOPER_FLOOR_Y];
            y = (floorY + 10.0) - npc->pos.y;

            npc->moveSpeed = aiSettings->chaseSpeed;
            npc->duration = npc->planarFlyDist / npc->moveSpeed;
            if (npc->duration == 0) {
                npc->duration = 1;
            }
            // solve projectile motion equation for required acceleration
            npc->jumpScale = -fabsf(2.0f * (y - (npc->jumpVel * npc->duration)) / SQ(npc->duration));
            npc->verticalRenderOffset = 0;
            npc->flags &= ~NPC_FLAG_UPSIDE_DOWN;
            enemy->varTable[AI_VAR_SWOOPER_UNUSED_TIME] = 5;
            npc->duration = 0;
            script->AI_TEMP_STATE = AI_STATE_SWOOPER_ARC;
            // fallthrough
        case AI_STATE_SWOOPER_ARC:
            npc->jumpVel -= npc->jumpScale;
            if (npc->jumpVel < 0.0f) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                hitDepth = -npc->jumpVel;
                if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth)) {
                    npc->jumpVel = 0.0f;
                }
            }

            npc->pos.y += npc->jumpVel;
            if (npc->moveSpeed > 0.0) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, npc->moveSpeed, npc->yaw,
                                                       npc->collisionHeight, npc->collisionDiameter))
                {
                    npc->moveSpeed = 0.0f;
                } else if (npc->jumpVel < -2.5) {
                    npc->duration++;
                    if (npc->duration >= aiSettings->chaseUpdateInterval) {
                        f32 angle = atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        f32 angleDiff = get_clamped_angle_diff(npc->yaw, angle);

                        // cap the turn rate
                        if (aiSettings->chaseTurnRate < fabsf(angleDiff)) {
                            if (angleDiff < 0.0f) {
                                angle = npc->yaw - aiSettings->chaseTurnRate;
                            } else {
                                angle = npc->yaw + aiSettings->chaseTurnRate;
                            }
                        }
                        npc->yaw = clamp_angle(angle);
                        npc->duration = 0;
                    }
                }
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            }

            enemy->varTable[AI_VAR_SWOOPER_UNUSED_TIME]--;
            if (enemy->varTable[AI_VAR_SWOOPER_UNUSED_TIME] <= 0) {
                enemy->varTable[AI_VAR_SWOOPER_UNUSED_TIME] = 5;
            }

            if (npc->pos.y > npc->moveToPos.z) {
                npc->pos.y = npc->moveToPos.z;
                script->AI_TEMP_STATE = AI_STATE_SWOOPER_REATTACH;
            } else {
                break;
            }
            // fallthrough
        case AI_STATE_SWOOPER_REATTACH:
            npc->curAnim = enemy->animList[8];
            npc->verticalRenderOffset = npc->collisionHeight;
            npc->flags |= NPC_FLAG_UPSIDE_DOWN;
            npc->duration = 15;
            script->AI_TEMP_STATE = AI_STATE_SWOOPER_COOLDOWN;
            // fallthrough
        case AI_STATE_SWOOPER_COOLDOWN:
            npc->duration--;
            if (npc->duration <= 0) {
                script->AI_TEMP_STATE = AI_STATE_SWOOPER_HANG_INIT;
            }
    }
    return ApiStatus_BLOCK;
}
