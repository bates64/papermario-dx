#include "common.h"
#include "effects.h"
#include "npc.h"
#include "world/ai.h"

void ai_suspend_for_time(Evt* script) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = script->AI_TEMP_STATE_AFTER_SUSPEND;
    }
}

void basic_ai_suspend(Evt* script) {
    Enemy* enemy = script->owner1.enemy;

    get_npc_unsafe(enemy->npcID);
    if (enemy->aiSuspendTime == 0) {
        script->AI_TEMP_STATE = script->AI_TEMP_STATE_AFTER_SUSPEND;
    }
}

b32 ai_check_fwd_collisions(Npc* npc, f32 time, f32* outYaw, f32* outDistFwd, f32* outDistCW, f32* outDistCCW) {
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 x3, y3, z3;
    f32 fwdHitDist = -1.0f;
    f32 cwHitDist = -1.0f;
    f32 ccwHitDist = -1.0f;
    f32 yaw;
    b32 fwdHit;

    x1 = npc->pos.x;
    y1 = npc->pos.y;
    z1 = npc->pos.z;

    if (outYaw != nullptr) {
        yaw = *outYaw;
    } else {
        yaw = npc->yaw;
    }

    fwdHit = npc_test_move_simple_with_slipping(npc->collisionChannel,
            &x1, &y1, &z1,
            npc->moveSpeed * time,
            yaw,
            npc->collisionHeight,
            npc->collisionDiameter);

    if (fwdHit) {
        fwdHitDist = dist2D(npc->pos.x, npc->pos.z, x1, z1);

        // clockwise 'whisker' check
        x2 = npc->pos.x;
        y2 = npc->pos.y;
        z2 = npc->pos.z;
        if (npc_test_move_simple_with_slipping(npc->collisionChannel,
                &x2, &y2, &z2, npc->moveSpeed * time,
                clamp_angle(yaw + 35.0f),
                npc->collisionHeight,
                npc->collisionDiameter)) {
            cwHitDist = dist2D(npc->pos.x, npc->pos.z, x2, z2);
        }

        // counter-clockwise 'whisker' check
        x3 = npc->pos.x;
        y3 = npc->pos.y;
        z3 = npc->pos.z;
        if (npc_test_move_simple_with_slipping(npc->collisionChannel,
                &x3, &y3, &z3,
                npc->moveSpeed * time,
                clamp_angle(yaw - 35.0f),
                npc->collisionHeight,
                npc->collisionDiameter)) {
            ccwHitDist = dist2D(npc->pos.x, npc->pos.z, x3, z3);
        }

        if ((ccwHitDist < cwHitDist && cwHitDist < fwdHitDist) || (cwHitDist < ccwHitDist && ccwHitDist < fwdHitDist)) {
            // both whisker directions hit sooner than forward direction, make no adjustment
            yaw = npc->yaw;
        } else if ((ccwHitDist < fwdHitDist && fwdHitDist < cwHitDist) || (fwdHitDist < ccwHitDist && ccwHitDist < cwHitDist)) {
            // clockwise whisker hits furthest away, adjust toward that direction
            yaw = npc->yaw + 35.0f;
        } else if ((cwHitDist < fwdHitDist && fwdHitDist < ccwHitDist) || (fwdHitDist < cwHitDist && cwHitDist < ccwHitDist)) {
            // counter-clockwise whisker hits furthest away, adjust toward that direction
            yaw = npc->yaw - 35.0f;
        }
    }

    if (outYaw != nullptr) {
        *outYaw = clamp_angle(yaw);
    }
    if (outDistFwd != nullptr) {
        *outDistFwd = fwdHitDist;
    }
    if (outDistCW != nullptr) {
        *outDistCW = cwHitDist;
    }
    if (outDistCCW != nullptr) {
        *outDistCCW = ccwHitDist;
    }
    return fwdHit;
}

