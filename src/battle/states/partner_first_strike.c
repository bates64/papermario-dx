#include "states.h"
#include "battle/battle.h"

enum {
    // BTL_SUBSTATE_INIT                = 0,
    BTL_SUBSTATE_AWAIT_ENEMY_READY      = 1,
    BTL_SUBSTATE_AWAIT_SCRIPTS          = 2,
    BTL_SUBSTATE_AWAIT_ENEMY_DONE       = 3,
};

void btl_state_update_partner_striking_first(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    s32 enemyNotDone;
    SelectableTarget* target;
    Evt* script;
    s32 level;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            D_8029F254 = FALSE;
            // setup dummy 'menu selection' for partner move
            level = partner->actorBlueprint->level;
            switch (gPlayerData.curPartner) {
                case PARTNER_KOOPER:
                    battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                    battleStatus->moveArgument = 0;
                    battleStatus->selectedMoveID = level + MOVE_SHELL_TOSS1;
                    battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    break;
                case PARTNER_BOMBETTE:
                    battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                    battleStatus->moveArgument = 0;
                    battleStatus->selectedMoveID = level + MOVE_BODY_SLAM1;
                    battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    break;
            }
            // let the enemy know a first strike is coming
            actor = get_actor(ACTOR_ENEMY0);
            if (actor->handleEventSource != NULL) {
                actor->lastEventType = EVENT_BEGIN_FIRST_STRIKE;
                script = start_script(actor->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                actor->handleEventScript = script;
                actor->handleEventScriptID = script->id;
                script->owner1.actorID = actor->actorID;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_READY;
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_READY:
            create_current_pos_target_list(partner);
            target = &partner->targetData[partner->targetIndexList[0]];
            partner->targetActorID = target->actorID;
            partner->targetPartID = target->partID;
            battleStatus->stateFreezeCount = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            gBattleStatus.flags2 |= BS_FLAGS2_IS_FIRST_STRIKE;
            gBattleStatus.flags1 |= BS_FLAGS1_PARTNER_ACTING;
            increment_status_bar_disabled();
            btl_cam_use_preset(BTL_CAM_MIDPOINT_CLOSE);
            btl_cam_target_actor(ACTOR_PARTNER);
            reset_actor_turn_info();
            // begin the partner turn script
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
            partner->takeTurnScript = script;
            partner->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            BattleSubstateDelay = 3;
            gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_AWAIT_SCRIPTS:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                D_8029F254 = TRUE;
            }
            // wait for partner move script
            if (partner->takeTurnScript != NULL && does_script_exist(partner->takeTurnScriptID)) {
                break;
            }
            partner->takeTurnScript = NULL;
            // wait for partner handle event script
            if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                break;
            }
            partner->handleEventScript = NULL;
            // wait for player handle event script
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for all enemy turn scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->takeTurnScript != NULL) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->takeTurnScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            // wait for all enemy handle event scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handleEventScript != NULL) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            if (battleStatus->stateFreezeCount == 0) {
                decrement_status_bar_disabled();
                if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                    return;
                }

                actor = get_actor(partner->targetActorID);
                if (actor != NULL) {
                    if (actor->handleEventSource != NULL) {
                        actor->lastEventType = EVENT_END_FIRST_STRIKE;
                        script = start_script(actor->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                        actor->handleEventScript = script;
                        actor->handleEventScriptID = script->id;
                        script->owner1.actorID = actor->actorID;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_DONE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_DONE:
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handleEventScript != NULL) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->handleEventScript = NULL;
                    }
                }
            }
            if (!enemyNotDone) {
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_partner_striking_first(void) {
    if (D_8029F254) {
        if (BattleScreenFadeAmt == 0) {
            set_screen_overlay_params_front(OVERLAY_NONE, -1.0f);
        } else {
            BattleScreenFadeAmt -= 20;
            if (BattleScreenFadeAmt < 0) {
                BattleScreenFadeAmt = 0;
            }

            set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, BattleScreenFadeAmt);
        }
    }
}
