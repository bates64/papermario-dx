#include "common.h"
#include "script_api/battle.h"
#include "states.h"

b32 dispatch_damage_tick_event_player(s32 damageAmount, s32 event);

enum {
    // BTL_SUBSTATE_INIT                  = 0,
    BTL_SUBSTATE_TRY_COMMAND_RECOVER      = 1,
    BTL_SUBSTATE_AWAIT_WATER_BLOCK        = 2,
    BTL_SUBSTATE_CHECK_WATER_BLOCK        = 10,
    BTL_SUBSTATE_CHECK_CLOUD_NINE         = 11,
    BTL_SUBSTATE_AWAIT_CLOUD_NINE         = 12,
    BTL_SUBSTATE_CHECK_TURBO_CHARGE       = 15,
    BTL_SUBSTATE_AWAIT_TURBO_CHARGE       = 16,
    BTL_SUBSTATE_AWAIT_OUTTA_SIGHT        = 20,
    BTL_SUBSTATE_TRY_STATUS_DAMAGE        = 21,
    BTL_SUBSTATE_TRY_STATUS_RECOVER       = 22,
    BTL_SUBSTATE_END_DELAY                = 30,
    BTL_SUBSTATE_RESET_STATE              = 100,
};

void handle_water_block(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_WATER_BLOCK:
            // allow state to be frozen here
            if (battleStatus->stateFreezeCount != 0) {
                return;
            }

            // is water block active?
            if (battleStatus->waterBlockTurnsLeft == 0) {
                gBattleSubState = BTL_SUBSTATE_CHECK_CLOUD_NINE;
                return;
            }

            // decrement buff duration by 1 turn
            battleStatus->waterBlockTurnsLeft--;
            battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_WATER_BLOCK].turnsLeft = battleStatus->waterBlockTurnsLeft;
            if (battleStatus->waterBlockTurnsLeft > 0) {
                gBattleSubState = BTL_SUBSTATE_CHECK_CLOUD_NINE;
                return;
            }

            // buff has ended
            battleStatus->waterBlockEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
            fx_water_block(FX_WATER_BLOCK_DESTROY, player->curPos.x, player->curPos.y + 18.0f, player->curPos.z + 5.0f, 1.5f, 10);
            fx_water_splash(0, player->curPos.x - 10.0f, player->curPos.y + 5.0f, player->curPos.z + 5.0f, 1.0f, 24);
            fx_water_splash(0, player->curPos.x - 15.0f, player->curPos.y + 32.0f, player->curPos.z + 5.0f, 1.0f, 24);
            fx_water_splash(1, player->curPos.x + 15.0f, player->curPos.y + 22.0f, player->curPos.z + 5.0f, 1.0f, 24);
            battleStatus->waterBlockEffect = NULL;
            sfx_play_sound(SOUND_DESTROY_WATER_BLOCK);

            // new substate will wait for popup to go away
            btl_show_battle_message(BTL_MSG_WATER_BLOCK_END, 60);
            gBattleSubState = BTL_SUBSTATE_AWAIT_WATER_BLOCK;
            break;

        case BTL_SUBSTATE_AWAIT_WATER_BLOCK:
            if (btl_is_popup_displayed()) {
                return;
            }
            gBattleSubState = BTL_SUBSTATE_CHECK_CLOUD_NINE;
            break;
    }
}