b32 is_point_outside_territory(s32 shape, f32 centerX, f32 centerZ, f32 pointX, f32 pointZ, f32 sizeX, f32 sizeZ) {
    f32 dx, dz;
    f32 dist;

    switch (shape) {
        case SHAPE_CYLINDER:
            dist = dist2D(centerX, centerZ, pointX, pointZ);
            return (sizeX < dist);
        case SHAPE_RECT:
            dx = fabsf(centerX - pointX);
            dz = fabsf(centerZ - pointZ);
            return ((sizeX < dx) || (sizeZ < dz));
        default:
            return false;
    }
}

ALWAYS_INLINE b32 is_point_outside_wander_territory(EnemyTerritoryWander* wander, f32 pointX, f32 pointZ) {
    return is_point_outside_territory(
        wander->wanderShape,
        wander->centerPos.x, wander->centerPos.z,
        pointX, pointZ,
        wander->wanderSize.x, wander->wanderSize.z
    );
}

ALWAYS_INLINE b32 is_point_outside_detect_volume(EnemyDetectVolume* detect, f32 pointX, f32 pointZ) {
    return is_point_outside_territory(
        detect->shape,
        detect->pointX, detect->pointZ,
        pointX, pointZ,
        detect->sizeX, detect->sizeZ
    );
}

b32 basic_ai_check_player_dist(EnemyDetectVolume* detect, Enemy* enemy, f32 radius, f32 fwdPosOffset, b8 useWorldYaw) {
    Npc* npc = get_npc_unsafe(enemy->npcID);
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus;
    f32 x, y, z;
    f32 dist;
    s32 skipCheckForPlayer;

    if (enemy->aiFlags & AI_FLAG_CANT_DETECT_PLAYER) {
        return false;
    }

    partnerStatus = &gPartnerStatus;
    if (partnerStatus->actingPartner == PARTNER_BOW && partnerStatus->partnerActionState
            && !(detect->detectFlags & AI_DETECT_FLAG_IGNORE_HIDING)) {
        return false;
    }

    if (partnerStatus->actingPartner == PARTNER_SUSHIE && partnerStatus->partnerActionState
            && !(detect->detectFlags & AI_DETECT_FLAG_IGNORE_HIDING)) {
        return false;
    }

    if (detect->skipPlayerDetectChance < 0) {
        return false;
    }

    if (detect->halfHeight <= fabsf(npc->pos.y - playerStatus->pos.y)
            && !(detect->detectFlags & AI_DETECT_FLAG_IGNORE_ELEVATION)) {
        return false;
    }

    if (((detect->sizeX != 0) || (detect->sizeZ != 0))
        && is_point_outside_detect_volume(detect, playerStatus->pos.x, playerStatus->pos.z)
    ) {
        return false;
    }

    if ((playerStatus->actionState == ACTION_STATE_USE_SPINNING_FLOWER)) {
        return false;
    }

    // check for unbroken line of sight
    if (enemy->aiDetectFlags & AI_DETECT_SIGHT) {
        x = npc->pos.x;
        y = npc->pos.y + npc->collisionHeight * 0.5;
        z = npc->pos.z;
        dist = dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
        if (npc_test_move_simple_with_slipping(COLLIDER_FLAG_IGNORE_PLAYER | COLLISION_IGNORE_ENTITIES,
                &x, &y, &z,
                dist, atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z),
                0.1f, 0.1f)) {
            return false;
        }
    }

    if (detect->skipPlayerDetectChance == 0) {
        skipCheckForPlayer = 0;
    } else {
        skipCheckForPlayer = rand_int(detect->skipPlayerDetectChance + 1);
    }

    if (skipCheckForPlayer == 0) {
        if (enemy->aiDetectFlags & AI_DETECT_MOTION_SENSITIVE) {
            if (playerStatus->actionState == ACTION_STATE_WALK) {
                radius *= 1.15;
            } else if (playerStatus->actionState == ACTION_STATE_RUN) {
                radius *= 1.3;
            }
        }
        x = npc->pos.x;
        z = npc->pos.z;
        if (useWorldYaw) {
            add_vec2D_polar(&x, &z, fwdPosOffset, npc->yaw);
        } else {
            add_vec2D_polar(&x, &z, fwdPosOffset, 270.0f - npc->renderYaw);
        }
        if (dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z) <= radius) {
            return true;
        }
    }

    return false;
}

