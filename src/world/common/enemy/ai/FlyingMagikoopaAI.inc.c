#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

#include "world/common/enemy/ai/MagikoopaSpellAI.inc.c"

enum FlyingMagikoopaAiStates {
    AI_STATE_FLYMAGI_HOVER_INIT     = 10,
    AI_STATE_FLYMAGI_HOVER          = 11,
    AI_STATE_FLYMAGI_SWOOP_INIT     = 15,
    AI_STATE_FLYMAGI_SWOOP_TURN     = 16,
    AI_STATE_FLYMAGI_SWOOP          = 17,
    AI_STATE_FLYMAGI_CAST_INIT      = 20,
    AI_STATE_FLYMAGI_TARGETING      = 21,
    AI_STATE_FLYMAGI_CASTING        = 22,
    AI_STATE_FLYMAGI_FIRING         = 23,
    AI_STATE_FLYMAGI_POST_CAST      = 24,
    AI_STATE_FLYMAGI_COOLDOWN       = 50,
};

enum FlyingMagikoopaAiVars {
    AI_VAR_FLYMAGI_BOB_PHASE        = 0,
    AI_VAR_FLYMAGI_HOVER_Y          = 1,
    AI_VAR_FLYMAGI_SWOOP_DURATION   = 3,
    AI_VAR_FLYMAGI_SWOOP_START_X    = 4,
    AI_VAR_FLYMAGI_SWOOP_START_Y    = 5,
    AI_VAR_FLYMAGI_SWOOP_START_Z    = 6,
};

enum FlyingMagikoopaAiAnims {
    AI_ANIM_FLYMAGI_CAST        = 8, // preparing the spell, with staff raised
    AI_ANIM_FLYMAGI_FIRE        = 9, // throwing the spell
};

void N(FlyingMagikoopaAI_HoverInit)(Evt* script, MobileAISettings* arg1, EnemyDetectVolume* arg2) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 30;
    script->AI_TEMP_STATE = AI_STATE_FLYMAGI_HOVER;
}

void N(FlyingMagikoopaAI_Hover)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 basePosY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y]);

    npc->pos.y = basePosY + sin_deg(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE]) * 6.0;
    enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] + 10);

    if (N(MagikoopaAI_CanShootSpell)(script, settings->chaseRadius, settings->chaseOffsetDist, detect) == 1) {
        fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        npc->duration = 50; // not functional, overwritten immediately in default CastInit
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_CAST_INIT;
    } else {
        npc->duration--;
        if (npc->duration <= 0) {
            npc->duration = 5;
            script->AI_TEMP_STATE = AI_STATE_FLYMAGI_SWOOP_INIT;
        }
    }
}

enum MagikoopaMoveResult {
    RESULT_SEARCHING       = 0,
    RESULT_OK_BLOCKED      = 1,
    RESULT_OK_CLEAR        = 2,
    RESULT_NONE_FOUND      = 3,
};

