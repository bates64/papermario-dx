#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

// Used in:
// - kmr_02 Toad
// - kmr_07 GoombaBros
// - kmr_11 GoombaBros/King
// - sbk_30 (unused)
// - trd_01 Bobomb <-- only real use case!
// - nok_01 (unused)
// - omo_02 (unused)

enum GuardAiStates {
    AI_STATE_GUARD_IDLE_INIT            = 0,
    AI_STATE_GUARD_IDLE                 = 1,
    AI_STATE_GUARD_RETURN_HOME_INIT     = 15,
    AI_STATE_GUARD_RETURN_HOME          = 16
};

enum GuardAiVars {
    AI_VAR_GUARD_ORIGINAL_YAW           = 0,
};

void N(GuardAI_IdleInit)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_GUARD_IDLE;

    if (enemy->flags & ENEMY_FLAG_SKIP_BATTLE) {
        npc->yaw = enemy->varTable[AI_VAR_GUARD_ORIGINAL_YAW];
    }

    if (enemy->territory->wander.moveSpeedOverride <= 0) {
        npc->moveSpeed = settings->chaseSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
}

void N(GuardAI_Idle)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (settings->playerSearchInterval >= 0 && basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, false)) {
        fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);

        if (!(enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER)) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        } else {
            script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
        }
    }
}

void N(GuardAI_AlertInit)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->jumpVel = 10.0f;
    npc->jumpScale = 2.0f;
    npc->moveToPos.y = npc->pos.y;
    npc->flags |= NPC_FLAG_JUMPING;
    script->AI_TEMP_STATE = AI_STATE_ALERT;
}

void N(GuardAI_Alert)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->pos.y += npc->jumpVel;
    npc->jumpVel -= npc->jumpScale;

    if (!(npc->pos.y > npc->moveToPos.y)) {
        npc->pos.y = npc->moveToPos.y;
        npc->jumpVel = 0.0f;
        npc->flags &= ~NPC_FLAG_JUMPING;
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void N(GuardAI_ChaseInit)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 angle;
    f32 deltaAngle;

    npc->duration = (settings->chaseUpdateInterval / 2) + rand_int(settings->chaseUpdateInterval / 2 + 1);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
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

    script->AI_TEMP_STATE = AI_STATE_CHASE;
}

void N(GuardAI_Chase)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 25;
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
    } else {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        npc_surface_spawn_fx(npc, SURFACE_INTERACT_RUN);

        if (npc->duration > 0) {
            npc->duration--;
        }
        if (npc->duration <= 0) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }
    }
}

void N(GuardAI_LosePlayer)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    if (npc->duration > 0) {
        npc->duration--;
    }
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_GUARD_RETURN_HOME_INIT;
    }
}

void N(GuardAI_ReturnHomeInit)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = settings->chaseSpeed * 0.3;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
    script->functionTemp[1] = 0;
    script->AI_TEMP_STATE = AI_STATE_GUARD_RETURN_HOME;
}

void N(GuardAI_ReturnHome)(Evt* script, GuardAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (settings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = settings->playerSearchInterval;
            if (basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, false)) {
                fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                    script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
                } else {
                    script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
                }
                return;
            }
        }
        script->functionTemp[1]--;
    }

    if (dist2D(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z) < npc->moveSpeed) {
        npc->pos.x = enemy->territory->wander.centerPos.x;
        npc->pos.z = enemy->territory->wander.centerPos.z;
        // NOTE: initial yaw is stored HERE
        npc->yaw = enemy->territory->wander.wanderSize.x;
        script->AI_TEMP_STATE = AI_STATE_GUARD_IDLE_INIT;
    }

    if (npc->turnAroundYawAdjustment == 0) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }
}

API_CALLABLE(N(GuardAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    GuardAISettings* settings = (GuardAISettings*)evt_get_variable(script, *args++);
    EnemyDetectVolume detectVolume;
    EnemyDetectVolume* detect = &detectVolume;

    detect->skipPlayerDetectChance = 0;
    detect->shape = enemy->territory->wander.detectShape;
    detect->pointX = enemy->territory->wander.detectPos.x;
    detect->pointZ = enemy->territory->wander.detectPos.z;
    detect->sizeX = enemy->territory->wander.detectSize.x;
    detect->sizeZ = enemy->territory->wander.detectSize.z;
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_GUARD_IDLE_INIT;
        npc->duration = 0;
        enemy->varTable[AI_VAR_GUARD_ORIGINAL_YAW] = npc->yaw;
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
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_GUARD_RETURN_HOME_INIT;
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_GUARD_IDLE_INIT:
            N(GuardAI_IdleInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_GUARD_IDLE:
            N(GuardAI_Idle)(script, settings, detect);
            break;

        case AI_STATE_ALERT_INIT:
            N(GuardAI_AlertInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_ALERT:
            N(GuardAI_Alert)(script, settings, detect);
            break;

        case AI_STATE_CHASE_INIT:
            N(GuardAI_ChaseInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            N(GuardAI_Chase)(script, settings, detect);
            break;

        case AI_STATE_LOSE_PLAYER:
            N(GuardAI_LosePlayer)(script, settings, detect);
            break;

        case AI_STATE_GUARD_RETURN_HOME_INIT:
            N(GuardAI_ReturnHomeInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_GUARD_RETURN_HOME:
            N(GuardAI_ReturnHome)(script, settings, detect);
            break;

        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
