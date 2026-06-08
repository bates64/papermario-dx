#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#include "world/common/enemy/ai/WanderMeleeAI.inc.c"

// predefined size and shape of area_mim path area
#define PIRANHA_CONFINE_MAX_XZ  (380.0f)
#define PIRANHA_CONFINE_INNER_R (305.0f)
#define PIRANHA_CONFINE_OUTER_R (375.0f)

enum PiranhaPlantAiStates {
    AI_STATE_PIRANHA_PLANT_INIT         = 0,
    AI_STATE_PIRANHA_PLANT_IDLE         = 1,
    AI_STATE_PIRANHA_PLANT_BURROW       = 10,
    AI_STATE_PIRANHA_PLANT_EMERGE       = 11,
    AI_STATE_PIRANHA_PLANT_ATTACK       = 12,
    AI_STATE_PIRANHA_PLANT_COOLDOWN     = 13,
};

enum PiranhaPlantAiVars {
    // AI_VAR_MELEE_STATUS              = 0,
    // AI_VAR_MELEE_PRE_TIME            = 1,
    // AI_VAR_MELEE_SWING_TIME          = 2,
    // AI_VAR_MELEE_POST_TIME           = 3,
    AI_VAR_PIRANHA_PATH_USING_COLLISION = 7,  // move with collision checks when true, otherwise confine to area_mim path areas
    AI_VAR_PIRANHA_BURROW_TIME          = 8,  // how long it will take to burrow underground
    AI_VAR_PIRANHA_INTANGIBLE_TIME      = 9,  // time in the burrow animation when Piranha becomes intangible
    AI_VAR_PIRANHA_EMERGE_TIME          = 10, // how long it will take to emerge from underground
    AI_VAR_PIRANHA_TANGIBLE_TIME        = 11, // time in the emerge animation when Piranha becomes tangible again
    AI_VAR_PIRANHA_END_ATTACK_TIME      = 12, // time into the attack state to begin POST phase
    AI_VAR_PIRANHA_WINDUP_ANIM_TIME     = 13, // length of the WINDUP animation, will play BITE after (or -1 to skip)
    AI_VAR_PIRANHA_BEGIN_ATTACK_TIME    = 14, // time into the attack state to begin SWING phase
    AI_VAR_PIRANHA_COOLDOWN_TIME        = 15, // time after an attack before Piranha can detect the player again
};

enum PiranhaPlantAiAnims {
    AI_ANIM_PIRANHA_PLANT_BURROW    = 8,
    AI_ANIM_PIRANHA_PLANT_EMERGE    = 9,
    AI_ANIM_PIRANHA_PLANT_WINDUP    = 10,
    AI_ANIM_PIRANHA_PLANT_BITE      = 11,
};

void N(PiranhaPlantAI_Init)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (npc->duration > 0) {
        npc->duration--;
    } else {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_IDLE;
        script->functionTemp[1] = 0;
    }
}

void N(PiranhaPlantAI_Idle)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, false)) {
        ai_enemy_play_sound(npc, SOUND_BURROW_DIG, 0);
        fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 10, nullptr);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        npc->curAnim = enemy->animList[AI_ANIM_PIRANHA_PLANT_BURROW];
        npc->duration = enemy->varTable[AI_VAR_PIRANHA_BURROW_TIME];
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_BURROW;
    }
}