b32 ai_check_player_dist(Enemy* enemy, s32 chance, f32 radius, f32 moveSpeed) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posZ;

    if (chance >= 0) {
        b32 skipCheckForPlayer;

        if (chance != 0) {
            skipCheckForPlayer = (rand_int(chance + 1) != 0);
        } else {
            skipCheckForPlayer = false;
        }

        if (!skipCheckForPlayer) {
            posX = npc->pos.x;
            posZ = npc->pos.z;
            add_vec2D_polar(&posX, &posZ, moveSpeed, 270.0f - npc->renderYaw);

            if (dist2D(posX, posZ, playerStatus->pos.x, playerStatus->pos.z) <= radius) {
                return true;
            }
        }
    }

    return false;
}

void ai_enemy_play_sound(Npc* npc, s32 soundID, s32 upperSoundFlags) {
    Enemy* enemy = get_enemy(npc->npcID);
    s32 soundFlags = (upperSoundFlags & SOUND_SPACE_PARAMS_MASK) | SOUND_SPACE_FULL;

    if (upperSoundFlags & 1) {
        soundFlags |= SOUND_PARAM_MUTE;
    }

    if (enemy->npcSettings->actionFlags & AI_ACTION_MUTE_OFFSCREEN) {
        soundFlags |= SOUND_PARAM_CLIP_OFFSCREEN_ANY;
    }

    sfx_play_sound_at_position(soundID, soundFlags, npc->pos.x, npc->pos.y, npc->pos.z);
}

void ai_try_set_state(Evt* script, s32 state) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = state;
    }
}

void basic_ai_wander_init(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    // chose a random direction and move time
    npc->duration = (settings->moveTime / 2) + rand_int((settings->moveTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(60) - 30.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    script->functionTemp[1] = 0;

    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = settings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }

    enemy->aiFlags &= ~AI_FLAG_NEEDS_HEADING;
    enemy->aiFlags &= ~AI_FLAG_OUTSIDE_TERRITORY;
    script->AI_TEMP_STATE = AI_STATE_WANDER;
}

void basic_ai_wander(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    EnemyTerritoryWander* wander = &enemy->territory->wander;
    b32 shouldReturn = false;
    f32 x, y, z;
    f32 yaw;

    // search for the player
    if (settings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = settings->playerSearchInterval;
            if (basic_ai_check_player_dist(detect, enemy, settings->alertRadius, settings->alertOffsetDist, false)) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
                if (!npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, settings->chaseSpeed, yaw, npc->collisionHeight, npc->collisionDiameter)) {
                    npc->yaw = yaw;
                    ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                    fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                    enemy->aiFlags &= ~AI_FLAG_NEEDS_HEADING;
                    enemy->aiFlags &= ~AI_FLAG_OUTSIDE_TERRITORY;

                    if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                        script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
                    } else {
                        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
                    }
                    return;
                }
            }
        }
        script->functionTemp[1]--;
    }

    // check if we've wandered beyond the boundary of the territory
    if (is_point_outside_wander_territory(&wander, npc->pos.x, npc->pos.z)
        && npc->moveSpeed < dist2D(wander->centerPos.x, wander->centerPos.z, npc->pos.x, npc->pos.z)
    ) {
        if (!(enemy->aiFlags & AI_FLAG_OUTSIDE_TERRITORY)) {
            enemy->aiFlags |= (AI_FLAG_OUTSIDE_TERRITORY | AI_FLAG_NEEDS_HEADING);
        }

        if (enemy->aiFlags & AI_FLAG_NEEDS_HEADING) {
            npc->yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, wander->centerPos.x, wander->centerPos.z));
            enemy->aiFlags &= ~AI_FLAG_NEEDS_HEADING;
        }

        // if current heading is deflected by a wall, recalculate yaw to continue pursuing centerPos
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;
        if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, 2.0 * npc->moveSpeed, npc->yaw, npc->collisionHeight, npc->collisionDiameter)) {
            yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, wander->centerPos.x, wander->centerPos.z));
            enemy->aiFlags &= ~AI_FLAG_NEEDS_HEADING;
            ai_check_fwd_collisions(npc, 5.0f, &yaw, nullptr, nullptr, nullptr);
            npc->yaw = yaw;
        }
        shouldReturn = true;
    } else if (enemy->aiFlags & AI_FLAG_OUTSIDE_TERRITORY) {
        enemy->aiFlags &= ~AI_FLAG_OUTSIDE_TERRITORY;
        enemy->aiFlags &= ~AI_FLAG_NEEDS_HEADING;
    }

    // perform the motion
    if ((wander->wanderSize.x != 0) || (wander->wanderSize.z != 0) || shouldReturn) {
        if (npc->turnAroundYawAdjustment == 0) {
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        } else {
            return;
        }
    }

    // decide to loiter or continue wandering
    if (settings->moveTime > 0) {
        npc->duration--;
        if (npc->duration <= 0) {
            script->AI_TEMP_STATE = AI_STATE_LOITER_INIT;
            script->functionTemp[1] = rand_int(1000) % 3 + 2;
            if (settings->loiterMode <= 0 || settings->waitTime <= 0) {
                script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
            }
        }
    }
}

