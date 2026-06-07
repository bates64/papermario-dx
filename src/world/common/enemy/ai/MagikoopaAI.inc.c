#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"
#include "sprite.h"

#include "world/common/enemy/ai/MagikoopaSpellAI.inc.c"

enum MagikoopaAiStates {
    AI_STATE_MAGIKOOPA_IDLE         = 0,
    AI_STATE_MAGIKOOPA_VANISH       = 1,
    AI_STATE_MAGIKOOPA_WARP_INIT    = 5,
    AI_STATE_MAGIKOOPA_WARP_MOVE    = 6,
    AI_STATE_MAGIKOOPA_APPEAR_INIT  = 10,
    AI_STATE_MAGIKOOPA_APPEAR       = 11,
    AI_STATE_MAGIKOOPA_CAST_INIT    = 20,
    AI_STATE_MAGIKOOPA_TARGETING    = 21,
    AI_STATE_MAGIKOOPA_CASTING      = 22,
    AI_STATE_MAGIKOOPA_FIRING       = 23,
    AI_STATE_MAGIKOOPA_POST_CAST    = 24,
};

enum MagikoopaAiVars {
    AI_VAR_MAGIKOOPA_APPEAR_FAST    = 0,
};

enum MagikoopaAiAnims {
    AI_ANIM_MAGIKOOPA_CAST          = 8, // preparing the spell, with staff raised
    AI_ANIM_MAGIKOOPA_FIRE          = 9, // throwing the spell
};

typedef struct MagikoopaTeleportAnim {
    f32 scaleX;
    f32 scaleY;
    u8 alpha;
} MagikoopaTeleportAnim;

MagikoopaTeleportAnim N(MagikoopaAI_TeleportAnim)[] = {
    { 0.80f, 1.0f, 200 },
    { 0.60f, 1.0f, 180 },
    { 0.50f, 1.0f, 160 },
    { 0.40f, 1.0f, 140 },
    { 0.30f, 1.1f, 120 },
    { 0.20f, 1.3f, 110 },
    { 0.15f, 1.6f, 100 },
    { 0.12f, 2.0f, 90 },
    { 0.11f, 3.0f, 80 },
    { 0.10f, 4.0f, 70 },
    { 0.00f, 0.0f, 0 },
};

void N(MagikoopaAI_Idle)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->flags &= ~NPC_FLAG_INVISIBLE;
        npc->duration = 0;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_VANISH;
    }
}

void N(MagikoopaAI_Vanish)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    npc->scale.x = N(MagikoopaAI_TeleportAnim)[npc->duration].scaleX;
    npc->scale.y = N(MagikoopaAI_TeleportAnim)[npc->duration].scaleY;
    npc->alpha = N(MagikoopaAI_TeleportAnim)[npc->duration].alpha;

    npc->duration++;
    if (npc->duration == 4) {
        disable_npc_shadow(npc);
        enemy->flags |= ENEMY_INTANGIBLE_FLAGS;
    }

    if (N(MagikoopaAI_TeleportAnim)[npc->duration].alpha == 0) {
        npc->alpha = 255;
        npc->scale.x = 1.0f;
        npc->scale.y = 1.0f;
        npc->scale.z = 1.0f;
        npc->flags |= NPC_FLAG_INVISIBLE;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_WARP_INIT;
    }
}

void N(MagikoopaAI_WarpInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);
    f32 angle = (rand_int(100) % 2) * 180.0f; // equal chance of 0 or 180

    npc->duration = 15;
    npc->moveSpeed = 0.8f;
    npc->yaw = angle + 90.0f;
    script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_WARP_MOVE;
}

void N(MagikoopaAI_WarpMove)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc_move_heading(npc, npc->moveSpeed, npc->yaw);
    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_APPEAR_INIT;
    }
}

void N(MagikoopaAI_AppearInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;
    f32 hitDepth;

    enemy->varTable[AI_VAR_MAGIKOOPA_APPEAR_FAST] = true;
    npc->curAnim = enemy->animList[AI_ANIM_MAGIKOOPA_CAST];
    npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    npc->flags &= ~NPC_FLAG_INVISIBLE;
    npc->scale.x = 0.1f;
    npc->scale.y = 0.1f;
    npc->scale.z = 0.1f;
    if (!(npc->flags & NPC_FLAG_FLYING)) {
        posX = npc->pos.x;
        posY = npc->pos.y + 100.0;
        posZ = npc->pos.z;
        hitDepth = 200.0f;
        if (npc_raycast_down_sides(npc->collisionChannel, &posX, &posY, &posZ, &hitDepth)) {
            npc->pos.y = posY;
        }
    }
    npc->duration = 0;
    script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_APPEAR;
}

