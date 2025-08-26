#include "states.h"

enum {
    BTL_SUBSTATE_EXECUTE                        = 0,
    BTL_SUBSTATE_UNUSED_1                       = 1,
    BTL_SUBSTATE_AWAIT_SCRIPTS                  = 2,
    BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE        = 11, // wait for popups regarding player status to finish
    BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY        = 12, // a brief delay after the popup vanishes
    BTL_SUBSTATE_CHECK_PARTNER                  = 20,
    BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE       = 21, // wait for popups regarding partner status to finish
    BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY       = 22, // a brief delay after the popup vanishes
    BTL_SUBSTATE_DONE                           = 30,
};

void btl_state_update_enemy_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Actor* enemy;
    s32 i;

    Evt* script;
    s32 messageIndex;
    s32 waitingForEnemyScript;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_EXECUTE:
        case BTL_SUBSTATE_UNUSED_1:
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            gBattleStatus.flags1 &= ~BS_FLAGS1_YIELD_TURN;
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
            battleStatus->stateFreezeCount = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->actionQuality = 0;
            battleStatus->actionResult = ACTION_RESULT_NONE;
            battleStatus->blockResult = BLOCK_RESULT_NONE;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            reset_actor_turn_info();
            gBattleStatus.flags1 |= BS_FLAGS1_EXECUTING_MOVE;
            player->statusAfflicted = 0;
            if (partner != NULL) {
                partner->statusAfflicted = 0;
            }

            gBattleStatus.flags2 |= BS_FLAGS2_IGNORE_DARKNESS;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    if (!(enemy->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                        enemy->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                    }
                }
            }

            enemy = battleStatus->curTurnEnemy;
            if (!(enemy->flags & ACTOR_FLAG_NO_ATTACK)) {
                reset_all_actor_sounds(enemy);
                battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
                script = start_script(enemy->takeTurnSource, EVT_PRIORITY_A, 0);
                enemy->takeTurnScript = script;
                enemy->takeTurnScriptID = script->id;
                script->owner1.actorID = battleStatus->activeEnemyActorID;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_AWAIT_SCRIPTS:
            if (player->takeTurnScript != NULL && does_script_exist(player->takeTurnScriptID)) {
                break;
            }
            player->takeTurnScript = NULL;

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

            waitingForEnemyScript = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        waitingForEnemyScript = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }

            if (waitingForEnemyScript) {
                break;
            }

            if (btl_check_player_defeated()) {
                return;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->takeTurnScript != NULL) {
                    if (does_script_exist(enemy->takeTurnScriptID)) {
                        waitingForEnemyScript = TRUE;
                    } else {
                        enemy->takeTurnScript = NULL;
                    }
                }
            }

            if (waitingForEnemyScript && !(gBattleStatus.flags1 & BS_FLAGS1_YIELD_TURN)) {
                break;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_EXECUTING_MOVE;
            gBattleStatus.flags2 &= ~BS_FLAGS2_IGNORE_DARKNESS;
            if (btl_check_enemies_defeated()) {
                return;
            }

            if (battleStatus->stateFreezeCount != 0) {
                break;
            }

            if (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED) {
                btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
            } else {
                btl_update_ko_status();
                if (player->statusAfflicted != 0) {
                    player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    if (partner != NULL) {
                        partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    }
                    btl_cam_use_preset(BTL_CAM_PLAYER_STATUS_AFFLICTED);

                    switch (player->statusAfflicted) {
                        case STATUS_KEY_DIZZY:
                            messageIndex = BTL_MSG_PLAYER_DAZED;
                            break;
                        case STATUS_KEY_SLEEP:
                            messageIndex = BTL_MSG_PLAYER_ASLEEP;
                            break;
                        case STATUS_KEY_FROZEN:
                            messageIndex = BTL_MSG_PLAYER_FROZEN;
                            break;
                        case STATUS_KEY_POISON:
                            messageIndex = BTL_MSG_PLAYER_POISONED;
                            break;
                        case STATUS_KEY_SHRINK:
                            messageIndex = BTL_MSG_PLAYER_SHRUNK;
                            break;
                        case STATUS_KEY_PARALYZE:
                            messageIndex = BTL_MSG_PLAYER_PARALYZED;
                            break;
                        default:
                            messageIndex = 0;
                            gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                            break;
                    }
                    btl_show_battle_message(messageIndex, 60);
                    player->statusAfflicted = 0;
                    gBattleSubState = BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE;
                    break;
                } else {
                    gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                    break;
                }
            }
            break;
        case BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                break;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_PARTNER:
            if (partner != NULL) {
                if (partner->statusAfflicted == STATUS_KEY_DAZE) {
                    player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    btl_cam_use_preset(BTL_CAM_PARTNER_INJURED);
                    btl_show_battle_message(BTL_MSG_PARTNER_INJURED, 60);
                    partner->statusAfflicted = 0;
                    gBattleSubState = BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE;
                } else {
                    gBattleSubState = BTL_SUBSTATE_DONE;
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_enemy_move(void) {
}