void btl_state_update_begin_player_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    ActorPart* part = &player->partsTable[0];
    Evt* script;
    s32 i;

    s8 debuffDuration;
    s32 koDuration;
    s32 prevDuration;
    s32 itemSpawnOffsetX;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        btl_cam_use_preset(BTL_CAM_DEFAULT);
        btl_cam_move(5);
        gBattleSubState = BTL_SUBSTATE_RESET_STATE;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_RESET_STATE:
            if (btl_cam_is_moving_done()) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_PARTNER_ACTING;
                reset_actor_turn_info();
                battleStatus->actionResult = ACTION_RESULT_NONE;
                battleStatus->blockResult = BLOCK_RESULT_NONE;
                battleStatus->selectedMoveID = 0;
                gBattleStatus.flags1 |= BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
                gBattleStatus.flags2 &= ~BS_FLAGS2_IS_FIRST_STRIKE;
                player->disableDismissTimer = 0;
                player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;

                if (partner != NULL) {
                    player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    partner->disableDismissTimer = 0;
                }

                battleStatus->stateFreezeCount = 0;
                D_8029F254 = FALSE;
                D_8029F258 = 0;

                if (battleStatus->outtaSightActive != 0) {
                    battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                    script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                    partner->handlePhaseScript = script;
                    gBattleSubState = BTL_SUBSTATE_AWAIT_OUTTA_SIGHT;
                    partner->handleBatttlePhaseScriptID = script->id;
                    script->owner1.actorID = ACTOR_PARTNER;
                } else {
                    gBattleSubState = BTL_SUBSTATE_CHECK_WATER_BLOCK;
                }
            }
            break;
        case BTL_SUBSTATE_AWAIT_OUTTA_SIGHT:
            if (!does_script_exist(partner->handleBatttlePhaseScriptID)) {
                battleStatus->outtaSightActive = 0;
                gBattleSubState = BTL_SUBSTATE_CHECK_WATER_BLOCK;
                gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
            }
            break;
    }

    handle_water_block();

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_CLOUD_NINE:
            if (battleStatus->cloudNineTurnsLeft != 0) {
                battleStatus->cloudNineTurnsLeft--;
                battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_CLOUD_NINE].turnsLeft = battleStatus->cloudNineTurnsLeft;

                if (battleStatus->cloudNineTurnsLeft <= 0) {
                    remove_effect(battleStatus->cloudNineEffect);
                    battleStatus->cloudNineEffect = NULL;
                    btl_show_battle_message(BTL_MSG_CLOUD_NINE_END, 60);
                    gBattleSubState = BTL_SUBSTATE_AWAIT_CLOUD_NINE;
                } else {
                    gBattleSubState = BTL_SUBSTATE_CHECK_TURBO_CHARGE;
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_TURBO_CHARGE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_CLOUD_NINE:
            if (!btl_is_popup_displayed()) {
                gBattleSubState = BTL_SUBSTATE_CHECK_TURBO_CHARGE;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_TURBO_CHARGE:
            if (battleStatus->turboChargeTurnsLeft != 0) {
                if (gBattleStatus.flags2 & BS_FLAGS2_STORED_TURBO_CHARGE_TURN) {
                    gBattleStatus.flags2 &= ~BS_FLAGS2_STORED_TURBO_CHARGE_TURN;
                    gBattleSubState = BTL_SUBSTATE_TRY_STATUS_DAMAGE;
                } else {
                    battleStatus->turboChargeTurnsLeft--;
                    battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_TURBO_CHARGE].turnsLeft = battleStatus->turboChargeTurnsLeft;
                    if (battleStatus->turboChargeTurnsLeft <= 0) {
                        btl_show_battle_message(BTL_MSG_TURBO_CHARGE_END, 60);
                        gBattleSubState = BTL_SUBSTATE_AWAIT_TURBO_CHARGE;
                    } else {
                        gBattleSubState = BTL_SUBSTATE_TRY_STATUS_DAMAGE;
                    }
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_TRY_STATUS_DAMAGE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_TURBO_CHARGE:
            if (!btl_is_popup_displayed()) {
                gBattleSubState = BTL_SUBSTATE_TRY_STATUS_DAMAGE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_TRY_STATUS_DAMAGE) {
        if (player->debuff == STATUS_KEY_POISON && player->stoneStatus == 0) {
            gBattleStatus.flags1 |= BS_FLAGS1_TRIGGER_EVENTS;
            dispatch_damage_tick_event_player(1, EVENT_HIT);
        }

        // clear rush flags to initialize
        battleStatus->rushFlags = RUSH_FLAG_NONE;
        gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;

        // set rush flags based on danger/peril status
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
            if (gPlayerData.curHP <= PERIL_THRESHOLD && is_ability_active(ABILITY_MEGA_RUSH)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_MEGA;
            }
            if (gPlayerData.curHP <= DANGER_THRESHOLD && is_ability_active(ABILITY_POWER_RUSH)) {
                if (!(battleStatus->rushFlags & RUSH_FLAG_MEGA)) {
                    gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                    battleStatus->rushFlags |= RUSH_FLAG_POWER;
                }
            }
        }
        gBattleSubState = BTL_SUBSTATE_TRY_STATUS_RECOVER;
    }

    if (gBattleSubState == BTL_SUBSTATE_TRY_STATUS_RECOVER) {
        if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
            player->handleEventScript = NULL;
            if (btl_check_player_defeated()) {
                return;
            }

            D_8029F254 = FALSE;
            player->disableDismissTimer = 0;
            player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;

            if (is_ability_active(ABILITY_FEELING_FINE)) {
                if (player->debuff != 0) {
                    player->debuffDuration = 1;
                }
                if (player->staticStatus != 0) {
                    player->staticDuration = 1;
                }
                if (player->stoneStatus != 0) {
                    player->stoneDuration = 1;
                }
                if (player->koStatus != 0) {
                    player->koDuration = 1;
                }
                if (player->transparentStatus != 0) {
                    player->transparentDuration = 1;
                }
            }

            if (player->stoneStatus != 0) {
                player->stoneDuration--;
                if (player->stoneDuration <= 0) {
                    player->stoneStatus = 0;
                    dispatch_event_player(EVENT_RECOVER_STATUS);
                }
            } else {
                if (!is_ability_active(ABILITY_ZAP_TAP) && player->staticStatus != 0) {
                    player->staticDuration--;
                    if (player->staticDuration <= 0) {
                        player->staticStatus = 0;
                        remove_status_static(player->hudElementDataIndex);
                    }
                }
                if (player->transparentStatus != 0) {
                    player->transparentDuration--;
                    part->flags |= ACTOR_PART_FLAG_TRANSPARENT;
                    if (player->transparentDuration <= 0) {
                        player->transparentStatus = 0;
                        part->flags &= ~ACTOR_PART_FLAG_TRANSPARENT;
                        remove_status_transparent(player->hudElementDataIndex);
                    }
                }

                if (player->debuff != 0) {
                    if (player->debuff <= STATUS_KEY_POISON) {
                        D_8029F254 = TRUE;
                    }
                    D_8029F258 = 20;
                    player->debuffDuration--;
                    if (player->debuffDuration <= 0) {
                        if (player->debuff == STATUS_KEY_FROZEN) {
                            sfx_play_sound(SOUND_FROZEN_SHATTER);
                            player->icePillarEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
                            player->icePillarEffect = NULL;
                            dispatch_event_player(EVENT_32);
                        } else {
                            dispatch_event_player(EVENT_RECOVER_STATUS);
                        }
                        player->debuff = 0;
                        player->debuffDuration = 0;
                        remove_status_debuff(player->hudElementDataIndex);
                    }
                }

                debuffDuration = player->debuffDuration;
                prevDuration = player->koDuration;
                player->koDuration = debuffDuration;
                if (debuffDuration > 0) {
                    player->koStatus = STATUS_KEY_DAZE;
                    player->disableEffect->data.disableX->koDuration = player->koDuration;
                } else if (prevDuration != debuffDuration) {
                    player->koStatus = 0;
                    player->koDuration = 0;
                    player->disableEffect->data.disableX->koDuration = 0;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                Actor* enemy = battleStatus->enemyActors[i];

                if (enemy != NULL) {
                    enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    if (enemy->chillOutTurns != 0) {
                        enemy->chillOutTurns--;
                        if (enemy->chillOutTurns == 0) {
                            enemy->chillOutAmount = 0;
                            remove_status_chill_out(enemy->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }
                }
            }
            gBattleSubState = BTL_SUBSTATE_TRY_COMMAND_RECOVER;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_TRY_COMMAND_RECOVER) {
        if (btl_check_enemies_defeated()) {
            return;
        }
        itemSpawnOffsetX = 1;
        battleStatus->stateFreezeCount = 0;
        if (battleStatus->hammerLossTurns >= 0) {
            battleStatus->hammerLossTurns--;
            if (battleStatus->hammerLossTurns == -1) {
                script = start_script(&EVS_PlayerRegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = itemSpawnOffsetX;
                itemSpawnOffsetX += 8;
                script->varTable[10] = BTL_MENU_TYPE_SMASH;
                battleStatus->stateFreezeCount = 1;
            }
        }

        if (battleStatus->jumpLossTurns >= 0) {
            battleStatus->jumpLossTurns--;
            if (battleStatus->jumpLossTurns == -1) {
                script = start_script(&EVS_PlayerRegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = itemSpawnOffsetX;
                itemSpawnOffsetX += 8;
                script->varTable[10] = BTL_MENU_TYPE_JUMP;
                battleStatus->stateFreezeCount = 1;
            }
        }

        if (battleStatus->itemLossTurns >= 0) {
            battleStatus->itemLossTurns--;
            if (battleStatus->itemLossTurns == -1) {
                script = start_script(&EVS_PlayerRegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = itemSpawnOffsetX;
                itemSpawnOffsetX += 8;
                script->varTable[10] = BTL_MENU_TYPE_ITEMS;
                battleStatus->stateFreezeCount = 1;
            }
        }
        gBattleSubState = BTL_SUBSTATE_END_DELAY;
    }

    if (gBattleSubState == BTL_SUBSTATE_END_DELAY) {
        if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
            player->handleEventScript = NULL;

            if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                return;
            }

            if (D_8029F258 != 0) {
                D_8029F258--;
                return;
            }

            if (!D_8029F254) {
                btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
            } else{
                btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
                gBattleStatus.flags2 |= BS_FLAGS2_PLAYER_TURN_USED;
            }
        }
    }
}

void btl_state_draw_begin_player_turn(void) {
}
