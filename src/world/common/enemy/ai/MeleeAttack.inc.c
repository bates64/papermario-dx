#pragma once

#include "common.h"
#include "effects.h"
#include "world/ai.h"

enum HitboxAiStates {
    AI_STATE_HITBOX_IDLE        = 0,
    AI_STATE_HITBOX_ACTIVE      = 1,
};

enum HitboxAiVars {
    AI_VAR_HITBOX_YOFFSET       = 0,
    AI_VAR_HITBOX_DIST          = 1,
    AI_VAR_HITBOX_SIGHT_RANGE   = 2,
    AI_VAR_HITBOX_SIGHT_ANGLE   = 3,
    AI_VAR_HITBOX_STRIKE_TIME   = 4,
    AI_VAR_HITBOX_SOUND         = 15,
};

enum MeleeAttackerAiVars {
    AI_VAR_MELEE_STATUS         = 0, // see: MeleeAttackPhase
    AI_VAR_MELEE_PRE_TIME       = 1,
    AI_VAR_MELEE_SWING_TIME     = 2,
    AI_VAR_MELEE_POST_TIME      = 3,
};

enum MeleeAttackPhase {
    MELEE_ATTACK_PHASE_NONE     = 0,
    MELEE_ATTACK_PHASE_INIT     = 1,
    MELEE_ATTACK_PHASE_PRE      = 2,
    MELEE_ATTACK_PHASE_SWING    = 3, // hitbox is active
    MELEE_ATTACK_PHASE_POST     = 4,
};

void N(MeleeAttacker_Init)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_INIT;
    // if flipping, wait for it to finish
    if (npc->turnAroundYawAdjustment == 0) {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_PRE;
        npc->duration = enemy->varTable[AI_VAR_MELEE_PRE_TIME];
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_PRE];
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_PRE;
    }
}

void N(MeleeAttacker_Pre)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_SWING;
        npc->duration = enemy->varTable[AI_VAR_MELEE_SWING_TIME];
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_MELEE_HIT];
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_SWING;
    }
}

void N(MeleeAttacker_Swing)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_POST;
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = enemy->varTable[AI_VAR_MELEE_POST_TIME];
        if (npc->duration >= 8) {
            fx_emote(EMOTE_FRUSTRATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, npc->duration - 1, nullptr);
        }
        script->AI_TEMP_STATE = AI_STATE_MELEE_ATTACK_POST;
    }
}

void N(MeleeAttacker_Post)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        enemy->varTable[AI_VAR_MELEE_STATUS] = MELEE_ATTACK_PHASE_NONE;
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

b32 N(MeleeHitbox_CanTargetPlayer)(Evt* script) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Camera* camera = &gCameras[gCurrentCamID];
    Enemy* hitboxEnemy = get_enemy(enemy->npcID + 1);
    f32 angle;
    b32 ret = true;

    if (dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) > hitboxEnemy->varTable[AI_VAR_HITBOX_SIGHT_RANGE]) {
        ret = false;
    }

    if (clamp_angle(get_clamped_angle_diff(camera->curYaw, npc->yaw)) < 180.0) {
        angle = 90.0f;
    } else {
        angle = 270.0f;
    }

    if (fabsf(get_clamped_angle_diff(angle, atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x,
                                     gPlayerStatusPtr->pos.z))) > hitboxEnemy->varTable[AI_VAR_HITBOX_SIGHT_ANGLE]) {
        ret = false;
    }

    if ((2.0 * npc->collisionHeight) <= fabsf(npc->pos.y - gPlayerStatusPtr->pos.y)) {
        ret = false;
    }

    if (gPartnerStatus.actingPartner == PARTNER_BOW) {
        ret = false;
    }

    if (gPartnerStatus.actingPartner == PARTNER_SUSHIE) {
        ret = false;
    }

    return ret;
}

