#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

enum HoppingAiVars {
    AI_VAR_HOPPING_KIND         = 10, // type of hopper (unused)
};

enum HoppingEnemyType {
    HOPPING_KIND_FUZZY          = 0,
    HOPPING_KIND_FOREST_FUZZY   = 1,
    HOPPING_KIND_JUNGLE_FUZZY   = 2,
};

void N(HoppingAI_HopInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z;
    s32 i;

    basic_ai_wander_init(script, settings, detect);
    npc->flags |= NPC_FLAG_JUMPING;
    npc->jumpVel = (rand_int(45) / 10.0) + 8.0;
    npc->jumpScale = 1.5f;
    ai_enemy_play_sound(npc, SOUND_SEQ_FUZZY_HOP, 0);

    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;

        for (i = 0; i < 6; i++) {
            if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, 25.0f,
                npc->yaw, npc->collisionHeight, npc->collisionDiameter)
            ) {
                npc->yaw += 30.0;
            } else {
                break;
            }
        }
    } else {
        npc->yaw = clamp_angle(npc->yaw + rand_int(60) - 30.0f);
    }
}

void N(HoppingAI_Hop)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ, hitDepth;

    if (settings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = settings->playerSearchInterval;
            if (basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, false)) {
                fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
                return;
            }
        }
        script->functionTemp[1]--;
    }

    if (npc->moveSpeed > 0.0) {
        f32 collRadius;
        f32 collHeight;
        f32 moveSpeed;

        posX = npc->pos.x;
        posY = npc->pos.y;
        posZ = npc->pos.z;
        moveSpeed = npc->moveSpeed;
        collHeight = npc->collisionHeight;
        collRadius = npc->collisionDiameter;

        if (!npc_test_move_simple_with_slipping(npc->collisionChannel,
                &posX, &posY, &posZ,
                moveSpeed, npc->yaw, collHeight, collRadius * 1.2))
        {
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        } else {
            npc->moveSpeed = 0.0f;
        }
    }

    if (npc->jumpVel < 0.0) {
        posX = npc->pos.x;
        posY = npc->pos.y + 13.0;
        posZ = npc->pos.z;
        hitDepth = fabsf(npc->jumpVel) + 16.0;

        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth) &&
            hitDepth <= fabsf(npc->jumpVel) + 13.0)
        {
            npc->jumpVel = 0.0f;
            npc->pos.y = posY;
            npc->flags &= ~NPC_FLAG_JUMPING;
            script->AI_TEMP_STATE = AI_STATE_LOITER_INIT;
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;

            if (settings->loiterMode <= 0 || settings->moveTime <= 0 || script->functionTemp[1] == 0) {
                script->AI_TEMP_STATE = AI_STATE_HOP_INIT;
            }
            return;
        }
    }
    npc->pos.y += npc->jumpVel;
    npc->jumpVel -= npc->jumpScale;
}

void N(HoppingAI_LoiterInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (settings->waitTime / 2) + rand_int((settings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void N(HoppingAI_Loiter)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (settings->playerSearchInterval >= 0 && basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, false)) {
        fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    } else if (npc->turnAroundYawAdjustment == 0) {
        npc->duration--;
        if (npc->duration <= 0) {
            script->functionTemp[1]--;
            if (script->functionTemp[1] > 0) {
                npc->yaw = clamp_angle(npc->yaw + 180.0f);
                npc->duration = (rand_int(1000) % 11) + 5;
            } else {
                script->AI_TEMP_STATE = AI_STATE_HOP_INIT;
            }
        }
    }
}

void N(HoppingAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* enemy = get_npc_unsafe(script->owner1.enemy->npcID);

    basic_ai_chase_init(script, settings, detect);
    enemy->flags |= ENEMY_FLAG_FLYING;
    enemy->jumpVel = rand_int(5) + 10.0;
    enemy->jumpScale = 1.5f;
    enemy->yaw = atan2(enemy->pos.x, enemy->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    enemy->moveSpeed = settings->chaseSpeed;
    script->AI_TEMP_STATE = AI_STATE_CHASE;
    ai_enemy_play_sound(enemy, SOUND_SEQ_FUZZY_HOP, 0);
}

void N(HoppingAI_Chase)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;
    f32 groundY, hitDepth;

    if (npc->moveSpeed > 0.0) {
        posX = npc->pos.x;
        posY = npc->pos.y;
        posZ = npc->pos.z;
        if (npc_test_move_simple_with_slipping(npc->collisionChannel, &posX, &posY, &posZ, npc->moveSpeed, npc->yaw,
                                               npc->collisionHeight, npc->collisionDiameter))
        {
            npc->moveSpeed = 0.0f;
        } else {
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        }
    }

    if (npc->jumpVel < 0.0) {
        posX = npc->pos.x;
        groundY = 100.0f;
        posZ = npc->pos.z;
        hitDepth = 1000.0f;
        npc_raycast_down_sides(npc->collisionChannel, &posX, &groundY, &posZ, &hitDepth);

        posX = npc->pos.x;
        posY = npc->pos.y + 13.0;
        posZ = npc->pos.z;
        hitDepth = fabsf(npc->jumpVel) + 16.0;
        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth) && hitDepth <= fabsf(npc->jumpVel) + 13.0) {
            npc->jumpVel = 0.0f;
            npc->pos.y = posY;
            npc->flags &= ~NPC_FLAG_JUMPING;
            fx_walking_dust(2, npc->pos.x, npc->pos.y, npc->pos.z, 0.0f, 0.0f);
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;

            if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
                fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                npc->duration = 25;
                script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
            }
            return;
        }
    }
    npc->pos.y += npc->jumpVel;
    npc->jumpVel -= npc->jumpScale;
}

void N(HoppingAI_LosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_HOP_INIT;
    }
}

API_CALLABLE(N(HoppingAI_Main)) {
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

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_HOP_INIT;
        script->functionTemp[1] = 0;
        npc->duration = 0;
        npc->flags &= ~NPC_FLAG_JUMPING;
        npc->flags &= ~NPC_FLAG_GRAVITY;
        npc->flags |= NPC_FLAG_FLYING;

        enemy->aiFlags |= (AI_FLAG_SKIP_EMOTE_AFTER_FLEE | AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE);
        if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
        }
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_HOP_INIT:
            N(HoppingAI_HopInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_HOP:
            N(HoppingAI_Hop)(script, settings, detect);
            break;
        case AI_STATE_LOITER_INIT:
            N(HoppingAI_LoiterInit)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_LOITER) {
                break;
            }
            // fallthrough
        case AI_STATE_LOITER:
            N(HoppingAI_Loiter)(script, settings, detect);
            break;
        case AI_STATE_CHASE_INIT:
            N(HoppingAI_ChaseInit)(script, settings, detect);
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
