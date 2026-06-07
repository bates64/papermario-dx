#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"
#include "sprite.h"

// required include args
#ifndef AI_SENTINEL_FIRST_NPC
#error  AI_SENTINEL_FIRST_NPC must be defined for SentinelAI.inc.c
#define AI_SENTINEL_FIRST_NPC 0
#endif
#ifndef AI_SENTINEL_LAST_NPC
#error  AI_SENTINEL_LAST_NPC must be defined for SentinelAI.inc.c
#define AI_SENTINEL_LAST_NPC 0
#endif

#include "world/common/enemy/ai/FlyingAI.inc.c"

enum SentinelAiStates {
    AI_STATE_SENTINEL_WANDER_INIT       = 0,
    AI_STATE_SENTINEL_WANDER            = 1,
    AI_STATE_SENTINEL_LOITER_INIT       = 2,
    AI_STATE_SENTINEL_LOITER            = 3,
    AI_STATE_SENTINEL_CHASE_INIT        = 12,
    AI_STATE_SENTINEL_CHASE             = 13,
    AI_STATE_SENTINEL_DESCEND_INIT      = 14,
    AI_STATE_SENTINEL_DESCEND           = 15,
    AI_STATE_SENTINEL_LOSE_PLAYER_INIT  = 16,
    AI_STATE_SENTINEL_LOSE_PLAYER       = 17,
    AI_STATE_SENTINEL_POST_LOSE_PLAYER  = 18,
    AI_STATE_SENTINEL_GRAB_PLAYER       = 20,
    AI_STATE_SENTINEL_RETURN_HOME_INIT  = 30,
    AI_STATE_SENTINEL_RETURN_HOME       = 31,
    AI_STATE_SENTINEL_CAUGHT_PLAYER     = 100,
};

// extension of FlyingAiFlags
enum SentinelAiFlags {
    AI_SENTINEL_FLAG_GRABBING       = 0x0100, // use to ensure only one sentinel can 'attack' at a time
    AI_SENTINEL_FLAG_PLAYING_SOUND  = 0x1000, // use to force looping sound to stop
};

enum SentinelAiAnims {
    AI_ANIM_SENTINEL_CHASE          = 8,
    AI_ANIM_SENTINEL_LOST           = 9,
};

#define SENTINEL_AI_DESCEND_RATE    (1.8f)

void N(SentinelAI_ChaseInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 deltaAngle;
    f32 angle;

    npc->duration--;
    if (npc->duration <= 0) {
        npc->flags &= ~NPC_FLAG_FLIP_INSTANTLY;
        npc->duration = settings->chaseUpdateInterval / 2 + rand_int(settings->chaseUpdateInterval / 2 + 1);
        npc->curAnim = enemy->animList[AI_ANIM_SENTINEL_CHASE];
        npc->moveSpeed = settings->chaseSpeed;

        angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        deltaAngle = get_clamped_angle_diff(npc->yaw, angle);

        // cap the turn rate
        if (settings->chaseTurnRate < fabsf(deltaAngle)) {
            if (deltaAngle < 0.0f) {
                angle = npc->yaw - settings->chaseTurnRate;
            } else {
                angle = npc->yaw + settings->chaseTurnRate;
            }
        }
        npc->yaw = clamp_angle(angle);

        script->AI_TEMP_STATE = AI_STATE_SENTINEL_CHASE;
    }
}

void N(SentinelAI_Chase)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        if (dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x,
                   gPlayerStatusPtr->pos.z) <= (npc->moveSpeed * 2.5)) {
            npc->duration = 0;
            script->AI_TEMP_STATE = AI_STATE_SENTINEL_DESCEND_INIT;
        } else {
            npc->duration--;
            if (npc->duration <= 0) {
                npc->flags |= NPC_FLAG_FLIP_INSTANTLY;
                script->AI_TEMP_STATE = AI_STATE_SENTINEL_CHASE_INIT;
            }
        }
    } else {
        script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOSE_PLAYER_INIT;
    }
}

void N(SentinelAI_DescendInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 i;

    for (i = AI_SENTINEL_FIRST_NPC; i <= AI_SENTINEL_LAST_NPC; i++) {
        if (i != npc->npcID && (get_enemy(i)->varTable[AI_VAR_FLYING_FLAGS] & AI_SENTINEL_FLAG_GRABBING)) {
            return;
        }
    }

    enemy->varTable[AI_VAR_FLYING_FLAGS] |= AI_SENTINEL_FLAG_GRABBING;
    npc->pos.x = gPlayerStatusPtr->pos.x;
    npc->pos.z = gPlayerStatusPtr->pos.z;

    enemy->varTable[AI_VAR_FLYING_FLAGS] |= AI_SENTINEL_FLAG_PLAYING_SOUND;
    sfx_play_sound_at_position(SOUND_LOOP_SENTINEL_ALARM, SOUND_SPACE_FULL, npc->pos.x, npc->pos.y, npc->pos.z);

    npc->duration = 0;
    script->AI_TEMP_STATE = AI_STATE_SENTINEL_DESCEND;
}

