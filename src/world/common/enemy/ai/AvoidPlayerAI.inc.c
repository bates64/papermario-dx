#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

enum AvoidAiAnims {
    AI_ANIM_AVOID_SEE_PLAYER    = 8,
};

void N(AvoidPlayerAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    f32 posXFwd, posYFwd, posZFwd;
    f32 posXCW, posYCW, posZCW;
    f32 posXCCW, posYCCW, posZCCW;

    f32 deltaYaw;
    f32 yawFwd;
    f32 distFwd;
    f32 distCW;
    f32 distCCW;
    b32 detectedPlayer;

    npc->duration = settings->chaseUpdateInterval / 2 + rand_int(settings->chaseUpdateInterval / 2 + 1);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = settings->chaseSpeed;
    detectedPlayer = false;

    // get a heading directly away from the player
    yawFwd = clamp_angle(atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x,
                                 gPlayerStatusPtr->pos.z) + 180.0f);
    deltaYaw = get_clamped_angle_diff(npc->yaw, yawFwd);
    if (settings->chaseTurnRate < fabsf(deltaYaw)) {
        if (deltaYaw < 0.0f) {
            yawFwd = npc->yaw - settings->chaseTurnRate;
        } else {
            yawFwd = npc->yaw + settings->chaseTurnRate;
        }
    }

    npc->yaw = clamp_angle(yawFwd);

    posXFwd = npc->pos.x;
    posYFwd = npc->pos.y;
    posZFwd = npc->pos.z;

    yawFwd = clamp_angle(atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) + 180.0f);
    distFwd = 0.0f;
    distCW = 0.0f;
    distCCW = 0.0f;

    if (npc_test_move_simple_without_slipping(npc->collisionChannel,
            &posXFwd, &posYFwd, &posZFwd, npc->moveSpeed * 4.5,
            yawFwd, npc->collisionHeight, npc->collisionDiameter)) {
        distFwd = dist2D(npc->pos.x, npc->pos.z, posXFwd, posZFwd);

        // check 'whisker' 35 degrees CW
        posXCW = npc->pos.x;
        posYCW = npc->pos.y;
        posZCW = npc->pos.z;
        if (npc_test_move_simple_without_slipping(npc->collisionChannel,
                &posXCW, &posYCW, &posZCW, npc->moveSpeed * 4.5,
                clamp_angle(yawFwd + 35.0f), npc->collisionHeight, npc->collisionDiameter)) {
            distCW = dist2D(npc->pos.x, npc->pos.z, posXCW, posZCW);
        }

        // check 'whisker' 35 degrees CCW
        posXCCW = npc->pos.x;
        posYCCW = npc->pos.y;
        posZCCW = npc->pos.z;
        if (npc_test_move_simple_without_slipping(npc->collisionChannel,
                &posXCCW, &posYCCW, &posZCCW, npc->moveSpeed * 4.5,
                clamp_angle(yawFwd - 35.0f), npc->collisionHeight, npc->collisionDiameter)) {
            distCCW = dist2D(npc->pos.x, npc->pos.z, posXCCW, posZCCW);
        }

        if ((distFwd < npc->moveSpeed * 1.5) && (distCW < npc->moveSpeed * 1.5) && (distCCW < npc->moveSpeed * 1.5) &&
            (basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, false))) {
            detectedPlayer = true;
        }

        if (!detectedPlayer) {
            if ((distCW < distFwd) && (distCCW < distCW)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXFwd, posZFwd);
            } else if ((distCW < distFwd) && (distCW < distCCW)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXFwd, posZFwd);
            } else if ((distFwd < distCW) && (distCCW < distFwd)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXCW, posZCW);
            } else if ((distCCW < distCW) && (distFwd < distCCW)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXCW, posZCW);
            } else if ((distFwd < distCCW) && (distCW < distFwd)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXCCW, posZCCW);
            } else if ((distCW < distCCW) && (distFwd < distCW)) {
                yawFwd = atan2(npc->pos.x, npc->pos.z, posXCCW, posZCCW);
            }

            deltaYaw = get_clamped_angle_diff(npc->yaw, yawFwd);
            if (settings->chaseTurnRate < fabsf(deltaYaw)) {
                if (deltaYaw < 0.0f) {
                    yawFwd = npc->yaw - settings->chaseTurnRate;
                } else {
                    yawFwd = npc->yaw + settings->chaseTurnRate;
                }
            }
            npc->yaw = clamp_angle(yawFwd);
        }
    }
    if (detectedPlayer) {
        npc->duration = 10;
        npc->curAnim = enemy->animList[AI_ANIM_AVOID_SEE_PLAYER];
    }
    script->AI_TEMP_STATE = AI_STATE_CHASE;
}

void N(AvoidPlayerAI_Chase)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 25;
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
    } else {
        if (npc->curAnim != enemy->animList[AI_ANIM_AVOID_SEE_PLAYER]) {
            if (npc->moveSpeed < 4.0) {
                npc_surface_spawn_fx(npc, SURFACE_INTERACT_WALK);
            } else {
                npc_surface_spawn_fx(npc, SURFACE_INTERACT_RUN);
            }
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        }
        if (npc->duration > 0) {
            npc->duration--;
            return;
        }
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void N(AvoidPlayerAI_LosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 0) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

API_CALLABLE(N(AvoidPlayerAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*)evt_get_variable(script, *args++);
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
            N(AvoidPlayerAI_ChaseInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            N(AvoidPlayerAI_Chase)(script, settings, detect);
            break;

        case AI_STATE_LOSE_PLAYER:
            N(AvoidPlayerAI_LosePlayer)(script, settings, detect);
            break;

        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }

    return ApiStatus_BLOCK;
}

