#pragma once

#include "common.h"
#include "npc.h"
#include "world/ai.h"

#include "sprite/npc/MontyMole.h"

#include "world/common/enemy/ai/RangedAttack.inc.c"

enum MontyMoleAiStates {
    AI_STATE_MOLE_INIT          = 0,    // choose random heading and duration for next state
    AI_STATE_MOLE_WANDER        = 1,    // wander around 'underground'
    AI_STATE_MOLE_PRE_SURFACE   = 12,   // delay before emerging from underground
    AI_STATE_MOLE_SURFACE       = 13,   // emerge from underground
    AI_STATE_MOLE_DRAW_ROCK     = 14,   // pull out a rock, can either attack or cancel
    AI_STATE_MOLE_THROW_ROCK    = 15,   // throw the rock
    AI_STATE_MOLE_UNUSED        = 16,
    AI_STATE_MOLE_PRE_BURROW    = 20,   // delay before burrowing back underground
    AI_STATE_MOLE_BURROW        = 21,   // burrow underground
};

s32 N(MontyMoleAI_CanAttack)(Evt* script, EnemyDetectVolume* detect, f32 radius, f32 arg3) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Camera* cam = &gCameras[gCurrentCamID];
    f32 angle;
    s32 retVal;

    retVal = basic_ai_check_player_dist(detect, enemy, radius * 1.1, arg3, false);

    // check npc facing angle for sight of player
    if (clamp_angle(get_clamped_angle_diff(cam->curYaw, npc->yaw)) < 180.0) {
        angle = 90.0f;
    } else {
        angle = 270.0f;
    }
    if (fabsf(get_clamped_angle_diff(angle, atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z))) > 60.0) {
        retVal = false;
    }
    // check for overlap with player
    if (get_xz_dist_to_player(npc->pos.x, npc->pos.z) < gPlayerStatusPtr->colliderDiameter + npc->collisionDiameter) {
        retVal = false;
    }
    // check player elevation difference
    if (fabsf(npc->pos.y - gPlayerStatusPtr->pos.y) >= 40.0f) {
        retVal = false;
    }
    // check for bow hiding
    if (gPartnerStatus.actingPartner == PARTNER_BOW) {
        retVal = false;
    }
    return retVal;
}

void N(MontyMoleAI_Init)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (settings->moveTime / 2) + rand_int((settings->moveTime / 2) + 1);
    npc->yaw = clamp_angle((npc->yaw + rand_int(60)) - 30.0f);
    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = settings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }
    enemy->flags |= ENEMY_INTANGIBLE_FLAGS;
    npc->flags |= NPC_FLAG_INVISIBLE;
    script->functionTemp[1] = 0;
    script->AI_TEMP_STATE = AI_STATE_MOLE_WANDER;
}

void N(MontyMoleAI_Wander)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;
    f32 hitDepth;

    if (is_point_outside_wander_territory(&enemy->territory->wander, npc->pos.x, npc->pos.z)) {
        npc->yaw = atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z);
    }
    posX = npc->pos.x;
    posY = npc->pos.y + 1.0f;
    posZ = npc->pos.z;
    add_vec2D_polar(&posX, &posZ, npc->moveSpeed + npc->collisionDiameter, npc->yaw);
    hitDepth = 1000.0f;
    if (npc_raycast_down_sides(0, &posX, &posY, &posZ, &hitDepth) && (hitDepth < 5.0f)) {
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    }
    if (npc->flags & NPC_FLAG_COLLDING_FORWARD_WITH_WORLD) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
    if (settings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = settings->playerSearchInterval;
            if (N(MontyMoleAI_CanAttack)(script, detect, settings->alertRadius, settings->alertOffsetDist)) {
                npc->duration = 0;
                script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_SURFACE;
                return;
            }
        }
        script->functionTemp[1]--;
    }
    if (!(npc->flags & (NPC_FLAG_FLYING | NPC_FLAG_GROUNDED))) {
        npc->homePos.x = npc->pos.x;
        npc->homePos.z = npc->pos.z;
    }
    npc->duration--;
    if (npc->duration == 0) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
}

void N(MontyMoleAI_PreSurface)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->flags &= ~NPC_FLAG_INVISIBLE;
    ai_enemy_play_sound(npc, SOUND_BURROW_SURFACE, 0);
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->curAnim = ANIM_MontyMole_Anim10; // emerge from ground
    npc->duration = 10;
    script->AI_TEMP_STATE = AI_STATE_MOLE_SURFACE;
}