void N(SentinelAI_Descend)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ, hitDepth;
    s32 color;

    sfx_adjust_env_sound_pos(SOUND_LOOP_SENTINEL_ALARM, SOUND_SPACE_FULL, npc->pos.x, npc->pos.y, npc->pos.z);

    if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        enemy->varTable[AI_VAR_FLYING_FLAGS] &= ~AI_SENTINEL_FLAG_GRABBING;
        npc->rot.y = 0.0f;
        npc->flags &= ~NPC_FLAG_FLIP_INSTANTLY;
        script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOSE_PLAYER_INIT;
    } else {
        npc->pos.x = gPlayerStatusPtr->pos.x;
        npc->pos.z = gPlayerStatusPtr->pos.z + 2.0f;
        npc->rot.y += 25.0f;
        if (npc->rot.y > 360.0) {
            npc->rot.y -= 360.0;
        }
        color = 255.0f - (cosine((s32)npc->rot.y % 180) * 56.0f);
        set_npc_imgfx_all(npc->spriteInstanceID, IMGFX_SET_COLOR, color, color, color, 255, 0);

        posX = gPlayerStatusPtr->pos.x;
        posY = gPlayerStatusPtr->pos.y;
        posZ = gPlayerStatusPtr->pos.z;
        hitDepth = 1000.0f;
        npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
        if (fabsf(npc->pos.y - posY) > 24.0) {
            npc->pos.y -= SENTINEL_AI_DESCEND_RATE;
        } else {
            npc->rot.y = 0.0f;
            npc->flags &= ~NPC_FLAG_FLIP_INSTANTLY;
            if (gPartnerStatus.actingPartner != PARTNER_BOW) {
                disable_player_input();
                partner_disable_input();
                npc->duration = 0;
                script->AI_TEMP_STATE = AI_STATE_SENTINEL_GRAB_PLAYER;
            } else {
                script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOSE_PLAYER_INIT;
            }
        }
    }
}

void N(SentinelAI_LosePlayerInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    enemy->varTable[AI_VAR_FLYING_FLAGS] &= ~AI_SENTINEL_FLAG_GRABBING;
    set_npc_imgfx_all(npc->spriteInstanceID, IMGFX_CLEAR, 0, 0, 0, 0, 0);
    if (enemy->varTable[AI_VAR_FLYING_FLAGS] & AI_SENTINEL_FLAG_PLAYING_SOUND) {
        sfx_stop_sound(SOUND_LOOP_SENTINEL_ALARM);
        enemy->varTable[AI_VAR_FLYING_FLAGS] &= ~AI_SENTINEL_FLAG_PLAYING_SOUND;
    }
    npc->curAnim = enemy->animList[AI_ANIM_SENTINEL_LOST];
    npc->duration = 20;
    script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOSE_PLAYER;
}

void N(SentinelAI_LosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ, hitDepth;
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);

    npc->pos.y += 2.5;
    posX = npc->pos.x;
    posY = npc->pos.y;
    posZ = npc->pos.z;
    hitDepth = 1000.0f;
    npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth);
    if (!(npc->pos.y < posY + hoverHeight)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        npc->pos.y = posY + hoverHeight;
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 10, nullptr);
        npc->duration = 10;
        script->AI_TEMP_STATE = AI_STATE_SENTINEL_POST_LOSE_PLAYER;
    }
}

void N(SentinelAI_PostLosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_SENTINEL_RETURN_HOME_INIT;
    }
}

void N(SentinelAI_GrabPlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration++;
    if (npc->duration >= 3) {
        if (gPartnerStatus.actingPartner != PARTNER_BOW) {
            npc->duration = 0;
            script->AI_TEMP_STATE = AI_STATE_SENTINEL_CAUGHT_PLAYER;
        } else {
            enable_player_input();
            partner_enable_input();
            script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOSE_PLAYER_INIT;
        }
    }
}

void N(SentinelAI_ReturnHomeInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    enemy->varTable[AI_VAR_FLYING_FLAGS] &= ~AI_SENTINEL_FLAG_GRABBING;
    npc->flags &= ~NPC_FLAG_FLIP_INSTANTLY;
    npc->moveSpeed = 2.0 * settings->moveSpeed;
    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = 0;
    enemy->varTable[AI_VAR_FLYING_PREV_Y] = AI_PACK_FLT(npc->pos.y);
    script->functionTemp[1] = 30;
}

