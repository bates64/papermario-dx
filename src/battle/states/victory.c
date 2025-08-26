#include "states.h"
#include "script_api/battle.h"

enum {
    BTL_SUBSTATE_CHECK_OUTTA_SIGHT                  = 0,
    BTL_SUBSTATE_AWAIT_OUTTA_SIGHT                  = 1,
    BTL_SUBSTATE_CHECK_MERLEE                       = 2,
    BTL_SUBSTATE_AWAIT_MERLEE                       = 3,
    BTL_SUBSTATE_DONE                               = 4,
    BTL_SUBSTATE_RECOVER_STATUS                     = 5,
    BTL_SUBSTATE_AWAIT_RECOVER_KO                   = 10,
    BTL_SUBSTATE_CHECK_SWAP                         = 11,
    BTL_SUBSTATE_AWAIT_SWAP                         = 12,
};

void btl_state_update_victory(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_OUTTA_SIGHT:
            player->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            }

            battleStatus->stateFreezeCount = 0;
            if (battleStatus->outtaSightActive == 0) {
                gBattleSubState = BTL_SUBSTATE_RECOVER_STATUS;
            } else {
                if (battleStatus->outtaSightActive > 0) {
                    D_8029F254 = TRUE;
                }
                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                partner->handlePhaseScript = script;
                partner->handleBatttlePhaseScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
                gBattleSubState = BTL_SUBSTATE_AWAIT_OUTTA_SIGHT;
            }

            break;
        case BTL_SUBSTATE_AWAIT_OUTTA_SIGHT:
            if (!does_script_exist(partner->handleBatttlePhaseScriptID)) {
                battleStatus->outtaSightActive = 0;
                gBattleSubState = BTL_SUBSTATE_RECOVER_STATUS;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_RECOVER_STATUS:
            player->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            }
            gBattleSubState = BTL_SUBSTATE_CHECK_SWAP;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;

            gBattleStatus.flags1 &= ~BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
            if (player->koStatus == STATUS_KEY_DAZE) {
                dispatch_event_player(EVENT_RECOVER_FROM_KO);
                gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVER_KO;
            }
            player->debuff = 0;
            player->staticStatus = 0;
            player->stoneStatus = 0;
            player->transparentStatus = 0;
            player->koStatus = 0;
            player->koDuration = 0;
            player->disableEffect->data.disableX->koDuration = 0;

            if (partner != NULL) {
                if (partner->koStatus == STATUS_KEY_DAZE) {
                    dispatch_event_partner(EVENT_RECOVER_FROM_KO);
                    gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVER_KO;
                }
                partner->debuff = 0;
                partner->staticStatus = 0;
                partner->stoneStatus = 0;
                partner->transparentStatus = 0;
                partner->koStatus = 0;
                partner->koDuration = 0;
                partner->disableEffect->data.disableX->koDuration = 0;
            }
            break;
        case BTL_SUBSTATE_AWAIT_RECOVER_KO:
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }
            gBattleSubState = BTL_SUBSTATE_CHECK_SWAP;
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_CHECK_SWAP) {
        if (partner == NULL || !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK)) {
            gBattleSubState = BTL_SUBSTATE_CHECK_MERLEE;
        } else {
            partner->state.curPos.x = partner->curPos.x;
            partner->state.curPos.z = partner->curPos.z;
            partner->state.goalPos.x = player->curPos.x;
            partner->state.goalPos.z = player->curPos.z;
            partner->state.moveTime = 4;
            partner->state.angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_AWAIT_SWAP;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_SWAP) {
        if (partner->state.moveTime != 0) {
            partner->curPos.x += (partner->state.goalPos.x - partner->curPos.x) / partner->state.moveTime;
            partner->curPos.z += (partner->state.goalPos.z - partner->curPos.z) / partner->state.moveTime;
            player->curPos.x += (partner->state.curPos.x - player->curPos.x) / partner->state.moveTime;
            player->curPos.z += (partner->state.curPos.z - player->curPos.z) / partner->state.moveTime;
        }
        partner->curPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(-partner->state.angle);
        player->curPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(-partner->state.angle);
        partner->state.angle += 90.0f;

        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->curPos.x = partner->state.goalPos.x;
            partner->curPos.z = partner->state.goalPos.z;
            player->curPos.x = partner->state.curPos.x;
            player->curPos.z = partner->state.curPos.z;
            partner->homePos.x = partner->curPos.x;
            partner->homePos.z = partner->curPos.z;
            player->homePos.x = player->curPos.x;
            player->homePos.z = player->curPos.z;
            gBattleSubState = BTL_SUBSTATE_CHECK_MERLEE;
            gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_CHECK_MERLEE) {
        btl_cam_use_preset(BTL_CAM_DEFAULT);
        if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_EXP_BOOST) {
            if (battleStatus->totalStarPoints == 0) {
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
                gPlayerData.merleeTurnCount = 0;
                gPlayerData.merleeCastsLeft++;
            } else {
                battleStatus->battlePhase = PHASE_MERLEE_EXP_BONUS;
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
            }
        }
        gBattleSubState = BTL_SUBSTATE_AWAIT_MERLEE;
        BattleSubstateDelay = 0;
        gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_MERLEE) {
        if (BattleSubstateDelay != 0) {
            BattleSubstateDelay--;
        } else {
            if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
                player->takeTurnScript = NULL;
                if (battleStatus->nextMerleeSpellType != MERLEE_SPELL_EXP_BOOST) {
                    gBattleSubState = BTL_SUBSTATE_DONE;
                } else {
                    battleStatus->incrementStarPointDelay = 20;
                    battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
                    gBattleSubState = BTL_SUBSTATE_DONE;
                    battleStatus->pendingStarPoints = battleStatus->totalStarPoints
                                            + battleStatus->pendingStarPoints + battleStatus->pendingStarPoints;
                }
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        if (battleStatus->pendingStarPoints <= 0) {
            if (gBattleStatus.flags1 & BS_FLAGS1_STAR_POINTS_DROPPED) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_BATTLE_FLED;
            }
            if (gPlayerData.battlesWon < 9999) {
                gPlayerData.battlesWon++;
            }
            if (gBattleStatus.flags1 & BS_FLAGS1_BATTLE_FLED) {
                gCurrentEncounter.battleOutcome = OUTCOME_ENEMY_FLED;
            } else {
                gCurrentEncounter.battleOutcome = OUTCOME_PLAYER_WON;
            }
            if (gBattleStatus.flags1 & BS_FLAGS1_DISABLE_CELEBRATION) {
                if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                    bgm_set_song(0, -1, 0, 1500, 8);
                }
                btl_set_state(BATTLE_STATE_END_BATTLE);
            } else {
                btl_set_state(BATTLE_STATE_CELEBRATION);
            }
        }
    }
}

void btl_state_draw_victory(void) {
}