void N(PiranhaPlantAI_Burrow)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    b32 usedTruncatedPos = false;
    b32 allowGroundSnap = false;
    b32 higherPathBlocked;
    f32 dist;
    f32 reverseYaw;
    f32 sideYaw;
    f32 yaw;
    f32 ambushDist;
    f32 posRadius;
    s32 hasGroundBelow;
    f32 x, y, z;
    f32 testX, testY, testZ;

    npc->duration--;

    if (npc->duration <= enemy->varTable[AI_VAR_PIRANHA_INTANGIBLE_TIME]) {
        enemy->flags |= ENEMY_INTANGIBLE_FLAGS;
    }

    if (npc->duration <= 0) {
        // choose a direction in front of the player
        if (clamp_angle(gPlayerStatusPtr->spriteFacingAngle) < 180.0f) {
            sideYaw = clamp_angle(gCameras[gCurrentCameraID].curYaw - 90.0f);
        } else {
            sideYaw = clamp_angle(gCameras[gCurrentCameraID].curYaw + 90.0f);
        }
        reverseYaw = clamp_angle(sideYaw + 180.0f);

        // choose a distance to offset from the player
        if (enemy->varTable[AI_VAR_PIRANHA_PATH_USING_COLLISION]) {
            switch (gPlayerStatusPtr->actionState) {
                case ACTION_STATE_IDLE:
                    ambushDist = 38.0f;
                    break;
                case ACTION_STATE_WALK:
                    ambushDist = 75.0f;
                    break;
                default:
                    ambushDist = 90.0f;
                    break;
            }
        } else {
            switch (gPlayerStatusPtr->actionState) {
                case ACTION_STATE_IDLE:
                    ambushDist = 32.0f;
                    break;
                case ACTION_STATE_WALK:
                    ambushDist = 90.0f;
                    break;
                default:
                    ambushDist = 100.0f;
                    break;
            }
        }

        // set position to preliminary ambush location
        npc->pos.x = gPlayerStatusPtr->pos.x;
        npc->pos.z = gPlayerStatusPtr->pos.z;
        add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, reverseYaw);
        npc_move_heading(npc, ambushDist + npc->collisionDiameter, sideYaw);

        // adjust position based on collision or map geometry
        if (enemy->varTable[AI_VAR_PIRANHA_PATH_USING_COLLISION]) {
            if (npc->flags & NPC_FLAG_IGNORE_WORLD_COLLISION) {
                // if there is a collision between the player and the preliminary ambush location,
                // update the ambush location to an unobstructed position along the same direction
                x = gPlayerStatusPtr->pos.x;
                y = gPlayerStatusPtr->pos.y + 18.0;
                z = gPlayerStatusPtr->pos.z;
                if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, ambushDist, sideYaw, npc->collisionHeight, npc->collisionDiameter)) {
                    posRadius = dist2D(gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z, x, z);
                    npc->pos.x = gPlayerStatusPtr->pos.x;
                    npc->pos.z = gPlayerStatusPtr->pos.z;
                    add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, reverseYaw);
                    npc_move_heading(npc, posRadius + npc->collisionDiameter, sideYaw);
                }
            } else {
                // is there a collision between the player and the preliminary ambush location?
                x = gPlayerStatusPtr->pos.x;
                y = gPlayerStatusPtr->pos.y + 18.0;
                z = gPlayerStatusPtr->pos.z;
                if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, ambushDist, sideYaw, npc->collisionHeight, npc->collisionDiameter)) {
                    // perhaps there was a slope, are we obstructed if slightly higher up?
                    x = gPlayerStatusPtr->pos.x;
                    y = gPlayerStatusPtr->pos.y + 45.0;
                    z = gPlayerStatusPtr->pos.z;
                    higherPathBlocked = npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, ambushDist, sideYaw, npc->collisionHeight, npc->collisionDiameter);
                    // check the floor under the preliminary ambush location:
                    // if we move the NPC up a bit, can we snap down to a valid position?
                    testX = npc->pos.x;
                    testY = npc->pos.y + 100.0;
                    testZ = npc->pos.z;
                    dist = 200.0f;
                    hasGroundBelow = npc_raycast_down_sides(npc->collisionChannel, &testX, &testY, &testZ, &dist);
                    if (!higherPathBlocked && hasGroundBelow && dist > 80.0 && dist < 120.0 && npc->pos.y != testY) {
                        // there was a path at the slightly higher position, and there is ground at ±20 units
                        // of the expected position of the ambush location. this indicates a step or slight slope,
                        // which can addressed with a snap-to-ground later. keep the original ambush location.
                        allowGroundSnap = true;
                    } else {
                        // an adjusted ambush location is needed.
                        // there seems to be a wall in the way, so we'll move the location inward to fit.
                        x = gPlayerStatusPtr->pos.x;
                        y = gPlayerStatusPtr->pos.y + 10.0;
                        z = gPlayerStatusPtr->pos.z;
                        npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, ambushDist, sideYaw, npc->collisionHeight, npc->collisionDiameter);
                        posRadius = dist2D(gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z, x, z);
                        npc->pos.x = gPlayerStatusPtr->pos.x;
                        npc->pos.z = gPlayerStatusPtr->pos.z;
                        add_vec2D_polar(&npc->pos.x, &npc->pos.z, npc->collisionDiameter, reverseYaw);
                        npc_move_heading(npc, posRadius + npc->collisionDiameter, sideYaw);
                        usedTruncatedPos = true;
                    }
                }
            }
        } else {
            // confine to annular region of area_mim paths
            npc->pos.x = CLAMP(npc->pos.x, -PIRANHA_CONFINE_MAX_XZ, PIRANHA_CONFINE_MAX_XZ);
            npc->pos.z = CLAMP(npc->pos.z, -PIRANHA_CONFINE_MAX_XZ, PIRANHA_CONFINE_MAX_XZ);

            dist = sqrtf(SQ(npc->pos.x) + SQ(npc->pos.z));
            yaw = atan2(0.0f, 0.0f, npc->pos.x, npc->pos.z);

            if (dist < PIRANHA_CONFINE_INNER_R) {
                npc->pos.x = 0.0f;
                npc->pos.z = 0.0f;
                add_vec2D_polar(&npc->pos.x, &npc->pos.z, PIRANHA_CONFINE_INNER_R, yaw);
            } else if (dist > PIRANHA_CONFINE_OUTER_R) {
                npc->pos.x = 0.0f;
                npc->pos.z = 0.0f;
                add_vec2D_polar(&npc->pos.x, &npc->pos.z, PIRANHA_CONFINE_OUTER_R, yaw);
            }
        }

        // clamp position to detect
        if (is_point_outside_detect_volume(detect, npc->pos.x, npc->pos.z)) {
            switch (detect->shape) {
                case SHAPE_CYLINDER:
                    dist = dist2D(npc->pos.x, npc->pos.z, detect->pointX, detect->pointZ);
                    if (detect->sizeX < dist) {
                        f32 angle = atan2(detect->pointX, detect->pointZ, npc->pos.x, npc->pos.z);
                        npc->pos.x = detect->pointX;
                        npc->pos.z = detect->pointZ;
                        add_vec2D_polar(&npc->pos.x, &npc->pos.z, detect->sizeX, angle);
                    }
                    break;
                case SHAPE_RECT:
                    npc->pos.x = CLAMP(npc->pos.x,
                        detect->pointX - detect->sizeX,
                        detect->pointX + detect->sizeX);

                    npc->pos.z = CLAMP(npc->pos.z,
                        detect->pointZ - detect->sizeZ,
                        detect->pointZ + detect->sizeZ);
                    break;
            }
        }

        // snap to ground
        if (!usedTruncatedPos && (!(npc->flags & NPC_FLAG_FLYING) || allowGroundSnap)) {
            x = npc->pos.x;
            y = npc->pos.y + 150.0;
            z = npc->pos.z;
            dist = 400.0f;
            if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &dist)) {
                npc->pos.y = y;
            }
        }

        // face player and emerge
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        ai_enemy_play_sound(npc, SOUND_BURROW_SURFACE, 0);
        npc->curAnim = enemy->animList[AI_ANIM_PIRANHA_PLANT_EMERGE];
        npc->duration = enemy->varTable[AI_VAR_PIRANHA_EMERGE_TIME];
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_EMERGE;
    }
}