void N(MontyMoleAI_Surface)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 2) {
        enemy->flags &= ~ENEMY_INTANGIBLE_FLAGS;
    }
    if (npc->duration <= 0) {
        npc->curAnim = ANIM_MontyMole_Anim18; // get and throw rock
        npc->duration = 10;
        script->AI_TEMP_STATE = AI_STATE_MOLE_DRAW_ROCK;
    }
}

void N(MontyMoleAI_DrawRock)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if ((npc->duration) <= 0) {
        if (!N(MontyMoleAI_CanAttack)(script, detect, settings->alertRadius * 1.1, settings->alertOffsetDist)) {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
            npc->curAnim = ANIM_MontyMole_Anim01; // cancel attack
            npc->duration = 30;
            script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_BURROW;
        } else {
            npc->curAnim = ANIM_MontyMole_Anim1B; // throw rock
            npc->duration = 15;
            script->AI_TEMP_STATE = AI_STATE_MOLE_THROW_ROCK;
        }
    }
}

void N(MontyMoleAI_ThrowRock)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* moleEnemy;
    Enemy* rockEnemy;
    Npc* moleNpc;

    moleEnemy = script->owner1.enemy;
    moleNpc = get_npc_unsafe(moleEnemy->npcID);
    moleNpc->duration--;
    if (moleNpc->duration == 13) {
        rockEnemy = get_enemy(moleEnemy->npcID + 1);
        rockEnemy->varTable[4] = moleEnemy->npcID;
        rockEnemy->varTable[0] = 1;
    }
    if (moleNpc->duration < 8) {
        if (dist2D(moleNpc->pos.x, moleNpc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) > 100.0) {
            moleNpc->curAnim = ANIM_MontyMole_Anim15; // clap
        }
    }
    if (moleNpc->duration <= 0) {
        if (moleNpc->curAnim != ANIM_MontyMole_Anim15) {
            moleNpc->curAnim = ANIM_MontyMole_Anim01;
        }
        moleNpc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_MOLE_PRE_BURROW;
    }
}

void N(MontyMoleAI_PreBurrow)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        ai_enemy_play_sound(npc, SOUND_BURROW_DIG, 0);
        npc->duration = 11;
        npc->curAnim = ANIM_MontyMole_Anim11; // retreat into ground
        script->AI_TEMP_STATE = AI_STATE_MOLE_BURROW;
    }
}

void N(MontyMoleAI_Burrow)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 3) {
        enemy->flags |= ENEMY_INTANGIBLE_FLAGS;
    }
    if (npc->duration <= 0) {
        npc->flags |= NPC_FLAG_INVISIBLE;
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
    }
}

API_CALLABLE(N(MontyMoleAI_Main)) {
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
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_MOLE_INIT;
        npc->duration = 0;
        npc->flags &= ~NPC_FLAG_JUMPING;
        enemy->aiFlags |= (AI_FLAG_SKIP_EMOTE_AFTER_FLEE | AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE);
    }

    if (enemy->aiFlags & AI_FLAG_SUSPEND) {
        if (enemy->aiSuspendTime != 0) {
            return ApiStatus_BLOCK;
        }
        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MOLE_INIT:
            N(MontyMoleAI_Init)(script, settings, detect);
            // fallthrough
        case AI_STATE_MOLE_WANDER:
            N(MontyMoleAI_Wander)(script, settings, detect);
            break;
        case AI_STATE_MOLE_PRE_SURFACE:
            N(MontyMoleAI_PreSurface)(script, settings, detect);
            // fallthrough
        case AI_STATE_MOLE_SURFACE:
            N(MontyMoleAI_Surface)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_DRAW_ROCK) {
                break;
            } // else fallthrough
        case AI_STATE_MOLE_DRAW_ROCK:
            N(MontyMoleAI_DrawRock)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_THROW_ROCK) {
                break;
            } // else fallthrough
        case AI_STATE_MOLE_THROW_ROCK:
            N(MontyMoleAI_ThrowRock)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_MOLE_UNUSED) {
                break;
            } // else fallthrough
        case AI_STATE_MOLE_PRE_BURROW:
            N(MontyMoleAI_PreBurrow)(script, settings, detect);
            break;
        case AI_STATE_MOLE_BURROW:
            N(MontyMoleAI_Burrow)(script, settings, detect);
            break;
    }
    return ApiStatus_BLOCK;
}
