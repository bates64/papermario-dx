#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#define MISSILE_INTANGIBLE_FLAGS \
    ( ENEMY_FLAG_CANT_INTERACT \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    | ENEMY_FLAG_IGNORE_HAMMER \
    | ENEMY_FLAG_IGNORE_PARTNER \
    )

enum RangedAttackerAiStates {
    AI_STATE_RANGED_ATTACK_FIRE     = 30,
    AI_STATE_RANGED_ATTACK_CANCEL   = 31, // unused
    AI_STATE_RANGED_ATTACK_AWAIT    = 32, // unused and buggy (only respects first ammo)
    AI_STATE_RANGED_ATTACK_COOLDOWN = 33, // delay after losing target or finishing an attack
};

enum RangedAttackerAiVars {
    AI_VAR_RANGED_MIN_DIST          = 0,
    AI_VAR_RANGED_PRE_TIME          = 1,
    AI_VAR_RANGED_POST_TIME         = 2,
    AI_VAR_RANGED_AMMO_COUNT        = 3,
};

enum RangedAttackerAiAnims {
    AI_ANIM_RANGED_DRAW             = 8,
    AI_ANIM_RANGED_FIRE             = 9,
};

enum MissileAiStates {
    AI_STATE_MISSILE_INIT            = 0,
    AI_STATE_MISSILE_READY           = 1,
    AI_STATE_MISSILE_FIRED           = 2,
};

enum MissileAiVars {
    AI_VAR_MISSILE_STATUS           = 0, // see: MissileStatus
    AI_VAR_MISSILE_FLAGS            = 1, // see: MissileAiFlags
    AI_VAR_MISSILE_SPAWN_Y          = 2, // additional y-offset from parent npc when spawned
    AI_VAR_MISSILE_SPAWN_R          = 3, // additional radial offset from parent npc when spawned
    AI_VAR_MISSILE_OWNER            = 4, // npcID which fired this missile
};

enum MissileAiFlags {
    AI_MISSILE_FLAG_SPINNING        = 0x1,
    AI_MISSILE_FLAG_CENTERED        = 0x2,
};

enum MissileStatus {
    MISSILE_STATUS_IDLE             = 0, // missile is unoccupied and ready to be fired
    MISSILE_STATUS_REQUESTED        = 1, // launch requested by attacker
    MISSILE_STATUS_ACTIVE           = 2, // missile is moving through the air
    MISSILE_STATUS_REFLECTING       = 3, // bounced by the player
    MISSILE_STATUS_DESTROYED        = 4, // destroyed by player
    MISSILE_STATUS_DONE             = 5,
};

enum MissileReflectAiStates {
    AI_STATE_MISSILE_REFLECT_INIT   = 0,
    AI_STATE_MISSILE_REFLECT_ACTIVE = 1,
};

s32 N(RangedAttack_GetUsableMissileID)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    Camera* camera = &gCameras[gCurrentCamID];
    Npc* npc = get_npc_unsafe(enemy->npcID);
    MobileAISettings* settings = (MobileAISettings*)evt_get_variable(script, *args++);
    f32 facingAngle;
    f32 angleToPlayer;
    f32 deltaAngle;
    s32 i;

    if (ai_check_player_dist(enemy, 0, settings->chaseRadius, settings->chaseOffsetDist)) {
        if (clamp_angle(get_clamped_angle_diff(camera->curYaw, npc->yaw)) < 180.0) {
            facingAngle = 90.0f;
        } else {
            facingAngle = 270.0f;
        }

        // is the player to the left or right?
        angleToPlayer = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        deltaAngle = get_clamped_angle_diff(facingAngle, angleToPlayer);
        if (fabsf(deltaAngle) > 75.0) {
           return -1;
        }

        // is player close enough vertically?
        if (2.0 * npc->collisionHeight <= fabsf(npc->pos.y - gPlayerStatusPtr->pos.y)) {
            return -1;
        }

        // are partner abilities preventing the attack?
        if (gPartnerStatus.actingPartner == PARTNER_BOW) {
            return -1;
        }
        if (gPartnerStatus.actingPartner == PARTNER_SUSHIE) {
            return -1;
        }

        // choose the first idle projectile hitbox
        for (i = 0; i < enemy->varTable[AI_VAR_RANGED_AMMO_COUNT]; i++) {
            s32 missileNpcID = enemy->npcID + i + 1;
            Enemy* missile = get_enemy(missileNpcID);

            get_npc_unsafe(missileNpcID);

            if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE) {
                return missileNpcID;
            }
        }
    }
    return -1;
}

