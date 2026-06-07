#pragma once

#include "common.h"
#include "effects.h"
#include "world/ai.h"

enum SpellAiStates {
    AI_STATE_SPELL_INIT         = 0,
    AI_STATE_SPELL_READY        = 1,
    AI_STATE_SPELL_FIRED        = 2,
    AI_STATE_SPELL_FIZZLE       = 3,
    AI_STATE_SPELL_CLEANUP      = 4,
};

enum SpellAiVars {
    AI_VAR_SPELL_STATUS         = 0, // see: SpellStatus
    AI_VAR_SPELL_SPAWN_Y        = 1, // additional y-offset from caster when spawned
    AI_VAR_SPELL_SPAWN_R        = 2, // additional radial offset from caster when spawned
    AI_VAR_SPELL_FX_PTR         = 3, // pointer to active EFFECT_SHAPE_SPELL
};

enum SpellStatus {
    SPELL_STATUS_IDLE           = 0, // inactive, able to be cast
    SPELL_STATUS_REQUESTED      = 1, // caster has requested this spell to fire
    SPELL_STATUS_ACTIVE         = 2, // hitbox active and moving
    SPELL_STATUS_FIZZLING       = 3, // missed and is ready for cleanup
};

s32 N(MagikoopaAI_CanShootSpell)(Evt* script, f32 radius, f32 offset, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Camera* camera = &gCameras[gCurrentCamID];
    f32 sideYaw;
    f32 angle;

    if (!basic_ai_check_player_dist(detect, enemy, radius, offset, false)) {
        return -1;
    }

    if (clamp_angle(get_clamped_angle_diff(camera->curYaw, npc->yaw)) < 180.0) {
        sideYaw = 90.0f;
    } else {
        sideYaw = 270.0f;
    }

    angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    if (fabsf(get_clamped_angle_diff(sideYaw, angle)) > 75.0) {
        return -1;
    }

    angle = atan2(0.0f, npc->pos.y, fabsf(npc->pos.x - gPlayerStatusPtr->pos.x), gPlayerStatusPtr->pos.y);
    if (fabsf(angle - 90.0) > 70.0) {
        return -1;
    }

    if (gPartnerStatus.actingPartner == PARTNER_BOW || gPartnerStatus.actingPartner == PARTNER_SUSHIE) {
        return -1;
    }

    if ((get_enemy(enemy->npcID + 1)->varTable[AI_VAR_SPELL_STATUS] != SPELL_STATUS_IDLE)) {
        return -1;
    }

    return 1;
}

enum SpellStopReason {
    SPELL_STOP_NONE         = 0,
    SPELL_STOP_TIMEOUT      = 20,
};