void N(PiranhaPlantAI_Emerge)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (enemy->varTable[AI_VAR_PIRANHA_TANGIBLE_TIME] >= npc->duration) {
        enemy->flags &= ~ENEMY_INTANGIBLE_FLAGS;
    }
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[AI_ANIM_PIRANHA_PLANT_WINDUP];
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_ATTACK;
    }
}

void N(PiranhaPlantAI_Attack)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration++;
    if (npc->duration == enemy->varTable[AI_VAR_PIRANHA_WINDUP_ANIM_TIME]) {
        npc->curAnim = enemy->animList[AI_ANIM_PIRANHA_PLANT_BITE];
    }
    if (npc->duration == enemy->varTable[AI_VAR_PIRANHA_BEGIN_ATTACK_TIME]) {
        // activate the attack hitbox
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_SWING;
    }
    if (npc->duration >= enemy->varTable[AI_VAR_PIRANHA_END_ATTACK_TIME]) {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_POST;
        npc->duration = 8;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        fx_emote(EMOTE_FRUSTRATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 10, nullptr);
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_COOLDOWN;
    }
}

void N(PiranhaPlantAI_Cooldown)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->duration = enemy->varTable[AI_VAR_PIRANHA_COOLDOWN_TIME];
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
    }
}

void N(PiranhaPlantAI_LosePlayer)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        if (!basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, false)) {
            fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1, 2, -20, 15, nullptr);
        }
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_INIT;
    }
}

API_CALLABLE(N(PiranhaPlantAI_Main)) {
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
    detect->halfHeight = 200.0f;
    detect->detectFlags = 0;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_PIRANHA_PLANT_INIT;
        npc->duration = 0;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];

        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            script->AI_TEMP_STATE = AI_STATE_SUSPEND;
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_PIRANHA_PLANT_INIT;
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_PIRANHA_PLANT_INIT:
            N(PiranhaPlantAI_Init)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_IDLE) {
                break;
            }
            // fallthrough
        case AI_STATE_PIRANHA_PLANT_IDLE:
            N(PiranhaPlantAI_Idle)(script, settings, detect);
            break;
        case AI_STATE_PIRANHA_PLANT_BURROW:
            N(PiranhaPlantAI_Burrow)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_EMERGE) {
                break;
            }
            // fallthrough
        case AI_STATE_PIRANHA_PLANT_EMERGE:
            N(PiranhaPlantAI_Emerge)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_ATTACK) {
                break;
            }
            // fallthrough
        case AI_STATE_PIRANHA_PLANT_ATTACK:
            N(PiranhaPlantAI_Attack)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_PIRANHA_PLANT_COOLDOWN) {
                break;
            }
            // fallthrough
        case AI_STATE_PIRANHA_PLANT_COOLDOWN:
            N(PiranhaPlantAI_Cooldown)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }
            // fallthrough
        case AI_STATE_LOSE_PLAYER:
            N(PiranhaPlantAI_LosePlayer)(script, settings, detect);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}