void N(RangedAttack_TryTakeShot)(Evt* script, f32 radius, f32 offset, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (!basic_ai_check_player_dist(detect, enemy, radius, offset, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 20;
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_COOLDOWN;
    } else {
        s32 npcID = N(RangedAttack_GetUsableMissileID)(script);

        if (npcID >= 0
            && get_enemy(npcID)->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE
            && npc->turnAroundYawAdjustment == 0
        ) {
            npc->curAnim = enemy->animList[AI_ANIM_RANGED_DRAW];
            npc->duration = enemy->varTable[AI_VAR_RANGED_PRE_TIME];
            script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_FIRE;
        }
    }
}

void N(RangedAttack_Fire)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Enemy* missile;
    s32 npcID;

    npc->duration--;
    if (npc->duration <= 0) {
        npcID = N(RangedAttack_GetUsableMissileID)(script);
        if (npcID < 0) {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        } else {
            missile = get_enemy(npcID);
            missile->varTable[AI_VAR_MISSILE_OWNER] = enemy->npcID;
            missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_REQUESTED;
            npc->curAnim = enemy->animList[AI_ANIM_RANGED_FIRE];
        }
        npc->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_COOLDOWN;
    }
}

void N(RangedAttack_Cancel)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;

    get_npc_unsafe(enemy->npcID)->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
    script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_COOLDOWN;
}

void N(RangedAttack_Await)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Enemy* missile = get_enemy(enemy->npcID + 1);
    Npc* missileNpc = get_npc_unsafe(missile->npcID);

    npc->yaw = atan2(npc->pos.x, npc->pos.z, missileNpc->pos.x, missileNpc->pos.z);
    if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_COOLDOWN;
    }
}

void N(RangedAttack_Cooldown)(Evt* script) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

enum MissileStopReason {
    MISSILE_STOP_NONE                = 0,
    MISSILE_STOP_HIT_WALL            = 1,
    MISSILE_STOP_HIT_GROUND          = 10,
    MISSILE_STOP_NEAR_FLOOR          = 11,
    MISSILE_STOP_TIMEOUT             = 20,
};

