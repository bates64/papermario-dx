#include "common.h"

BSS s32 BattleSubstateDelay; // generic delay time usable for various substates
BSS b32 D_8029F254;
BSS s32 D_8029F258;

void btl_merlee_on_start_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerData* playerData = &gPlayerData;

    if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)
        && battleStatus->nextMerleeSpellType != MERLEE_SPELL_EXP_BOOST
        && battleStatus->nextMerleeSpellType != MERLEE_SPELL_COIN_BOOST
        && playerData->merleeCastsLeft > 0
    ) {
        if (playerData->merleeTurnCount <= 0) {
            s32 temp = rand_int(100);

            if (currentEncounter->curEnemy != NULL) {
                if (currentEncounter->curEnemy->flags & ACTOR_FLAG_NO_HEALTH_BAR) {
                    // 46/101 ≈ 45.5%
                    if (temp <= 45) {
                        playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
                    } else if (temp <= 90) { // 45/101 ≈ 44.6%
                        playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
                    } else { // 10/101 ≈ 9.9%
                        playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
                    }
                } else if (temp <= 30) { // 31/101 ≈ 30.7%
                    playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
                } else if (temp <= 60) { // 30/101 ≈ 29.7%
                    playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
                } else if (temp <= 80) { // 20/101 ≈ 19.8%
                    playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
                } else { // 20/101 ≈ 19.8%
                    playerData->merleeSpellType = MERLEE_SPELL_COIN_BOOST;
                }
            } else if (temp <= 30) { // 31/101 ≈ 30.7%
                playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
            } else if (temp <= 60) { // 30/101 ≈ 29.7%
                playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
            } else if (temp <= 80) { // 20/101 ≈ 19.8%
                playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
            } else { // 20/101 ≈ 19.8%
                playerData->merleeSpellType = MERLEE_SPELL_COIN_BOOST;
            }

            temp = rand_int(10) + 6;
            playerData->merleeTurnCount = temp;
        }

        if (playerData->merleeTurnCount >= 2) {
            playerData->merleeTurnCount--;
        } else {
            playerData->merleeTurnCount = 0;
            battleStatus->nextMerleeSpellType = playerData->merleeSpellType;
            playerData->merleeCastsLeft--;
        }
    }
}

void btl_merlee_on_first_strike(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerData* playerData = &gPlayerData;

    if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)
        && battleStatus->nextMerleeSpellType != MERLEE_SPELL_EXP_BOOST
        && battleStatus->nextMerleeSpellType != MERLEE_SPELL_COIN_BOOST
        && playerData->merleeCastsLeft > 0)
    {
        if (playerData->merleeTurnCount <= 0) {
            s32 temp = rand_int(100);

            if (currentEncounter->curEnemy != NULL) {
                if (currentEncounter->curEnemy->flags & ACTOR_FLAG_NO_HEALTH_BAR) {
                    // 46/101 ≈ 45.5%
                    if (temp <= 45) {
                        playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
                    } else if (temp <= 90) { // 45/101 ≈ 44.6%
                        playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
                    } else { // 10/101 ≈ 9.9%
                        playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
                    }
                } else if (temp <= 30) { // 31/101 ≈ 30.7%
                    playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
                } else if (temp <= 60) { // 30/101 ≈ 29.7%
                    playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
                } else if (temp <= 80) { // 20/101 ≈ 19.8%
                    playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
                } else { // 20/101 ≈ 19.8%
                    playerData->merleeSpellType = MERLEE_SPELL_COIN_BOOST;
                }
            } else if (temp <= 30) { // 31/101 ≈ 30.7%
                playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
            } else if (temp <= 60) { // 30/101 ≈ 29.7%
                playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
            } else if (temp <= 80) { // 20/101 ≈ 19.8%
                playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
            } else { // 20/101 ≈ 19.8%
                playerData->merleeSpellType = MERLEE_SPELL_COIN_BOOST;
            }

            if (playerData->merleeSpellType == MERLEE_SPELL_COIN_BOOST) {
                temp = rand_int(8) + 5;
            } else {
                temp = rand_int(5) + 5;
            }
            playerData->merleeTurnCount = temp;
        }

        if (playerData->merleeSpellType == MERLEE_SPELL_EXP_BOOST || playerData->merleeSpellType == MERLEE_SPELL_COIN_BOOST) {
            if (playerData->merleeTurnCount >= 2) {
                playerData->merleeTurnCount--;
            } else {
                battleStatus->nextMerleeSpellType = playerData->merleeSpellType;
                playerData->merleeTurnCount = 0;
                playerData->merleeCastsLeft--;
            }
        }
    }
}

void btl_set_state(s32 battleState) {
    gBattleState = battleState;
    gBattleSubState = BTL_SUBSTATE_INIT;

    if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
        switch (battleState) {
            case BATTLE_STATE_PARTNER_MENU:
                battleState = BATTLE_STATE_TWINK_MENU;
                break;
            case BATTLE_STATE_PLAYER_MENU:
                battleState = BATTLE_STATE_PEACH_MENU;
                break;
            case BATTLE_STATE_BEGIN_PLAYER_TURN:
                battleState = BATTLE_STATE_BEGIN_PARTNER_TURN;
                break;
            case BATTLE_STATE_BEGIN_PARTNER_TURN:
                battleState = BATTLE_STATE_BEGIN_PLAYER_TURN;
                break;
        }
        gBattleState = battleState;
    }
}
