#include "states.h"
#include "effects.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT            = 0,
    BTL_SUBSTATE_9_1                = 1,
    BTL_SUBSTATE_9_2                = 2,
    BTL_SUBSTATE_9_3                = 3,
    BTL_SUBSTATE_9_4                = 4,
    BTL_SUBSTATE_9_5                = 5,
    BTL_SUBSTATE_9_6                = 6,
    BTL_SUBSTATE_9_7                = 7,
};

void btl_state_update_9(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    ActorState* state;
    Evt* script;
    s32 waitingForScript;
    s32 i;

    s32 oldKoDuration;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PLAYER_TURN_USED)) {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
            return;
        }

        if (partner != NULL) {
            if (!(gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED) && !(partner->flags & ACTOR_FLAG_NO_ATTACK)) {
                btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
                return;
            }
        }

        player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
        player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        if (partner != NULL) {
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        }

        gBattleSubState = BTL_SUBSTATE_9_1;
        D_8029F258 = 0;
        gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
        gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
    }

    if (gBattleSubState == BTL_SUBSTATE_9_1) {
        waitingForScript = FALSE;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handleEventScript != NULL) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    waitingForScript = TRUE;
                } else {
                    actor->handleEventScript = NULL;
                }
            }
        }

        if (!waitingForScript) {
            reset_actor_turn_info();

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags |= ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS;
                    actor->flags &= ~ACTOR_FLAG_SKIP_TURN;

                    if (actor->debuff != 0) {
                        if (actor->debuff == STATUS_KEY_FEAR
                            || actor->debuff == STATUS_KEY_DIZZY
                            || actor->debuff == STATUS_KEY_PARALYZE
                            || actor->debuff == STATUS_KEY_SLEEP
                            || actor->debuff == STATUS_KEY_FROZEN
                            || actor->debuff == STATUS_KEY_STOP
                        ) {
                            actor->flags |= ACTOR_FLAG_SKIP_TURN;
                        }
                        actor->debuffDuration--;
                        if (actor->debuffDuration <= 0) {
                            actor->debuff = 0;
                            remove_status_debuff(actor->hudElementDataIndex);
                            dispatch_event_actor(actor, EVENT_RECOVER_STATUS);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->staticStatus != 0) {
                        actor->staticDuration--;
                        if (actor->staticDuration <= 0) {
                            actor->staticStatus = 0;
                            remove_status_static(actor->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->transparentStatus != 0) {
                        actor->transparentDuration--;
                        if (actor->transparentDuration <= 0) {
                            actor->transparentStatus = 0;
                            remove_status_transparent(actor->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->stoneStatus != 0) {
                        actor->stoneDuration--;
                        if (actor->stoneDuration <= 0) {
                            actor->stoneStatus = 0;
                            D_8029F258 = 20;
                        }
                    }

                    oldKoDuration = actor->koDuration;
                    actor->koDuration = actor->debuffDuration;
                    if (actor->koDuration > 0) {
                        actor->koStatus = STATUS_KEY_DAZE;
                        actor->disableEffect->data.disableX->koDuration = actor->koDuration;
                    } else if (oldKoDuration != actor->koDuration) {
                        actor->koStatus = 0;
                        actor->disableEffect->data.disableX->koDuration = 0;
                    }
                    if (actor->debuff == STATUS_KEY_POISON) {
                        gBattleStatus.flags1 |= BS_FLAGS1_TRIGGER_EVENTS;
                        dispatch_damage_event_actor_0(actor, 1, EVENT_HIT);
                        D_8029F258 = 20;
                    }
                }
            }
            gBattleSubState = BTL_SUBSTATE_9_2;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_2) {
        // wait for player HandleEvent script to finish
        if(player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
            goto WAITING;
        }
        player->handleEventScript = NULL;

        // wait for partner HandleEvent script to finish
        if (partner != NULL) {
            if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                goto WAITING;
            }
            partner->handleEventScript = NULL;
        }

        // wait for all enemy HandleEvent scripts to finish
        waitingForScript = FALSE;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handleEventScript != NULL) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    waitingForScript = TRUE;
                } else {
                    actor->handleEventScript = NULL;
                }
            }
        }

        if (waitingForScript) {
            goto WAITING;
        }

        if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
            return;
        }

        btl_cam_use_preset(BTL_CAM_DEFAULT);
        if (partner == NULL || !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK)) {
            gBattleSubState = BTL_SUBSTATE_9_4;
        } else if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
            gBattleSubState = BTL_SUBSTATE_9_4;
        } else {
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            state = &partner->state;
            if (!battleStatus->outtaSightActive) {
                partner->state.curPos.x = partner->homePos.x;
                partner->state.curPos.z = partner->homePos.z;
                partner->state.goalPos.x = player->homePos.x;
                partner->state.goalPos.z = player->homePos.z;
            } else {
                partner->state.curPos.x = partner->homePos.x;
                partner->state.curPos.z = partner->homePos.z;
                partner->state.goalPos.x = partner->homePos.x;
                partner->state.goalPos.z = partner->homePos.z + 5.0f;
                partner->homePos.x = player->homePos.x;
                partner->homePos.z = player->homePos.z;
            }
            state->moveTime = 4;
            state->angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_9_3;
        }
    }
    WAITING:

    if (gBattleSubState == BTL_SUBSTATE_9_3) {
        if (partner->state.moveTime != 0) {
            partner->curPos.x += (partner->state.goalPos.x - partner->curPos.x) / partner->state.moveTime;
            partner->curPos.z += (partner->state.goalPos.z - partner->curPos.z) / partner->state.moveTime;
            player->curPos.x += (partner->state.curPos.x - player->curPos.x) / partner->state.moveTime;
            player->curPos.z += (partner->state.curPos.z - player->curPos.z) / partner->state.moveTime;
        }
        partner->curPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(partner->state.angle);
        player->curPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(partner->state.angle);
        partner->state.angle += 90.0f;

        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->curPos.x = partner->state.goalPos.x;
            partner->curPos.z = partner->state.goalPos.z;
            player->curPos.x = partner->state.curPos.x;
            player->curPos.z = partner->state.curPos.z;
            if (!battleStatus->outtaSightActive) {
                partner->homePos.x = partner->curPos.x;
                partner->homePos.z = partner->curPos.z;
                player->homePos.x = player->curPos.x;
                player->homePos.z = player->curPos.z;
            } else {
                player->homePos.x = player->curPos.x;
                player->homePos.z = player->curPos.z;
            }
            gBattleSubState = BTL_SUBSTATE_9_4;
            gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_4) {
        if (D_8029F258 != 0) {
            D_8029F258--;
        } else {
            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_DEF_BOOST) {
                battleStatus->merleeDefenseBoost = 3;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
                battleStatus->battlePhase = PHASE_MERLEE_DEFENSE_BONUS;
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
            }
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            }
            gBattleSubState = BTL_SUBSTATE_9_5;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_5) {
        if (player->takeTurnScript == NULL || (does_script_exist(player->takeTurnScriptID) == 0)) {
            player->takeTurnScript = NULL;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handlePhaseSource != NULL) {
                    battleStatus->battlePhase = PHASE_PLAYER_END;
                    script = start_script(actor->handlePhaseSource, EVT_PRIORITY_A, 0);
                    actor->handlePhaseScript = script;
                    actor->handleBatttlePhaseScriptID = script->id;
                    script->owner1.enemyID = i | ACTOR_CLASS_ENEMY;
                }
            }
            gBattleSubState = BTL_SUBSTATE_9_6;
        }
    }

    waitingForScript = FALSE;
    if (gBattleSubState == BTL_SUBSTATE_9_6) {
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handlePhaseSource != NULL && does_script_exist(actor->handleBatttlePhaseScriptID)) {
                waitingForScript = TRUE;
            }
        }
        if (!waitingForScript) {
            gBattleSubState = BTL_SUBSTATE_9_7;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_7) {
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_9(void) {
}
