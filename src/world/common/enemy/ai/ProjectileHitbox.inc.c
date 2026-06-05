#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

enum RangedAttackerAiVars {
    AI_VAR_RANGED_0                 = 0,
    AI_VAR_RANGED_PRE_TIME          = 1,
    AI_VAR_RANGED_POST_TIME         = 2,
    AI_VAR_RANGED_AMMO_COUNT        = 3,
};

enum MissileAiStates {
    AI_STATE_MISSLE_0           = 0,
    AI_STATE_MISSLE_1           = 1,
    AI_STATE_MISSLE_2           = 2,
};

enum MissileAiVars {
    AI_VAR_MISSILE_STATUS       = 0,
    AI_VAR_MISSILE_FLAGS        = 1,
    AI_VAR_MISSILE_2            = 2,
    AI_VAR_MISSILE_3            = 3,
    AI_VAR_MISSILE_OWNER        = 4,
};

enum MissileAiFlags {
    AI_MISSILE_FLAG_SPINNING    = 0x1,
    AI_MISSILE_FLAG_2           = 0x2,
};

enum MissileStatus {
    MISSILE_STATUS_IDLE         = 0, // bullet is unoccupied and ready to be fired
    MISSILE_STATUS_1            = 1, // reserved?
    MISSILE_STATUS_2            = 2,
    MISSILE_STATUS_3            = 3,
    MISSILE_STATUS_5            = 5,
};

enum MissileReflectAiStates {
    AI_STATE_MISSLE_REFLECT_0           = 0,
    AI_STATE_MISSLE_REFLECT_1           = 1,
    AI_STATE_MISSLE_REFLECT_2           = 2,
};

s32 N(ProjectileHitbox_GetUsableProjectileID)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    Camera* camera = &gCameras[gCurrentCamID];
    Npc* npc = get_npc_unsafe(enemy->npcID);
    MobileAISettings* aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);
    f32 facingAngle;
    f32 angleToPlayer;
    f32 deltaAngle;
    s32 i;

    if (ai_check_player_dist(enemy, 0, aiSettings->chaseRadius, aiSettings->chaseOffsetDist)) {
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
            s32 projectileNpcID = enemy->npcID + i + 1;
            Enemy* projectileEnemy = get_enemy(projectileNpcID);

            get_npc_unsafe(projectileNpcID);

            if (projectileEnemy->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE) {
                return projectileNpcID;
            }
        }
    }
    return -1;
}

void N(UnkNpcAIFunc48)(Evt* script, f32 radius, f32 offset, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (!basic_ai_check_player_dist(territory, enemy, radius, offset, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 20;
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_33;
    } else {
        s32 npcID = N(ProjectileHitbox_GetUsableProjectileID)(script);

        if (npcID >= 0
            && get_enemy(npcID)->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE
            && npc->turnAroundYawAdjustment == 0
        ) {
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
            npc->duration = enemy->varTable[AI_VAR_RANGED_PRE_TIME];
            script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_30;
        }
    }
}

void N(ProjectileHitbox_30)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Enemy* missileEnemy;
    s32 npcID;

    npc->duration--;
    if (npc->duration <= 0) {
        npcID = N(ProjectileHitbox_GetUsableProjectileID)(script);
        if (npcID < 0) {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        } else {
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_HIT];
            missileEnemy = get_enemy(npcID);
            missileEnemy->varTable[AI_VAR_MISSILE_OWNER] = enemy->npcID;
            missileEnemy->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_1;
        }
        npc->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_33;
    }
}

void N(ProjectileHitbox_31)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;

    get_npc_unsafe(enemy->npcID)->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
    script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_33;
}

void N(ProjectileHitbox_32)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Enemy* missileEnemy = get_enemy(enemy->npcID + 1);
    Npc* missileNpc = get_npc_unsafe(missileEnemy->npcID);

    npc->yaw = atan2(npc->pos.x, npc->pos.z, missileNpc->pos.x, missileNpc->pos.z);
    if (missileEnemy->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_IDLE) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = enemy->varTable[AI_VAR_RANGED_POST_TIME];
        script->AI_TEMP_STATE = AI_STATE_RANGED_ATTACK_33;
    }
}

// TODO same as ParatroopaAI_Reset, but removes the extra args since it affects codegen...?
void N(ProjectileHitbox_33)(Evt* script) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

