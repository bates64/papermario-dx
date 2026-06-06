#pragma once

#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

#define AI_PATROL_GOAL_INDEX    functionTemp[2]

void N(PatrolAI_MoveInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 dist;
    f32 nearest;
    f32 posX, posZ;
    s32 pointX, pointZ;
    s32 i;

    nearest = 32767.0f;
    posX = npc->pos.x;
    posZ = npc->pos.z;
    script->functionTemp[1] = 0;
    script->AI_PATROL_GOAL_INDEX = 0;

    // select the next patrol point
    for (i = 0; i < enemy->territory->patrol.numPoints; i++) {
        pointX = enemy->territory->patrol.points[i].x;
        pointZ = enemy->territory->patrol.points[i].z;
        dist = dist2D(posX, posZ, pointX, pointZ);
        if (dist < nearest) {
            nearest = dist;
            script->AI_PATROL_GOAL_INDEX = i;
        }
    }

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    if (enemy->territory->patrol.moveSpeedOverride < 0) {
        npc->moveSpeed = aiSettings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->patrol.moveSpeedOverride / 32767.0;
    }

    script->AI_TEMP_STATE = AI_STATE_PATROL;
}

void N(PatrolAI_Move)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, z;

    if (aiSettings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = aiSettings->playerSearchInterval;
            if (basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, false)) {
                fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
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

    if (npc->turnAroundYawAdjustment == 0) {
        if (npc->moveSpeed < 4.0) {
            npc_surface_spawn_fx(npc, SURFACE_INTERACT_WALK);
        } else {
            npc_surface_spawn_fx(npc, SURFACE_INTERACT_RUN);
        }
        x = enemy->territory->patrol.points[script->AI_PATROL_GOAL_INDEX].x;
        z = enemy->territory->patrol.points[script->AI_PATROL_GOAL_INDEX].z;
        npc->yaw = atan2(npc->pos.x, npc->pos.z, x, z);
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        if (dist2D(npc->pos.x, npc->pos.z, x, z) <= npc->moveSpeed) {
            script->AI_TEMP_STATE = AI_STATE_LOITER_INIT;
            script->functionTemp[1] = (rand_int(1000) % 3) + 2;
            if ((aiSettings->loiterMode <= 0) || (aiSettings->moveTime <= 0) || (aiSettings->waitTime <= 0)) {
                script->AI_TEMP_STATE = AI_STATE_LOITER_POST;
            }
            if (rand_int(10000) % 100 < aiSettings->moveTime) {
                script->AI_TEMP_STATE = AI_STATE_LOITER_POST;
            }
        }
    }
}

// identical to basic_ai_loiter_init
void N(PatrolAI_LoiterInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (aiSettings->waitTime / 2) + rand_int((aiSettings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void N(PatrolAI_Loiter)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if ((aiSettings->playerSearchInterval >= 0) && basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, false)) {
        fx_emote(EMOTE_EXCLAMATION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
        if (!(enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER)) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        } else {
            script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
        }
        return;
    }

    // look around randomly
    if (npc->turnAroundYawAdjustment == 0) {
        npc->duration--;
        if (npc->duration == 0) {
            script->functionTemp[1]--;
            if (script->functionTemp[1] != 0) {
                if (!(enemy->npcSettings->actionFlags & AI_ACTION_LOOK_AROUND_DURING_LOITER)) {
                    npc->yaw = clamp_angle(npc->yaw + 180.0f);
                }
                npc->duration = (aiSettings->waitTime / 2) + rand_int(aiSettings->waitTime / 2 + 1);
            } else {
                script->AI_TEMP_STATE = AI_STATE_LOITER_POST;
            }
        }
    }
}

void N(PatrolAI_PostLoiter)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    script->AI_PATROL_GOAL_INDEX++;
    if (script->AI_PATROL_GOAL_INDEX >= enemy->territory->patrol.numPoints) {
        script->AI_PATROL_GOAL_INDEX = 0;
    }
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    if (enemy->territory->patrol.moveSpeedOverride < 0) {
        npc->moveSpeed = aiSettings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->patrol.moveSpeedOverride / 32767.0;
    }
    script->AI_TEMP_STATE = AI_STATE_PATROL;
}

void N(PatrolAI_JumpInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_JUMP];
    npc->jumpVel = 10.0f;
    npc->jumpScale = 2.0f;
    npc->moveToPos.y = npc->pos.y;
    npc->flags |= NPC_FLAG_JUMPING;
    script->AI_TEMP_STATE = AI_STATE_ALERT;
}

void N(PatrolAI_Jump)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
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

void N(PatrolAI_ChaseInit)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 angle;
    f32 angleDiff;

    npc->duration = (aiSettings->chaseUpdateInterval / 2) + rand_int(aiSettings->chaseUpdateInterval / 2 + 1);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = aiSettings->chaseSpeed;

    angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
    angleDiff = get_clamped_angle_diff(npc->yaw, angle);

    // cap the turn rate
    if (aiSettings->chaseTurnRate < fabsf(angleDiff)) {
        if (angleDiff < 0.0f) {
            angle = npc->yaw - aiSettings->chaseTurnRate;
        } else {
            angle = npc->yaw + aiSettings->chaseTurnRate;
        }
    }
    npc->yaw = clamp_angle(angle);

    script->AI_TEMP_STATE = AI_STATE_CHASE;
}

void N(PatrolAI_Chase)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if (!basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0.0f, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 25;
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
    } else {
        npc_surface_spawn_fx(npc, SURFACE_INTERACT_RUN);
        npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        if (npc->duration > 0) {
            npc->duration--;
        } else {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }
    }
}

void N(PatrolAI_LosePlayer)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        if (enemy->aiFlags & AI_FLAG_CAN_RESUME_PATROL) {
            script->AI_TEMP_STATE = AI_STATE_PATROL_RESUME;
        } else {
            script->AI_TEMP_STATE = AI_STATE_PATROL_INIT;
        }
    }
}

void N(PatrolAI_Resume)(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 i;

    // get next patrol point
    for (i = script->AI_PATROL_GOAL_INDEX; i < enemy->territory->patrol.numPoints; i++) {
        if (enemy->territory->patrol.points[i].y <= npc->pos.y) {
            script->AI_PATROL_GOAL_INDEX = i;
            break;
        }
    }

    npc->moveSpeed = aiSettings->moveSpeed;
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    script->functionTemp[1] = 0;
    script->AI_TEMP_STATE = AI_STATE_PATROL;
}
