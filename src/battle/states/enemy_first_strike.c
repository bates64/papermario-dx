#include "states.h"

enum {
    // BTL_SUBSTATE_INIT            = 0,
    BTL_SUBSTATE_AWAIT              = 2,
};

void btl_state_update_enemy_striking_first(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;
    Actor* actor;
    u16* enemyIDs;
    s16 activeEnemyActorID;
    s32 nextEnemyIdx;
    s32 count;
    s32 flags;
    s32 waitingForScript;
    s32 i;
    s32 j;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            gPlayerData.enemyFirstStrikes++;
            battleStatus->stateFreezeCount = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            battleStatus->flags1 &= ~BS_FLAGS1_MENU_OPEN;
            BattleCanShowFirstStrike = FALSE;
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
            battleStatus->flags2 |= BS_FLAGS2_IS_FIRST_STRIKE;
            battleStatus->flags2 |= BS_FLAGS2_IGNORE_DARKNESS;
            count = 0;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    battleStatus->enemyIDs[count] = i | ACTOR_ENEMY0;
                    count++;
                }
            }

            battleStatus->numEnemyActors = count;

            enemyIDs = battleStatus->enemyIDs;
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    s32 iVal = enemyIDs[i];
                    s32 jVal = enemyIDs[j];

                    if (battleStatus->enemyActors[iVal & 0xFF]->turnPriority <
                        battleStatus->enemyActors[jVal & 0xFF]->turnPriority)
                    {
                        enemyIDs[i] = jVal;
                        enemyIDs[j] = iVal;
                    }
                }
            }

            battleStatus->nextEnemyIndex = 0;
            nextEnemyIdx = 0;
            flags = ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_TARGET_ONLY;

            while (TRUE) {
                actor = battleStatus->enemyActors[battleStatus->enemyIDs[nextEnemyIdx] & 0xFF];
                if (actor == NULL || (actor->flags & flags)) {
                    nextEnemyIdx++;
                    if (nextEnemyIdx >= battleStatus->numEnemyActors) {
                        nextEnemyIdx = 0;
                    }
                } else {
                    break;
                }
            }

            activeEnemyActorID = battleStatus->enemyIDs[nextEnemyIdx];
            nextEnemyIdx++;
            battleStatus->curTurnEnemy = actor;
            battleStatus->activeEnemyActorID = activeEnemyActorID;
            if (nextEnemyIdx >= battleStatus->numEnemyActors) {
                nextEnemyIdx = 0;
            }
            battleStatus->nextEnemyIndex = nextEnemyIdx;
            btl_cam_target_actor(battleStatus->activeEnemyActorID);
            actor = battleStatus->curTurnEnemy;
            reset_actor_turn_info();
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(actor->takeTurnSource, EVT_PRIORITY_A, 0);
            script->owner1.actorID = battleStatus->activeEnemyActorID;
            actor->takeTurnScript = script;
            actor->takeTurnScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_AWAIT;
            BattleSubstateDelay = 3;
            break;
        case BTL_SUBSTATE_AWAIT:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                BattleCanShowFirstStrike = TRUE;
            }

            // wait for current enemy TakeTurn script to finish
            actor = battleStatus->curTurnEnemy;
            if (actor->takeTurnScript != NULL && does_script_exist(actor->takeTurnScriptID)) {
                break;
            }
            actor->takeTurnScript = NULL;

            // wait for player HandleEvent script to finish (may have been triggered by enemy Take Turn)
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for partner HandleEvent script to finish (may have been triggered by enemy Take Turn)
            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            // wait for all enemy TakeTurn scripts to finish
            waitingForScript = FALSE;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->takeTurnScript != NULL) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        waitingForScript = TRUE;
                    } else {
                        actor->takeTurnScript = NULL;
                    }
                }
            }

            if (waitingForScript) {
                break;
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
                break;
            }

            // reset state
            gBattleStatus.flags2 &= ~BS_FLAGS2_IGNORE_DARKNESS;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            if (battleStatus->stateFreezeCount == 0) {
                if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                    return;
                }
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_enemy_striking_first(void) {
    if (BattleCanShowFirstStrike) {
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