void N(FlyingMagikoopaAI_SwoopInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;
    f32 swoopDist;
    f32 returnDist;
    f32 hitDist;
    s32 offsetSteps;
    f32 baseYaw;
    s32 yawOffset;
    s32 result;
    b32 isCCW;

    npc->duration--;
    if (npc->duration > 0) {
        return;
    }

    swoopDist = rand_int(30) + 180.0;

    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        // return toward center if outside detect
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        returnDist = dist2D(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
        if (swoopDist > returnDist) {
            swoopDist = returnDist;
        }
    } else {
        // initially choose a swoop direction toward the player
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatus.pos.x, gPlayerStatus.pos.z);
        if (npc->yaw  < 180.0) {
            baseYaw = (rand_int(10) + 90.0) - 5.0;
        } else {
            baseYaw = (rand_int(10) + 270.0) - 5.0;
        }

        // search for best angle at alternating ±5 degree increments from baseYaw
        result = RESULT_SEARCHING;
        offsetSteps = 0;
        yawOffset = 0;
        isCCW = true;

        while (true) {
            if (isCCW) {
                npc->yaw = baseYaw + yawOffset;
            } else {
                npc->yaw = baseYaw - yawOffset;
            }
            posX = npc->pos.x;
            posY = npc->pos.y;
            posZ = npc->pos.z;
            if (npc_test_move_taller_with_slipping(0, &posX, &posY, &posZ,
                swoopDist, npc->yaw, npc->collisionHeight, npc->collisionDiameter)
            ) {
                hitDist = dist2D(npc->pos.x, npc->pos.z, posX, posZ);
                if (hitDist > 160.0) {
                    if (hitDist < swoopDist) {
                        swoopDist = hitDist;
                    }
                    result = RESULT_OK_BLOCKED;
                }
            } else {
                result = RESULT_OK_CLEAR;
            }

            if (result != RESULT_SEARCHING) {
                break;
            }

            if (isCCW) {
                yawOffset += 5;
                offsetSteps++;
                isCCW = false;
            } else {
                isCCW = true;
            }

            if (offsetSteps > 6) {
                // quit searching after ±30 degrees
                result = RESULT_NONE_FOUND;
                break;
            }
        }
    }

    posX = npc->pos.x;
    posZ = npc->pos.z;
    add_vec2D_polar(&posX, &posZ, swoopDist, npc->yaw);
    npc->moveToPos.x = posX;
    npc->moveToPos.y = npc->pos.y;
    npc->moveToPos.z = posZ;
    enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_X] = AI_PACK_FLT(npc->pos.x);
    enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_Z] = AI_PACK_FLT(npc->pos.z);
    enemy->varTable[AI_VAR_FLYMAGI_SWOOP_DURATION] = rand_int(10) + 35;
    npc->duration = 0;
    npc->moveSpeed = 3.0f;
    npc->jumpVel = 1.4f;
    npc->jumpScale = 0.2f;
    script->AI_TEMP_STATE = AI_STATE_FLYMAGI_SWOOP_TURN;
}

void N(FlyingMagikoopaAI_SwoopTurn)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 basePosY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y]);

    enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] + 10);
    npc->pos.y = basePosY + sin_deg(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE]) * 6.0;

    if (npc->turnAroundYawAdjustment == 0) {
        enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_Y] = AI_PACK_FLT(npc->pos.y);
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_SWOOP;
    }
}

void N(FlyingMagikoopaAI_Swoop)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 limitY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y]);
    f32 startX = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_X]);
    f32 startY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_Y]);
    f32 startZ = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_SWOOP_START_Z]);
    s32 swoopTime = enemy->varTable[AI_VAR_FLYMAGI_SWOOP_DURATION];
    f32 lerpX = update_lerp(EASING_SIN_OUT, startX, npc->moveToPos.x, npc->duration, swoopTime);
    f32 lerpZ = update_lerp(EASING_SIN_OUT, startZ, npc->moveToPos.z, npc->duration, swoopTime);

    npc->pos.x = lerpX;
    npc->pos.z = lerpZ;

    // height dips 25 units below swoop starting Y in a sinusoid over the swoop
    npc->pos.y = startY + 25.0f * sin_deg(180.0f * (1.0f + (f32)npc->duration / swoopTime));

    npc->duration++;
    if (npc->duration == swoopTime - 8) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatus.pos.x, gPlayerStatus.pos.z);
    }
    if (limitY <= npc->pos.y) {
        npc->pos.y = limitY;
        enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = 0;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_HOVER_INIT;
    } else if (npc->duration >= swoopTime) {
        if (enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] >= 180.0) {
            if (enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] < 270.0) {
                enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = clamp_angle(540 - enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE]);
            }
        }
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_HOVER_INIT;
    }
}

void N(FlyingMagikoopaAI_CastInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 40;
    script->AI_TEMP_STATE = AI_STATE_FLYMAGI_TARGETING;
}