API_CALLABLE(N(MissileAI_Main)) {
    Enemy* missile = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    s32 stopReason = MISSILE_STOP_NONE;
    f32 x, y, z;
    f32 hitDepth;
    Npc* npc;
    Npc* parentNpc;
    MobileAISettings* settings;

    if (get_enemy_safe(missile->npcID) == nullptr) {
        return ApiStatus_BLOCK;
    }

    if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_DONE) {
        return ApiStatus_BLOCK;
    }

    settings = (MobileAISettings*)evt_get_variable(script, *args++);
    npc = get_npc_unsafe(missile->npcID);

    if (missile->varTable[AI_VAR_MISSILE_FLAGS] & AI_MISSILE_FLAG_CENTERED) {
        npc->verticalRenderOffset = npc->collisionHeight / 2;
    }

    if (isInitialCall || (missile->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_MISSILE_INIT;
        npc->duration = 0;
        npc->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_PLAYER_COLLISION | NPC_FLAG_INVISIBLE;
        disable_npc_shadow(npc);
        npc->flags &= ~NPC_FLAG_JUMPING;
        missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
        missile->flags |= ENEMY_INTANGIBLE_FLAGS;
        missile->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_PROJECTILE;
        if (missile->aiFlags & AI_FLAG_SUSPEND) {
            missile->aiFlags &= ~AI_FLAG_SUSPEND;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MISSILE_INIT:
            npc->flags |= NPC_FLAG_INVISIBLE;
            disable_npc_shadow(npc);
            missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
            script->AI_TEMP_STATE = AI_STATE_MISSILE_READY;
            // fallthrough
        case AI_STATE_MISSILE_READY:
            // wait for a launch request
            if (missile->varTable[AI_VAR_MISSILE_STATUS] != MISSILE_STATUS_REQUESTED) {
                break;
            }
            missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_ACTIVE;
            parentNpc = get_npc_unsafe(missile->varTable[AI_VAR_MISSILE_OWNER]);
            npc->pos.x = parentNpc->pos.x;
            npc->pos.y = parentNpc->pos.y + missile->varTable[AI_VAR_MISSILE_SPAWN_Y];
            npc->pos.z = parentNpc->pos.z;
            add_vec2D_polar(&npc->pos.x, &npc->pos.z, missile->varTable[AI_VAR_MISSILE_SPAWN_R], 270.0f - parentNpc->renderYaw);
            missile->firstStrikeActive = true;
            missile->attackOriginPos.x = npc->pos.x;
            missile->attackOriginPos.y = npc->pos.y;
            missile->attackOriginPos.z = npc->pos.z;
            npc->rot.x = 0.0f;
            npc->rot.y = 0.0f;
            npc->rot.z = 0.0f;
            npc->moveSpeed = settings->moveSpeed;
            npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            npc->jumpVel = settings->alertRadius;
            npc->jumpScale = settings->alertOffsetDist;
            npc->moveToPos.y = parentNpc->pos.y;
            npc->flags &= ~NPC_FLAG_INVISIBLE;
            enable_npc_shadow(npc);
            npc->flags |= NPC_FLAG_JUMPING;
            missile->flags &= ~MISSILE_INTANGIBLE_FLAGS;
            npc->duration = 90;
            script->AI_TEMP_STATE = AI_STATE_MISSILE_FIRED;
            break;
        case AI_STATE_MISSILE_FIRED:
            // test forward motion
            x = npc->pos.x;
            y = npc->pos.y + (npc->collisionHeight * 0.5);
            z = npc->pos.z;
            if (npc_test_move_taller_with_slipping(0, &x, &y, &z,
                npc->moveSpeed, npc->yaw, npc->collisionDiameter, npc->collisionHeight)
            ) {
                stopReason = MISSILE_STOP_HIT_WALL;
            }

            // test vertical motion
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            hitDepth = 1000.0f;
            if ((npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth))
                && (hitDepth < fabsf(npc->jumpVel))
                && (fabsf(y - npc->moveToPos.y) < 20.0)
            ) {
                npc->pos.y = y;
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
                stopReason = MISSILE_STOP_HIT_GROUND;
            }

            // very close to floor?
            if (hitDepth < 1.0) {
                stopReason = MISSILE_STOP_NEAR_FLOOR;
            }

            npc->duration--;
            if (npc->duration <= 0) {
                stopReason = MISSILE_STOP_TIMEOUT;
            }

            if (stopReason == MISSILE_STOP_NONE) {
                if (missile->varTable[AI_VAR_MISSILE_FLAGS] & AI_MISSILE_FLAG_SPINNING) {
                    npc->rot.z += 40.0;
                }
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
                npc->pos.y += npc->jumpVel;
                npc->jumpVel -= npc->jumpScale;
            } else {
                fx_walking_dust(2, npc->pos.x, npc->pos.y, npc->pos.z, 0, 0);
                missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
                npc->pos.x = NPC_DISPOSE_POS_X;
                npc->pos.y = NPC_DISPOSE_POS_Y;
                npc->pos.z = NPC_DISPOSE_POS_Z;
                npc->jumpVel = 0.0f;
                npc->flags |= NPC_FLAG_INVISIBLE;
                disable_npc_shadow(npc);
                npc->flags &= ~NPC_FLAG_JUMPING;
                missile->flags |= MISSILE_INTANGIBLE_FLAGS;
                script->AI_TEMP_STATE = AI_STATE_MISSILE_INIT;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

enum ReflectEndReason {
    REFLECT_STOP_NONE                = 0,
    REFLECT_STOP_HIT_WALL            = 1,
    REFLECT_STOP_HIT_GROUND          = 10,
    REFLECT_STOP_NEAR_FLOOR          = 11,
    REFLECT_STOP_TIMEOUT             = 20,
};

API_CALLABLE(N(MissileAI_Reflect)) {
    Enemy* missile = script->owner1.enemy;
    Camera* camera = &gCameras[gCurrentCamID];
    s32 stopReason = REFLECT_STOP_NONE;
    Npc* npc;
    f32 x, y, z;
    f32 hitDepth;
    f32 yaw;
    b32 hitGround;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_MISSILE_REFLECT_INIT;
    }

    if (get_enemy_safe(missile->npcID) == nullptr) {
        evt_set_variable(script, LVar0, false);
        return ApiStatus_DONE2;
    }

    if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_DONE) {
        evt_set_variable(script, LVar0, false);
        return ApiStatus_DONE2;
    }

    if (get_enemy_safe(missile->npcID) == nullptr) {
        evt_set_variable(script, LVar0, false);
        return ApiStatus_DONE2;
    }

    npc = get_npc_unsafe(missile->npcID);
    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MISSILE_REFLECT_INIT:
            fx_walking_dust(2, npc->pos.x, npc->pos.y, npc->pos.z, 0.0f, 0.0f);
            yaw = clamp_angle(camera->curYaw);
            if (clamp_angle(get_clamped_angle_diff(camera->curYaw, gPlayerStatusPtr->curYaw)) < 180.0) {
                npc->yaw = clamp_angle(yaw + 90.0);
            } else {
                npc->yaw = clamp_angle(yaw - 90.0);
            }
            npc->duration = 30;
            npc->jumpVel = 10.0f;
            npc->jumpScale = 0.9f;
            npc->moveSpeed *= 1.2;
            script->AI_TEMP_STATE = AI_STATE_MISSILE_REFLECT_ACTIVE;
            // fallthrough
        case AI_STATE_MISSILE_REFLECT_ACTIVE:
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            if (npc_test_move_simple_with_slipping(0, &x, &y, &z,
                npc->moveSpeed, npc->yaw, npc->collisionDiameter, npc->collisionHeight)
            ) {
                stopReason = REFLECT_STOP_HIT_WALL;
            } else {
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            }

            hitGround = false;
            if (npc->jumpVel < 0.0) {
                x = npc->pos.x;
                y = npc->pos.y + 13.0;
                z = npc->pos.z;
                hitDepth = fabsf(npc->jumpVel) + 16.0;
                if (npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth)
                    && (hitDepth <= (fabsf(npc->jumpVel) + 13.0))
                ) {
                    hitGround = true;
                }
            }

            if (hitGround) {
                stopReason = REFLECT_STOP_HIT_GROUND;
            } else {
                npc->pos.y += npc->jumpVel;
                npc->jumpVel -= npc->jumpScale;
            }

            npc->duration--;
            if (npc->duration <= 0) {
                stopReason = REFLECT_STOP_TIMEOUT;
            }

            if (stopReason != REFLECT_STOP_NONE) {
                fx_walking_dust(2, npc->pos.x, npc->pos.y, npc->pos.z, 0, 0);
                missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
                npc->pos.x = NPC_DISPOSE_POS_X;
                npc->pos.y = NPC_DISPOSE_POS_Y;
                npc->pos.z = NPC_DISPOSE_POS_Z;
                npc->flags |= NPC_FLAG_INVISIBLE;
                disable_npc_shadow(npc);
                npc->flags &= ~NPC_FLAG_JUMPING;
                missile->flags |= MISSILE_INTANGIBLE_FLAGS;
                script->AI_TEMP_STATE = AI_STATE_MISSILE_REFLECT_INIT;
                evt_set_variable(script, LVar0, true);
                return ApiStatus_DONE2;
            }

            if (missile->varTable[AI_VAR_MISSILE_FLAGS] & AI_MISSILE_FLAG_SPINNING) {
                npc->rot.z += 60.0;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(GetEncounterEnemyIsOwner)) {
    Enemy* enemy = script->owner1.enemy;

    evt_set_variable(script, LVar0, gCurrentEncounter.curEnemy == enemy);
    return ApiStatus_DONE2;
}
