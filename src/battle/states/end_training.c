#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_AWAIT_RECOVERING           = 10,
    BTL_SUBSTATE_CHECK_OUTTA_SIGHT          = 11,
    BTL_SUBSTATE_AWAIT_OUTTA_SIGHT          = 12,
    BTL_SUBSTATE_RESET_CAM                  = 13,
    BTL_SUBSTATE_DONE                       = 14,
};

void btl_state_update_end_training_battle(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            player->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
            }
            gBattleSubState = BTL_SUBSTATE_CHECK_OUTTA_SIGHT;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;

            if (player->koStatus == STATUS_KEY_DAZE) {
                dispatch_event_player(EVENT_RECOVER_FROM_KO);
                gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVERING;
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
                    gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVERING;
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
        case BTL_SUBSTATE_AWAIT_RECOVERING:
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

            gBattleSubState = BTL_SUBSTATE_CHECK_OUTTA_SIGHT;
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_OUTTA_SIGHT:
            battleStatus->stateFreezeCount = 0;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;

            if (!battleStatus->outtaSightActive) {
                gBattleSubState = BTL_SUBSTATE_RESET_CAM;
            } else {
                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                partner->handlePhaseScript = script;
                partner->handlePhaseScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
                gBattleSubState = BTL_SUBSTATE_AWAIT_OUTTA_SIGHT;
            }
            break;
        case BTL_SUBSTATE_AWAIT_OUTTA_SIGHT:
            if (!does_script_exist(partner->handlePhaseScriptID)) {
                battleStatus->outtaSightActive = FALSE;
                gBattleSubState = BTL_SUBSTATE_RESET_CAM;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_RESET_CAM:
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            BattleSubstateDelay = 30;
            gBattleSubState = BTL_SUBSTATE_DONE;
            break;
        case BTL_SUBSTATE_DONE:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
                return;
            }
            if (playerData->trainingsDone < 9999) {
                playerData->trainingsDone++;
            }
            encounterStatus->battleOutcome = OUTCOME_ENEMY_FLED;
            if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                bgm_set_song(0, -1, 0, 1500, 8);
            }
            btl_set_state(BATTLE_STATE_END_BATTLE);
            break;
    }
}

void btl_state_draw_end_training_battle(void) {
}