void N(SentinelAI_ReturnHome)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX = npc->pos.x;
    f32 posY = npc->pos.y;
    f32 posZ = npc->pos.z;
    f32 hitDepth = 1000.0f;
    f32 hoverHeight = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_HEIGHT]);
    f32 hoverBase = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_HOVER_BASE]);
    f32 bobAmplitude = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYING_BOB_AMPLITUDE]);
    f32 bobAmount = sin_deg(enemy->varTable[AI_VAR_FLYING_BOB_PHASE]);
    f32 dist;

    if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth)) {
        npc->pos.y = posY + hoverHeight + (bobAmount * bobAmplitude);
    } else {
        npc->pos.y = hoverBase + hoverHeight + (bobAmount * bobAmplitude);
    }

    enemy->varTable[AI_VAR_FLYING_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYING_BOB_PHASE] + 12);
    if (script->functionTemp[1] <= 0) {
        script->functionTemp[1] = settings->playerSearchInterval;
        if (basic_ai_check_player_dist(detect, enemy, settings->alertRadius * 0.5, settings->alertOffsetDist * 0.5, 0)) {
            fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
            ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
            npc->moveToPos.y = npc->pos.y;
            script->AI_TEMP_STATE = AI_STATE_SENTINEL_CHASE_INIT;
            return;
        }
    }

    script->functionTemp[1]--;
    if (npc->turnAroundYawAdjustment == 0) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        dist = dist2D(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        if (dist <= (2.0f * npc->moveSpeed)) {
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;
            script->AI_TEMP_STATE = AI_STATE_SENTINEL_LOITER_INIT;
        }
    }
}

API_CALLABLE(N(SentinelAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 125.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_SENTINEL_WANDER_INIT;
        N(FlyingAI_Init)(npc, enemy, script, settings);
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_SENTINEL_WANDER_INIT:
            N(FlyingAI_WanderInit)(script, settings, detect);
            set_npc_imgfx_all(npc->spriteInstanceID, IMGFX_CLEAR, 0, 0, 0, 0, 0);
            // fallthrough
        case AI_STATE_SENTINEL_WANDER:
            N(FlyingAI_Wander)(script, settings, detect);
            if (script->AI_TEMP_STATE == AI_STATE_SENTINEL_CHASE_INIT) {
                npc->duration = 6;
            }
            break;
        case AI_STATE_SENTINEL_LOITER_INIT:
            N(FlyingAI_LoiterInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_SENTINEL_LOITER:
            N(FlyingAI_Loiter)(script, settings, detect);
            if (script->AI_TEMP_STATE == AI_STATE_SENTINEL_CHASE_INIT) {
                npc->duration = 6;
            }
            break;
        case AI_STATE_SENTINEL_CHASE_INIT:
            N(SentinelAI_ChaseInit)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_SENTINEL_CHASE) {
                break;
            }
            // fallthrough
        case AI_STATE_SENTINEL_CHASE:
            N(SentinelAI_Chase)(script, settings, detect);
            break;
        case AI_STATE_SENTINEL_DESCEND_INIT:
            N(SentinelAI_DescendInit)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_SENTINEL_DESCEND) {
                break;
            }
            // fallthrough
        case AI_STATE_SENTINEL_DESCEND:
            N(SentinelAI_Descend)(script, settings, detect);
            break;
        case AI_STATE_SENTINEL_LOSE_PLAYER_INIT:
            N(SentinelAI_LosePlayerInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_SENTINEL_LOSE_PLAYER:
            N(SentinelAI_LosePlayer)(script, settings, detect);
            break;
        case AI_STATE_SENTINEL_POST_LOSE_PLAYER:
            N(SentinelAI_PostLosePlayer)(script, settings, detect);
            break;
        case AI_STATE_SENTINEL_GRAB_PLAYER:
            N(SentinelAI_GrabPlayer)(script, settings, detect);
            break;
        case AI_STATE_SENTINEL_RETURN_HOME_INIT:
            N(SentinelAI_ReturnHomeInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_SENTINEL_RETURN_HOME:
            N(SentinelAI_ReturnHome)(script, settings, detect);
            break;
    }

    if (script->AI_TEMP_STATE == AI_STATE_SENTINEL_CAUGHT_PLAYER) {
        return ApiStatus_DONE2; // when player is caught, relinquish control to the AI evt script
    } else {
        return ApiStatus_BLOCK;
    }
}