void basic_ai_loiter_init(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (settings->waitTime / 2) + rand_int((settings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void basic_ai_loiter(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z;
    f32 yaw;

    if (settings->playerSearchInterval >= 0) {
        if (basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, false)) {
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
            if (!npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, settings->chaseSpeed, yaw, npc->collisionHeight, npc->collisionDiameter)) {
                npc->yaw = yaw;
                ai_enemy_play_sound(npc, SOUND_AI_ALERT_A, SOUND_PARAM_MORE_QUIET);
                fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
                if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                    script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
                } else {
                    script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
                }
                return;
            }
        }
    }

    // look around randomly
    if (npc->turnAroundYawAdjustment == 0) {
        npc->duration--;
        if (npc->duration <= 0) {
            script->functionTemp[1]--;
            if (script->functionTemp[1]) {
                if (!(enemy->npcSettings->actionFlags & AI_ACTION_LOOK_AROUND_DURING_LOITER)) {
                    npc->yaw = clamp_angle(npc->yaw + 180.0f);
                }
                npc->duration = (settings->waitTime / 2) + rand_int(settings->waitTime / 2 + 1);
                return;
            }
            script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
        }
    }
}

void basic_ai_found_player_jump_init(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    ai_enemy_play_sound(npc, SOUND_AI_FOUND_PLAYER_JUMP, 0);
    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_JUMP];
    npc->jumpVel = 10.0f;
    npc->jumpScale = 2.5f;
    npc->moveToPos.y = npc->pos.y;
    npc->flags |= NPC_FLAG_JUMPING;
    script->AI_TEMP_STATE = AI_STATE_ALERT;
}