void N(MagikoopaAI_Appear)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s16 alpha;

    if (enemy->varTable[AI_VAR_MAGIKOOPA_APPEAR_FAST]) {
        alpha = (npc->duration * 15) + 30;
    } else {
        alpha = (npc->duration * 15) + 130;
    }
    if (alpha > 255) {
        alpha = 255;
    }
    npc->alpha = alpha;

    npc->scale.x = (npc->duration * 0.1) + 0.4;
    if (npc->scale.x > 1.0) {
       npc->scale.x = 1.0f;
    }
    npc->scale.y = npc->scale.x;
    npc->scale.z = npc->scale.x;

    npc->duration++;
    if (npc->duration == 5) {
        enable_npc_shadow(npc);
        enemy->flags &= ~ENEMY_INTANGIBLE_FLAGS;
    }

    if (enemy->varTable[AI_VAR_MAGIKOOPA_APPEAR_FAST]) {
        if (npc->duration >= 10) {
            npc->alpha = 255;
            npc->scale.x = 1.0f;
            npc->scale.y = 1.0f;
            npc->scale.z = 1.0f;
            script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_CAST_INIT;
        }
    } else {
        if (npc->duration >= 20) {
            set_npc_imgfx_all(npc->spriteInstanceID, IMGFX_CLEAR, 0, 0, 0, 0, 0);
            npc->alpha = 255;
            npc->scale.x = 1.0f;
            npc->scale.y = 1.0f;
            npc->scale.z = 1.0f;
            script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_CAST_INIT;
        }
    }
}

void N(MagikoopaAI_CastInit)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = 40;
    script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_TARGETING;
}

void N(MagikoopaAI_Targeting)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posY, posZ;

    npc->duration--;
    if (npc->duration == 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_IDLE;
        return;
    }

    if (N(MagikoopaAI_CanShootSpell)(script, settings->chaseRadius, settings->chaseOffsetDist, detect) == 1) {
        ai_enemy_play_sound(npc, SOUND_SPELL_CAST1, 0);
        npc->curAnim = enemy->animList[AI_ANIM_MAGIKOOPA_CAST];
        posX = npc->pos.x;
        posY = npc->pos.y + 32.0f;
        posZ = npc->pos.z + 1.0f;
        add_vec2D_polar(&posX, &posZ, 17.0f, 270.0f - npc->renderYaw);
        fx_gather_energy_pink(0, posX, posY, posZ, 0.1f, 13);
        npc->duration = 15;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_CASTING;
    }
}

void N(MagikoopaAI_Casting)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[AI_ANIM_MAGIKOOPA_FIRE];
        npc->duration = 9;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_FIRING;
    }
}

void N(MagikoopaAI_Firing)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        if (N(MagikoopaAI_CanShootSpell)(script, settings->chaseRadius, settings->chaseOffsetDist, detect) == 1) {
            ai_enemy_play_sound(npc, SOUND_SPELL_CAST2, 0);
            get_enemy(enemy->npcID + 1)->varTable[AI_VAR_SPELL_STATUS] = SPELL_STATUS_REQUESTED;
            npc->duration = 20;
            script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_POST_CAST;
        } else {
            fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
            npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
            npc->duration = 15;
            script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_IDLE;
        }
    }
}

void N(MagikoopaAI_PostCast)(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 3;
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_IDLE;
    }
}

API_CALLABLE(N(MagikoopaAI_Main)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    MobileAISettings* settings = (MobileAISettings*) evt_get_variable(script, *args++);
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

    if (isInitialCall || (enemy->aiFlags & AI_FLAG_SUSPEND)) {
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->flags &= ~NPC_FLAG_JUMPING;
        npc->flags |= NPC_FLAG_FLIP_INSTANTLY;
        enemy->flags |= ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN;
        npc->duration = 0;
        if (enemy->aiFlags & AI_FLAG_SUSPEND) {
            enemy->aiFlags &= ~AI_FLAG_SUSPEND;
            npc->alpha = 255;
            npc->duration = 20;
            npc->scale.x = 1.0f;
            npc->scale.y = 1.0f;
            npc->scale.z = 1.0f;
        }
        script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_IDLE;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_MAGIKOOPA_IDLE:
            N(MagikoopaAI_Idle)(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_MAGIKOOPA_VANISH) {
                break;
            }
            // fallthrough
        case AI_STATE_MAGIKOOPA_VANISH:
            N(MagikoopaAI_Vanish)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_WARP_INIT:
            N(MagikoopaAI_WarpInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_MAGIKOOPA_WARP_MOVE:
            N(MagikoopaAI_WarpMove)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_APPEAR_INIT:
            N(MagikoopaAI_AppearInit)(script, settings, detect);
            // fallthrough
        case AI_STATE_MAGIKOOPA_APPEAR:
            N(MagikoopaAI_Appear)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_CAST_INIT:
            N(MagikoopaAI_CastInit)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_TARGETING:
            N(MagikoopaAI_Targeting)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_CASTING:
            N(MagikoopaAI_Casting)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_FIRING:
            N(MagikoopaAI_Firing)(script, settings, detect);
            break;

        case AI_STATE_MAGIKOOPA_POST_CAST:
            N(MagikoopaAI_PostCast)(script, settings, detect);
            break;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(MagikoopaAI_OnPlayerWon)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->alpha = 255;
    set_npc_imgfx_all(npc->spriteInstanceID, IMGFX_CLEAR, 0, 0, 0, 0, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(MagikoopaAI_OnPlayerFled)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->alpha = 255;
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_RUN];
    npc->duration = 0;
    script->AI_TEMP_STATE = AI_STATE_MAGIKOOPA_IDLE;
    return ApiStatus_DONE2;
}
