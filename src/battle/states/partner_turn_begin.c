#include "states.h"
#include "effects.h"

enum {
    // BTL_SUBSTATE_INIT                = 0,
    BTL_SUBSTATE_AWAIT_RECOVER_DONE     = 1,
    BTL_SUBSTATE_EXEC_TURN_SCRIPT       = 8,
    BTL_SUBSTATE_AWAIT_TURN_SCRIPT      = 9,
    BTL_SUBSTATE_END_DELAY              = 10,
    BTL_SUBSTATE_RESET_STATE            = 100,
};

void btl_state_update_begin_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemy;
    Evt* script;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        if (partner == NULL) {
            D_8029F254 = TRUE;
            gBattleSubState = BTL_SUBSTATE_END_DELAY;
        } else if ((battleStatus->flags2 & (BS_FLAGS2_PARTNER_TURN_USED | BS_FLAGS2_PLAYER_TURN_USED)) != (BS_FLAGS2_PARTNER_TURN_USED | BS_FLAGS2_PLAYER_TURN_USED)) {
            if (!(partner->flags & ACTOR_FLAG_NO_ATTACK)) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(5);
                gBattleSubState = BTL_SUBSTATE_RESET_STATE;
            } else {
                btl_set_state(BATTLE_STATE_9);
                return;
            }
        } else {
            btl_set_state(BATTLE_STATE_9);
            return;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_RESET_STATE) {
        if (btl_cam_is_moving_done()) {
            D_8029F258 = 0;
            reset_actor_turn_info();
            partner = battleStatus->partnerActor;
            battleStatus->actionResult = ACTION_RESULT_NONE;
            battleStatus->blockResult = BLOCK_RESULT_NONE;
            D_8029F254 = FALSE;
            gBattleStatus.flags1 |= BS_FLAGS1_PARTNER_ACTING;
            gBattleStatus.flags2 |= BS_FLAGS1_PLAYER_IN_BACK;
            partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;

            if (partner->koStatus != 0) {
                partner->koDuration--;
                D_8029F254 = TRUE;
                D_8029F258 = 20;
                if (partner->koDuration > 0) {
                    partner->disableEffect->data.disableX->koDuration = partner->koDuration;
                } else {
                    partner->koStatus = 0;
                    dispatch_event_partner(EVENT_RECOVER_FROM_KO);
                    partner->disableEffect->data.disableX->koDuration = 0;
                    gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                }
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVER_DONE;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_AWAIT_RECOVER_DONE:
            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                return;
            }
            gBattleSubState = BTL_SUBSTATE_EXEC_TURN_SCRIPT;
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_EXEC_TURN_SCRIPT) {
        if (partner->handlePhaseSource != NULL) {
            battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
            script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
            partner->handlePhaseScript = script;
            partner->handleBatttlePhaseScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
        }
        gBattleSubState = BTL_SUBSTATE_AWAIT_TURN_SCRIPT;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_TURN_SCRIPT) {
        if (partner->handlePhaseSource == NULL || !does_script_exist(partner->handleBatttlePhaseScriptID)) {
            gBattleSubState = BTL_SUBSTATE_END_DELAY;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_DELAY) {
        if (D_8029F258 != 0) {
            D_8029F258--;
            return;
        }
        gBattleStatus.flags2 &= ~BS_FLAGS2_NO_PLAYER_PAL_ADJUST;
        if (!D_8029F254) {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
        } else {
            gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
            btl_set_state(BATTLE_STATE_9);
        }
    }
}

void btl_state_draw_begin_partner_turn(void) {
}