void basic_ai_found_player_jump(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);
    b32 done = false;

    if (npc->jumpVel <= 0.0) {
        if (npc->pos.y <= npc->moveToPos.y) {
            npc->pos.y = npc->moveToPos.y;
            done = true;
        }
    }

    if (!done) {
        npc->pos.y += npc->jumpVel;
        npc->jumpVel -= npc->jumpScale;
    } else {
        npc->jumpVel = 0.0f;
        npc->flags &= ~NPC_FLAG_JUMPING;
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void basic_ai_chase_init(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    b32 skipTurnAround = false;

    switch(gPlayerStatusPtr->actionState) {
        case ACTION_STATE_JUMP:
        case ACTION_STATE_HOP:
        case ACTION_STATE_BOUNCE:
        case ACTION_STATE_FALLING:
            if (dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) < npc->collisionDiameter) {
                skipTurnAround = true;
            }
            break;
    }

    if (!skipTurnAround) {
        f32 angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z);
        f32 deltaAngleToPlayer = get_clamped_angle_diff(npc->yaw, angle);

        if (settings->chaseTurnRate < fabsf(deltaAngleToPlayer)) {
            if (deltaAngleToPlayer < 0.0f) {
                angle = npc->yaw - settings->chaseTurnRate;
            } else {
                angle = npc->yaw + settings->chaseTurnRate;
            }
        }
        npc->yaw = clamp_angle(angle);
        npc->duration = (settings->chaseUpdateInterval / 2) + rand_int((settings->chaseUpdateInterval / 2) + 1);
    } else {
        npc->duration = 0;
    }

    npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = settings->chaseSpeed;
    script->AI_TEMP_STATE = AI_STATE_CHASE;
}

void basic_ai_chase(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z;

    if (!basic_ai_check_player_dist(detect, enemy, settings->chaseRadius, settings->chaseOffsetDist, true)) {
        fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, nullptr);
        npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 20;
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
        return;
    }

    if (enemy->npcSettings->actionFlags & AI_ACTION_CHASE_REQUIRES_PATH) {
        if (dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->pos.x, gPlayerStatusPtr->pos.z) > (npc->moveSpeed * 5.0)) {
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, 1.0f, npc->yaw, npc->collisionHeight, npc->collisionDiameter)) {
                fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 12, nullptr);
                npc->curAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
                npc->duration = 15;
                script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
                return;
            }
        }
    }

    npc_surface_spawn_fx(npc, SURFACE_INTERACT_RUN);
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    if (npc->moveSpeed > 8.0 && !(gGameStatusPtr->frameCounter % 5)) {
        ai_enemy_play_sound(npc, SOUND_SMALL_NPC_STEP, 0);
    }

    if (npc->duration > 0) {
        npc->duration--;
    } else {
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void basic_ai_lose_player(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 0) {
        // turn to face home position
        npc->yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z));
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

API_CALLABLE(BasicAI_Main) {
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
    detect->halfHeight = 65.0f;
    detect->detectFlags = 0;

    if (isInitialCall || enemy->aiFlags & AI_FLAG_SUSPEND) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
        npc->duration = 0;

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
            script->AI_TEMP_STATE_AFTER_SUSPEND = AI_STATE_WANDER_INIT;
        } else if (enemy->flags & ENEMY_FLAG_BEGIN_WITH_CHASING) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }

        enemy->aiFlags &= ~AI_FLAG_SUSPEND;
        enemy->flags &= ~ENEMY_FLAG_BEGIN_WITH_CHASING;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_WANDER_INIT:
            basic_ai_wander_init(script, settings, detect);
            // fallthrough
        case AI_STATE_WANDER:
            basic_ai_wander(script, settings, detect);
            break;

        case AI_STATE_LOITER_INIT:
            basic_ai_loiter_init(script, settings, detect);
            // fallthrough
        case AI_STATE_LOITER:
            basic_ai_loiter(script, settings, detect);
            break;

        case AI_STATE_ALERT_INIT:
            basic_ai_found_player_jump_init(script, settings, detect);
            // fallthrough
        case AI_STATE_ALERT:
            basic_ai_found_player_jump(script, settings, detect);
            break;

        case AI_STATE_CHASE_INIT:
            basic_ai_chase_init(script, settings, detect);
            // fallthrough
        case AI_STATE_CHASE:
            basic_ai_chase(script, settings, detect);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }
            // fallthrough
        case AI_STATE_LOSE_PLAYER:
            basic_ai_lose_player(script, settings, detect);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