API_CALLABLE(N(MeleeHitbox_Main)) {
    Enemy* hitboxEnemy = script->owner1.enemy;
    Npc* hitboxNpc = get_npc_unsafe(hitboxEnemy->npcID);
    Enemy* parentEnemy;
    Npc* parentNpc;
    f32 posX, posZ;

    if (isInitialCall || (hitboxEnemy->aiFlags & AI_FLAG_SUSPEND)) {
        script->AI_TEMP_STATE = AI_STATE_HITBOX_IDLE;
        hitboxNpc->duration = 0;
        hitboxNpc->flags |= (NPC_FLAG_INVISIBLE | NPC_FLAG_IGNORE_PLAYER_COLLISION);
        hitboxEnemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        hitboxEnemy->flags |= ENEMY_INTANGIBLE_FLAGS;
        hitboxNpc->pos.x = NPC_DISPOSE_POS_X;
        hitboxNpc->pos.y = NPC_DISPOSE_POS_Y;
        hitboxNpc->pos.z = NPC_DISPOSE_POS_Z;
        if (hitboxEnemy->aiFlags & AI_FLAG_SUSPEND) {
            hitboxEnemy->aiFlags &= ~AI_FLAG_SUSPEND;
        }
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_HITBOX_IDLE:
            parentEnemy = get_enemy(hitboxEnemy->npcID - 1);
            parentNpc = get_npc_unsafe(parentEnemy->npcID);
            hitboxEnemy->firstStrikeActive = true;
            if (parentEnemy->varTable[AI_VAR_MELEE_STATUS] == MELEE_ATTACK_PHASE_SWING) {
                if (hitboxEnemy->varTable[AI_VAR_HITBOX_SOUND] != SOUND_NONE) {
                    ai_enemy_play_sound(parentNpc, hitboxEnemy->varTable[AI_VAR_HITBOX_SOUND], 0);
                }
                posX = parentNpc->pos.x;
                posZ = parentNpc->pos.z;
                add_vec2D_polar(&posX, &posZ, hitboxEnemy->varTable[AI_VAR_HITBOX_DIST], 270.0f - parentNpc->renderYaw);

                hitboxNpc->pos.x = posX;
                hitboxEnemy->attackOriginPos.x = hitboxNpc->pos.x;

                hitboxNpc->pos.y = parentNpc->pos.y + hitboxEnemy->varTable[AI_VAR_HITBOX_YOFFSET];
                hitboxEnemy->attackOriginPos.y = hitboxNpc->pos.y;

                hitboxNpc->pos.z = posZ;
                hitboxEnemy->attackOriginPos.z = hitboxNpc->pos.z;

                hitboxNpc->yaw = atan2(hitboxNpc->pos.x, hitboxNpc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                hitboxEnemy->flags &= ~ENEMY_INTANGIBLE_FLAGS;
                hitboxNpc->duration = 0;
                script->AI_TEMP_STATE = AI_STATE_HITBOX_ACTIVE;
            }
            break;
        case AI_STATE_HITBOX_ACTIVE:
            parentEnemy = get_enemy(hitboxEnemy->npcID - 1);
            parentNpc = get_npc_unsafe(parentEnemy->npcID);
            hitboxNpc->duration++;
            if (hitboxNpc->duration >= hitboxEnemy->varTable[AI_VAR_HITBOX_STRIKE_TIME]) {
                hitboxEnemy->firstStrikeActive = false;
            }
            if (parentEnemy->varTable[AI_VAR_MELEE_STATUS] == MELEE_ATTACK_PHASE_POST) {
                hitboxEnemy->flags |= ENEMY_INTANGIBLE_FLAGS;
                hitboxNpc->pos.x = NPC_DISPOSE_POS_X;
                hitboxNpc->pos.y = NPC_DISPOSE_POS_Y;
                hitboxNpc->pos.z = NPC_DISPOSE_POS_Z;
                hitboxEnemy->firstStrikeActive = true;
                script->AI_TEMP_STATE = AI_STATE_HITBOX_IDLE;
            }
            break;
    }

    return ApiStatus_BLOCK;
}