void N(FlyingMagikoopaAI_Targeting)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;

    npc->duration--;
    if (npc->duration == 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_COOLDOWN;
        return;
    }

    if ((N(MagikoopaAI_CanShootSpell)(script, settings->chaseRadius, settings->chaseOffsetDist, detect) == 1) && (npc->turnAroundYawAdjustment == 0)) {
        ai_enemy_play_sound(npc, SOUND_SPELL_CAST1, 0);
        npc->curAnim = enemy->animList[AI_ANIM_FLYMAGI_CAST];
        posX = npc->pos.x;
        posY = npc->pos.y + 29.0f;
        posZ = npc->pos.z + 1.0f;
        add_vec2D_polar(&posX, &posZ, 30.0f, 270.0f - npc->renderYaw);
        fx_gather_energy_pink(0, posX, posY, posZ, 0.1f, 13);
        npc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_CASTING;
    }
}

void N(FlyingMagikoopaAI_Casting)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[AI_ANIM_FLYMAGI_FIRE];
        npc->duration = 7;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_FIRING;
    }
}

void N(FlyingMagikoopaAI_Firing)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        if (N(MagikoopaAI_CanShootSpell)(script, settings->chaseRadius, settings->chaseOffsetDist, detect) == 1) {
            ai_enemy_play_sound(npc, SOUND_SPELL_CAST2, 0);
            get_enemy(enemy->npcID + 1)->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_REQUESTED;
            npc->duration = 20;
            script->AI_TEMP_STATE = AI_STATE_FLYMAGI_POST_CAST;
        } else {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
            npc->duration = 15;
            script->AI_TEMP_STATE = AI_STATE_FLYMAGI_COOLDOWN;
        }
    }
}

void N(FlyingMagikoopaAI_PostCast)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 basePosY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y]);

    npc->pos.y = basePosY + sin_deg(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE]) * 6.0;
    enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] + 10);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 3;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_COOLDOWN;
    }
}

void N(FlyingMagikoopaAI_Cooldown)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 basePosY = AI_UNPACK_FLT(enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y]);

    npc->pos.y = basePosY + sin_deg(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE]) * 6.0;
    enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = clamp_angle(enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] + 10);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_HOVER_INIT;
    }
}

API_CALLABLE(N(FlyingMagikoopaAI_Main)) {
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
    detect->halfHeight = 120.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        npc->flags &= ~NPC_FLAG_GRAVITY;
        npc->flags |= NPC_FLAG_FLYING;
        npc->flags |= NPC_FLAG_FLIP_INSTANTLY;
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        enemy->varTable[AI_VAR_FLYMAGI_HOVER_Y] = AI_PACK_FLT(npc->pos.y);
        enemy->varTable[AI_VAR_FLYMAGI_BOB_PHASE] = 0;
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_STATE_FLYMAGI_HOVER_INIT;
    }

    npc->verticalRenderOffset = -5;

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_FLYMAGI_HOVER_INIT:
            N(FlyingMagikoopaAI_HoverInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_FLYMAGI_HOVER:
            N(FlyingMagikoopaAI_Hover)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_SWOOP_INIT:
            N(FlyingMagikoopaAI_SwoopInit)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_FLYMAGI_SWOOP_TURN) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYMAGI_SWOOP_TURN:
            N(FlyingMagikoopaAI_SwoopTurn)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_FLYMAGI_SWOOP) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYMAGI_SWOOP:
            N(FlyingMagikoopaAI_Swoop)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_CAST_INIT:
            N(FlyingMagikoopaAI_CastInit)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_TARGETING:
            N(FlyingMagikoopaAI_Targeting)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_CASTING:
            N(FlyingMagikoopaAI_Casting)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_FIRING:
            N(FlyingMagikoopaAI_Firing)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_FLYMAGI_POST_CAST) {
                break;
            }
            // fallthrough
        case AI_STATE_FLYMAGI_POST_CAST:
            N(FlyingMagikoopaAI_PostCast)(script, settings, detect);
            break;

        case AI_STATE_FLYMAGI_COOLDOWN:
            N(FlyingMagikoopaAI_Cooldown)(script, settings, detect);
            break;
    }
    return ApiStatus_BLOCK;
}