API_CALLABLE(N(MagikoopaSpellAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    s32 stopReason = SPELL_STOP_NONE;
    Npc* spellNpc = get_npc_unsafe(enemy->npcID);
    Npc* casterNpc = get_npc_unsafe(get_enemy(enemy->npcID - 1)->npcID);
    s32 moveTime;
    f32 spellX, spellZ;
    f32 dist, angle;
    f32 dx;

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_SPELL_INIT;
        spellNpc->duration = 0;
        spellNpc->flags |= NPC_FLAG_FLIP_INSTANTLY | NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_PLAYER_COLLISION | NPC_FLAG_INVISIBLE;
        enemy->flags |= ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_JUMP |
                        ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_PROJECTILE;
        spellNpc->scale.x = 0.4f;
        spellNpc->scale.y = 0.4f;
        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_SPELL_INIT:
            enemy->varTablePtr[AI_VAR_SPELL_FX_PTR] = nullptr;
            spellNpc->collisionDiameter = 20;
            spellNpc->collisionHeight = 20;
            spellNpc->pos.x = NPC_DISPOSE_POS_X;
            spellNpc->pos.y = NPC_DISPOSE_POS_Y;
            spellNpc->pos.z = NPC_DISPOSE_POS_Z;
            enemy->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_IDLE;
            script->AI_TEMP_STATE = AI_STATE_SPELL_READY;
            // fallthrough
        case AI_STATE_SPELL_READY:
            if (enemy->varTable[AI_VAR_SPELL_STATUS] != SPELL_STATUS_REQUESTED) {
                break;
            }

            enemy->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_ACTIVE;
            spellX = casterNpc->pos.x;
            spellZ = casterNpc->pos.z;
            add_vec2D_polar(&spellX, &spellZ, enemy->varTable[AI_VAR_SPELL_SPAWN_R], 270.0f - casterNpc->renderYaw);
            spellNpc->pos.x = spellX;
            spellNpc->pos.y = casterNpc->pos.y + enemy->varTable[AI_VAR_SPELL_SPAWN_Y];
            spellNpc->pos.z = spellZ;

            enemy->firstStrikeActive = true;
            enemy->attackOriginPos.x = spellNpc->pos.x;
            enemy->attackOriginPos.y = spellNpc->pos.y;
            enemy->attackOriginPos.z = spellNpc->pos.z;
            spellNpc->moveSpeed = 3.6f;

            dx = fabsf(spellNpc->pos.x - gPlayerStatusPtr->pos.x);
            angle = atan2(0.0f, spellNpc->pos.y, dx, (gPlayerStatusPtr->pos.y + 10.0)) - 90.0;
            spellNpc->jumpVel = cosine(angle) * spellNpc->moveSpeed;
            spellNpc->yaw = atan2(spellNpc->pos.x, spellNpc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            dist = dist3D(spellNpc->pos.x, spellNpc->pos.y, spellNpc->pos.z,
                gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.y + 10.0, gPlayerStatusPtr->pos.z);

            moveTime = dist / spellNpc->moveSpeed;
            if (moveTime <= 0) {
                moveTime = 1;
            }

            // create the effect
            enemy->varTablePtr[AI_VAR_SPELL_FX_PTR] = fx_shape_spell(0,
                spellNpc->pos.x, spellNpc->pos.y + 14.0f, spellNpc->pos.z,
                gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.y + 10.0f + 14.0f, gPlayerStatusPtr->pos.z,
                moveTime);

            spellNpc->duration = moveTime;
            script->AI_TEMP_STATE = AI_STATE_SPELL_FIRED;
            break;
        case AI_STATE_SPELL_FIRED:
            spellNpc->duration--;
            if (spellNpc->duration <= 0) {
                stopReason = SPELL_STOP_TIMEOUT;
            }
            if (stopReason == SPELL_STOP_NONE) {
                npc_move_heading(spellNpc, spellNpc->moveSpeed, spellNpc->yaw);
                spellNpc->pos.y += spellNpc->jumpVel;
                break;
            }
            // fallthrough
        case AI_STATE_SPELL_FIZZLE:
            spellNpc->jumpVel = 0.0f;
            spellNpc->moveSpeed = 0.0f;
            spellNpc->pos.y -= spellNpc->collisionHeight * 0.5;
            enemy->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_FIZZLING;
            spellNpc->duration = 0;
            script->AI_TEMP_STATE = AI_STATE_SPELL_CLEANUP;
            break;
        case AI_STATE_SPELL_CLEANUP:
            spellNpc->duration++;
            if (spellNpc->duration < 7) {
                spellNpc->pos.y -= 3.5;
                spellNpc->collisionDiameter = ((f32) spellNpc->duration * 7.0) + 20.0;
                spellNpc->collisionHeight = ((f32) spellNpc->duration * 7.0) + 20.0;
            } else if (spellNpc->duration == 7) {
                spellNpc->pos.x = NPC_DISPOSE_POS_X;
                spellNpc->pos.y = NPC_DISPOSE_POS_Y;
                spellNpc->pos.z = NPC_DISPOSE_POS_Z;
                spellNpc->collisionDiameter = 20;
                spellNpc->collisionHeight = 20;
            } else if (spellNpc->duration >= 16) {
                enemy->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_IDLE;
                script->AI_TEMP_STATE = AI_STATE_SPELL_INIT;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(MagikoopaSpellAI_OnHitInit)) {
    Enemy* enemy = script->owner1.enemy;

    evt_set_variable(script, LVar0, gCurrentEncounter.curEnemy == enemy);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(MagikoopaSpellAI_OnHit)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (enemy->varTable[AI_VAR_SPELL_STATUS] == SPELL_STATUS_ACTIVE) {
        npc->jumpVel = 0.0f;
        npc->moveSpeed = 0.0f;
    }
    return ApiStatus_DONE2;
}
