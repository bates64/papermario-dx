#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_AWAIT_ENEMY_READY          = 1,
    BTL_SUBSTATE_AWAIT_SCRIPTS              = 2,
    BTL_SUBSTATE_AWAIT_ENEMY_DONE           = 3,
};

void btl_merlee_on_first_strike(void);

void btl_state_update_first_strike(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Evt* script;
    Actor* enemy;
    s32 enemyNotDone;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            D_8029F254 = FALSE;
            btl_merlee_on_first_strike();
            if (playerData->playerFirstStrikes < 9999) {
                playerData->playerFirstStrikes++;
            }

            // clear rush flags to initialize
            battleStatus->rushFlags = RUSH_FLAG_NONE;
            gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;

            // set rush flags based on danger/peril status
            if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
                if (playerData->curHP <= PERIL_THRESHOLD && is_ability_active(ABILITY_MEGA_RUSH)) {
                    gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                    battleStatus->rushFlags |= RUSH_FLAG_MEGA;
                }
                if (playerData->curHP <= DANGER_THRESHOLD && is_ability_active(ABILITY_POWER_RUSH)) {
                    if (!(battleStatus->rushFlags & RUSH_FLAG_MEGA)) {
                        gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                        battleStatus->rushFlags |= RUSH_FLAG_POWER;
                    }
                }
            }

            // setup dummy 'menu selection' for player move
            switch (encounterStatus->hitType) {
                case ENCOUNTER_TRIGGER_JUMP:
                    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
                    battleStatus->selectedMoveID = MOVE_FIRST_STRIKE_JUMP;
                    battleStatus->moveArgument = encounterStatus->hitTier;
                    battleStatus->curTargetListFlags = gMoveTable[MOVE_FIRST_STRIKE_JUMP].flags;
                    break;
                case ENCOUNTER_TRIGGER_HAMMER:
                    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
                    battleStatus->selectedMoveID = MOVE_FIRST_STRIKE_HAMMER;
                    battleStatus->moveArgument = encounterStatus->hitTier;
                    battleStatus->curTargetListFlags = gMoveTable[MOVE_FIRST_STRIKE_HAMMER].flags;
                    break;
                case ENCOUNTER_TRIGGER_PARTNER:
                    btl_set_state(BATTLE_STATE_PARTNER_FIRST_STRIKE);
                    return;
            }
            // let the enemy know a first strike is coming
            enemy = get_actor(ACTOR_ENEMY0);
            if (enemy->handleEventSource != NULL) {
                enemy->lastEventType = EVENT_BEGIN_FIRST_STRIKE;
                script = start_script(enemy->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                enemy->handleEventScript = script;
                enemy->handleEventScriptID = script->id;
                script->owner1.actorID = enemy->actorID;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_READY;
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_READY:
            enemy = get_actor(ACTOR_ENEMY0);
            if (enemy->handleEventSource != NULL) {
                if (does_script_exist(enemy->handleEventScriptID)) {
                    break;
                } else {
                    enemy->handleEventScript = NULL;
                }
            }

            func_80263230(player, enemy);
            battleStatus->stateFreezeCount = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            gBattleStatus.flags2 |= BS_FLAGS2_IS_FIRST_STRIKE;
            gBattleStatus.flags1 &= ~BS_FLAGS1_PARTNER_ACTING;
            increment_status_bar_disabled();
            btl_cam_use_preset(BTL_CAM_MIDPOINT_CLOSE);
            btl_cam_target_actor(ACTOR_PLAYER);
            reset_actor_turn_info();
            // begin the player turn script
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            BattleSubstateDelay = 3;
            gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_AWAIT_SCRIPTS:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                D_8029F254 = TRUE;
            }

            // wait for player move script
            if (!(gBattleStatus.flags1 & BS_FLAGS1_YIELD_TURN)) {
                if (player->takeTurnScript != NULL && does_script_exist(player->takeTurnScriptID)) {
                    break;
                }
                player->takeTurnScript = NULL;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_EXECUTING_MOVE;

            // wait for player handle event script
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for partner handle event script
            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            // wait for all enemy turn scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->takeTurnScript != NULL) {
                    if (does_script_exist(enemy->takeTurnScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->takeTurnScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            // wait for all enemy handle event scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            if (battleStatus->stateFreezeCount == 0) {
                decrement_status_bar_disabled();
                if (!(gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED)) {
                    Actor* target;

                    if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                        return;
                    }

                    target = get_actor(player->targetActorID);
                    if (target != NULL) {
                        if (target->handleEventSource != NULL) {
                            target->lastEventType = EVENT_END_FIRST_STRIKE;
                            script = start_script(target->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                            target->handleEventScript = script;
                            target->handleEventScriptID = script->id;
                            script->owner1.actorID = target->actorID;
                        }
                    }
                    gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_DONE;
                } else {
                    btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                }
            }
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_DONE:
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }
            if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
                player->takeTurnScript = NULL;
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_first_stike(void) {
    if (D_802809F6 == -1 && D_8029F254) {
        if (BattleScreenFadeAmt == 0) {
            set_screen_overlay_params_front(OVERLAY_NONE, -1.0f);
        } else {
            if (!(gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED)) {
                BattleScreenFadeAmt -= 20;
            } else {
                BattleScreenFadeAmt -= 50;
            }

            if (BattleScreenFadeAmt < 0) {
                BattleScreenFadeAmt = 0;
            }
            set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, BattleScreenFadeAmt);
        }
    }
}