API_CALLABLE(N(ProjectileAI_Main)) {
    Enemy* missile = script->owner1.enemy;
    Bytecode* args = script->ptrReadPos;
    s32 phi_s6 = 0;
    f32 x, y, z;
    f32 hitDepth;
    Npc* npc;
    Npc* parentNpc;
    MobileAISettings* aiSettings;

    if (get_enemy_safe(missile->npcID) == nullptr) {
        return ApiStatus_BLOCK;
    }

    if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_5) {
        return ApiStatus_BLOCK;
    }

    aiSettings = (MobileAISettings*)evt_get_variable(script, *args++);
    npc = get_npc_unsafe(missile->npcID);

    if (missile->varTable[AI_VAR_MISSILE_FLAGS] & AI_MISSILE_FLAG_2) {
        npc->verticalRenderOffset = npc->collisionHeight / 2;
    }

    if (isInitialCall || (missile->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_MISSLE_0;
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
        case AI_STATE_MISSLE_0:
            npc->flags |= NPC_FLAG_INVISIBLE;
            disable_npc_shadow(npc);
            missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
            script->AI_TEMP_STATE = AI_STATE_MISSLE_1;
            // fallthrough
        case AI_STATE_MISSLE_1:
            if (missile->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_1) {
                missile->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_2;
                parentNpc = get_npc_unsafe(missile->varTable[AI_VAR_MISSILE_OWNER]);
                npc->pos.x = parentNpc->pos.x;
                npc->pos.y = parentNpc->pos.y + missile->varTable[AI_VAR_MISSILE_2];
                npc->pos.z = parentNpc->pos.z;
                add_vec2D_polar(&npc->pos.x, &npc->pos.z, missile->varTable[AI_VAR_MISSILE_3], 270.0f - parentNpc->renderYaw);
                missile->firstStrikeActive = true;
                missile->attackOriginPos.x = npc->pos.x;
                missile->attackOriginPos.y = npc->pos.y;
                missile->attackOriginPos.z = npc->pos.z;
                npc->rot.x = 0.0f;
                npc->rot.y = 0.0f;
                npc->rot.z = 0.0f;
                npc->moveSpeed = aiSettings->moveSpeed;
                npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                npc->jumpVel = aiSettings->alertRadius;
                npc->jumpScale = aiSettings->alertOffsetDist;
                npc->moveToPos.y = parentNpc->pos.y;
                npc->flags &= ~NPC_FLAG_INVISIBLE;
                enable_npc_shadow(npc);
                npc->flags |= NPC_FLAG_JUMPING;
                missile->flags &= ~(ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_HAMMER |
                                    ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_TOUCH);
                npc->duration = 90;
                script->AI_TEMP_STATE = AI_STATE_MISSLE_2;
                break;
            }
            break;
        case AI_STATE_MISSLE_2:
            x = npc->pos.x;
            y = npc->pos.y + (npc->collisionHeight * 0.5);
            z = npc->pos.z;
            if (npc_test_move_taller_with_slipping(
                0, &x, &y, &z, npc->moveSpeed, npc->yaw, npc->collisionDiameter, npc->collisionHeight))
            {
                phi_s6 = 1;
            }

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
                phi_s6 = 10;
            }

            if (hitDepth < 1.0) {
                phi_s6 = 11;
            }
            npc->duration--;
            if (npc->duration <= 0) {
                phi_s6 = 20;
            }

            if (phi_s6 == 0) {
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
                missile->flags |= ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_HAMMER |
                                ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_TOUCH;
                script->AI_TEMP_STATE = AI_STATE_MISSLE_0;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(ProjectileAI_Reflect)) {
    Enemy* missileEnemy = script->owner1.enemy;
    Camera* camera = &gCameras[gCurrentCamID];
    s32 phi_s4 = 0;
    Npc* npc;
    f32 x, y, z;
    f32 hitDepth;
    f32 yaw;
    s32 cond;

    if (isInitialCall) {
        script->AI_TEMP_STATE = AI_STATE_MISSLE_REFLECT_0;
    }

    if (get_enemy_safe(missileEnemy->npcID) == nullptr) {
        evt_set_variable(script, LVar0, 0);
        return ApiStatus_DONE2;
    }
    if (missileEnemy->varTable[AI_VAR_MISSILE_STATUS] == MISSILE_STATUS_5) {
        evt_set_variable(script, LVar0, 0);
        return ApiStatus_DONE2;
    }
    if (get_enemy_safe(missileEnemy->npcID) == nullptr) {
        evt_set_variable(script, LVar0, 0);
        return ApiStatus_DONE2;
    }

    npc = get_npc_unsafe(missileEnemy->npcID);
    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MISSLE_REFLECT_0:
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
            script->AI_TEMP_STATE = AI_STATE_MISSLE_REFLECT_1;
            // fallthrough
        case AI_STATE_MISSLE_REFLECT_1:
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            if (!npc_test_move_simple_with_slipping(0,
                &x, &y, &z, npc->moveSpeed, npc->yaw, npc->collisionDiameter, npc->collisionHeight)
            ) {
                npc_move_heading(npc, npc->moveSpeed, npc->yaw);
            } else {
                phi_s4 = 1;
            }

            cond = false;
            if (npc->jumpVel < 0.0) {
                x = npc->pos.x;
                y = npc->pos.y + 13.0;
                z = npc->pos.z;
                hitDepth = fabsf(npc->jumpVel) + 16.0;
                if ((npc_raycast_down_sides(npc->collisionChannel, &x, &y, &z, &hitDepth) != 0) &&
                    (hitDepth <= (fabsf(npc->jumpVel) + 13.0)))
                {
                    cond = true;
                }
            }

            if (!cond) {
                npc->pos.y += npc->jumpVel;
                npc->jumpVel -= npc->jumpScale;
            } else {
                phi_s4 = 10;
            }

            npc->duration--;
            if (npc->duration <= 0) {
                phi_s4 = 11;
            }

            if (phi_s4 != 0) {
                fx_walking_dust(2, npc->pos.x, npc->pos.y, npc->pos.z, 0, 0);
                missileEnemy->varTable[AI_VAR_MISSILE_STATUS] = MISSILE_STATUS_IDLE;
                npc->pos.x = NPC_DISPOSE_POS_X;
                npc->pos.y = NPC_DISPOSE_POS_Y;
                npc->pos.z = NPC_DISPOSE_POS_Z;
                npc->flags |= NPC_FLAG_INVISIBLE;
                disable_npc_shadow(npc);
                npc->flags &= ~NPC_FLAG_JUMPING;
                missileEnemy->flags |= ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_HAMMER |
                                ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_TOUCH;
                script->AI_TEMP_STATE = AI_STATE_MISSLE_REFLECT_0;
                evt_set_variable(script, LVar0, 1);
                return ApiStatus_DONE2;
            }
            if (missileEnemy->varTable[AI_VAR_MISSILE_FLAGS] & AI_MISSILE_FLAG_SPINNING) {
                npc->rot.z += 60.0;
            }
            break;
    }
    return ApiStatus_BLOCK;
}
