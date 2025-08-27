#include "states.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"

#include "sprite/npc/Goompa.h"
#include "sprite/npc/BattleGoombario.h"
#include "sprite/npc/BattleKooper.h"
#include "sprite/npc/BattleBombette.h"
#include "sprite/npc/BattleParakarry.h"
#include "sprite/npc/BattleBow.h"
#include "sprite/npc/BattleWatt.h"
#include "sprite/npc/BattleSushie.h"
#include "sprite/npc/BattleLakilester.h"

enum {
    // BTL_SUBSTATE_INIT                        = 0,

    // Main menu
    BTL_SUBSTATE_MAIN_MENU_1                    = 2,
    BTL_SUBSTATE_MAIN_MENU_2                    = 3,
    BTL_SUBSTATE_MAIN_MENU_3                    = 4,
    BTL_SUBSTATE_MAIN_MENU_4                    = 5,
    BTL_SUBSTATE_MAIN_MENU_5                    = 6,
    BTL_SUBSTATE_MAIN_MENU_6                    = 7,
    BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP            = 8,
    BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP           = 9,
    // Abilities
    BTL_SUBSTATE_ABILITIES_1                    = 10,
    BTL_SUBSTATE_ABILITIES_2                    = 11,
    BTL_SUBSTATE_ABILITIES_3                    = 12,
    BTL_SUBSTATE_ABILITIES_4                    = 13,
    BTL_SUBSTATE_ABILITIES_5                    = 14,
    BTL_SUBSTATE_ABILITIES_6                    = 15,
    BTL_SUBSTATE_ABILITIES_7                    = 16,
    // Unknown, referenced only in btl_state_draw_partner_menu
    BTL_SUBSTATE_UNKNOWN_1                      = 20,
    BTL_SUBSTATE_UNKNOWN_2                      = 21,
    BTL_SUBSTATE_UNKNOWN_3                      = 22,
    BTL_SUBSTATE_UNKNOWN_4                      = 23,
    BTL_SUBSTATE_UNKNOWN_5                      = 24,
    // Change Partner
    BTL_SUBSTATE_CHANGE_PARTNER_1               = 30,
    BTL_SUBSTATE_CHANGE_PARTNER_2               = 31,
    BTL_SUBSTATE_CHANGE_PARTNER_3               = 32,
    BTL_SUBSTATE_CHANGE_PARTNER_4               = 33,
    BTL_SUBSTATE_CHANGE_PARTNER_5               = 34,
    BTL_SUBSTATE_CHANGE_PARTNER_6               = 35,
    BTL_SUBSTATE_CHANGE_PARTNER_7               = 36,
    // Items
    BTL_SUBSTATE_ITEMS_BUILD_MENU               = 40,
    BTL_SUBSTATE_ITEMS_CHOOSING                 = 41,
    BTL_SUBSTATE_ITEMS_PREP_TARGET_SELECT       = 42,
    BTL_SUBSTATE_ITEMS_REOPEN_MENU              = 43,
    BTL_SUBSTATE_ITEMS_TARGET_CANCELED          = 44,
    BTL_SUBSTATE_ITEMS_TARGET_SELECTED          = 45,
    // Switch partner (from main menu?) (unused)
    BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU       = 50,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2        = 51,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_3        = 52,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_4        = 53,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_5        = 54,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_6        = 55,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_7        = 56,
    // Focus
    BTL_SUBSTATE_FOCUS_BUILD_MENU               = 60,
    BTL_SUBSTATE_FOCUS_CHOOSING                        = 61,
    BTL_SUBSTATE_FOCUS_3                        = 62,
    BTL_SUBSTATE_FOCUS_REOPEN_MENU                        = 63,
    BTL_SUBSTATE_FOCUS_CANCELED                        = 64,
    BTL_SUBSTATE_FOCUS_SELECTED                        = 65,
    // Strategies
    BTL_SUBSTATE_STRATEGIES_BUILD_MENU          = 200,
    BTL_SUBSTATE_STRATEGIES_CHOOSING            = 201,
    BTL_SUBSTATE_STRATEGIES_3                   = 202,
    BTL_SUBSTATE_STRATEGIES_4                   = 203,
    BTL_SUBSTATE_STRATEGIES_5                   = 204,
    BTL_SUBSTATE_STRATEGIES_6                   = 205,
    // initialize
    BTL_SUBSTATE_12D                            = 301,
    BTL_SUBSTATE_INIT_MENU                      = 302,
};

AnimID PartnerThinkAnims[] = {
    [PARTNER_GOOMBARIO]  ANIM_BattleGoombario_Think,
    [PARTNER_KOOPER]     ANIM_BattleKooper_Think,
    [PARTNER_BOMBETTE]   ANIM_BattleBombette_Think,
    [PARTNER_PARAKARRY]  ANIM_BattleParakarry_Think,
    [PARTNER_GOOMPA]     ANIM_Goompa_Idle,
    [PARTNER_WATT]       ANIM_BattleWatt_Think,
    [PARTNER_SUSHIE]     ANIM_BattleSushie_Think,
    [PARTNER_LAKILESTER] ANIM_BattleLakilester_Run,
    [PARTNER_BOW]        ANIM_BattleBow_Still,
    [PARTNER_GOOMBARIA]  0,
    [PARTNER_TWINK]      0,
};

AnimID PartnerIdleAnims[] = {
    [PARTNER_GOOMBARIO]  ANIM_BattleGoombario_Walk,
    [PARTNER_KOOPER]     ANIM_BattleKooper_Walk,
    [PARTNER_BOMBETTE]   ANIM_BattleBombette_Walk,
    [PARTNER_PARAKARRY]  ANIM_BattleParakarry_Walk,
    [PARTNER_GOOMPA]     ANIM_Goompa_Walk,
    [PARTNER_WATT]       ANIM_BattleWatt_Walk,
    [PARTNER_SUSHIE]     ANIM_BattleSushie_Walk,
    [PARTNER_LAKILESTER] ANIM_BattleLakilester_Walk,
    [PARTNER_BOW]        ANIM_BattleBow_Walk,
    [PARTNER_GOOMBARIA]  0,
    [PARTNER_TWINK]      0,
};

IconHudScriptPair PartnerMoveHudScripts[][5] = {
    [PARTNER_GOOMBARIO] {
        {&HES_Goombario, &HES_GoombarioDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_KOOPER] {
        {&HES_Kooper, &HES_KooperDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_BOMBETTE] {
        {&HES_Bombette, &HES_BombetteDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_PARAKARRY]  {
        {&HES_Parakarry, &HES_ParakarryDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_GOOMPA] {
        {&HES_Partner0, &HES_Partner0Disabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_WATT] {
        {&HES_Watt, &HES_WattDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_SUSHIE] {
        {&HES_Sushie, &HES_SushieDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_LAKILESTER] {
        {&HES_Lakilester, &HES_LakilesterDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_BOW] {
        {&HES_Bow, &HES_BowDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
};

s32 PartnerNameMessages[] = {
    MSG_NONE,
    MSG_Menus_Party_Goombario,
    MSG_Menus_Party_Kooper,
    MSG_Menus_Party_Bombette,
    MSG_Menus_Party_Parakarry,
    MSG_Menus_Party_Goompa,
    MSG_Menus_Party_Watt,
    MSG_Menus_Party_Sushie,
    MSG_Menus_Party_Lakilester,
    MSG_Menus_Party_Bow,
    MSG_Menus_Party_Goombaria,
    MSG_Menus_Party_Twink,
    MSG_Menus_Party_Peach,
    MSG_NONE
};

void btl_init_menu_partner(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 fpCost;
    s32 i;
    s32 hasAnyBadgeMoves;

    for (i = 0; i < ARRAY_COUNT(battleStatus->submenuMoves); i++) {
        battleStatus->submenuMoves[i] = MOVE_NONE;
    }

    // In the move table (enum MoveIDs), partners get move IDs set up like this:
    //
    //  Move ID offset | Description          | Goombario example
    // ----------------+----------------------+-------------------
    //  0              | No rank only         | Headbonk
    //  1              | Super rank only      | Headbonk (2)
    //  2              | Ultra rank only      | Headbonk (3)
    //  3              | Always unlocked      | Tattle
    //  4              | Unlocked after super | Charge
    //  5              | Unlocked after ultra | Multibonk

    battleStatus->submenuMoveCount = partner->actorBlueprint->level + 2;

    // Select rank-appropriate basic move from offsets 0, 1, or 2
    battleStatus->submenuMoves[0] =
        (playerData->curPartner - 1) * 6
        + MOVE_HEADBONK1
        + partner->actorBlueprint->level;

    // Add rank-unlocked special moves from offsets 3, 4, and 5
    for (i = 1; i < battleStatus->submenuMoveCount; i++) {
        battleStatus->submenuMoves[i] =
            (playerData->curPartner - 1) * 6
            + MOVE_TATTLE
            + (i - 1);
    }

    hasAnyBadgeMoves = FALSE;
    for (i = 0; i < battleStatus->submenuMoveCount; i++){
        MoveData* move = &gMoveTable[battleStatus->submenuMoves[i]];

        fpCost = move->costFP;
        if (fpCost != 0) {
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_SAVER);
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_FANATIC) * 2;
            if (fpCost < 1) {
                fpCost = 1;
            }
        }

        battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
        battleStatus->moveArgument = partner->actorBlueprint->level;
        battleStatus->curTargetListFlags = move->flags;
        create_current_pos_target_list(partner);

        if (partner->targetListLength != 0){
            hasAnyBadgeMoves = TRUE;
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_ENABLED;
        }

        if (partner->targetListLength == 0) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS_2;
        }

        if (playerData->curFP < fpCost) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NOT_ENOUGH_FP;
        }
        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS;
        }
    }

    if (!hasAnyBadgeMoves) {
        battleStatus->menuStatus[3] = -1;
    } else {
        battleStatus->menuStatus[3] = 1;
    }
}

void btl_state_update_partner_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* playerActor = battleStatus->playerActor;
    Actor* partnerActor = battleStatus->partnerActor;
    PopupMenu* popupMenu = &D_802ACCD0;
    s32 entryIdx;
    s32 i;
    s32 popupIndex;
    s32 initialPos;
    MoveData* moveData;
    PartnerPopupProperties* popupProps;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->moveCategory = BTL_MENU_TYPE_INVALID;
        battleStatus->selectedMoveID = MOVE_NONE;
        battleStatus->curAttackElement = 0;
        if (!can_switch_to_partner()) {
            btl_set_state(BATTLE_STATE_9);
        } else {
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            battleStatus->flags1 |= BS_FLAGS1_MENU_OPEN;
            playerActor->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
            partnerActor->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
            if (battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
                gBattleSubState = BTL_SUBSTATE_INIT_MENU;
            } else {
                gBattleSubState = BTL_SUBSTATE_12D;
                partnerActor->state.curPos.x = partnerActor->homePos.x;
                partnerActor->state.curPos.z = partnerActor->homePos.z;
                partnerActor->state.goalPos.x = playerActor->homePos.x;
                partnerActor->state.goalPos.z = playerActor->homePos.z;
                partnerActor->state.moveTime = 4;
                partnerActor->state.angle = 0.0f;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_12D) {
        if (partnerActor->state.moveTime != 0) {
            partnerActor->curPos.x += (partnerActor->state.goalPos.x - partnerActor->curPos.x) / partnerActor->state.moveTime;
            partnerActor->curPos.z += (partnerActor->state.goalPos.z - partnerActor->curPos.z) / partnerActor->state.moveTime;
            playerActor->curPos.x += (partnerActor->state.curPos.x - playerActor->curPos.x) / partnerActor->state.moveTime;
            playerActor->curPos.z += (partnerActor->state.curPos.z - playerActor->curPos.z) / partnerActor->state.moveTime;
        }
        partnerActor->curPos.z += sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
        partnerActor->yaw = clamp_angle(-partnerActor->state.angle);
        playerActor->curPos.z -= sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
        playerActor->yaw = clamp_angle(-partnerActor->state.angle);
        partnerActor->state.angle += 90.0f;
        if (partnerActor->state.moveTime != 0) {
            partnerActor->state.moveTime--;
        } else {
            gBattleSubState = BTL_SUBSTATE_INIT_MENU;
            partnerActor->curPos.x = partnerActor->state.goalPos.x;
            partnerActor->curPos.z = partnerActor->state.goalPos.z;
            playerActor->curPos.x = partnerActor->state.curPos.x;
            playerActor->curPos.z = partnerActor->state.curPos.z;
            partnerActor->homePos.x = partnerActor->curPos.x;
            partnerActor->homePos.z = partnerActor->curPos.z;
            playerActor->homePos.x = playerActor->curPos.x;
            playerActor->homePos.z = playerActor->curPos.z;
            gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT_MENU:
            partnerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            partnerActor->flags &= ~ACTOR_FLAG_USING_IDLE_ANIM;
            playerActor->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            playerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            btl_init_menu_items();
            btl_check_can_change_partner();
            entryIdx = 0;
            initialPos = 1;
            if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] < 0) {
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = BTL_MENU_TYPE_ABILITY;
            }
            btl_init_menu_partner();
            btl_check_can_change_partner();

            // strategies menu category
            battle_menu_submenuIDs[entryIdx] = BTL_MENU_TYPE_STRATEGIES;
            BattleMenu_OptionEnabled[entryIdx] = TRUE;
            battle_menu_isMessageDisabled[entryIdx] = 0;
            BattleMenu_HudScripts[entryIdx] = battle_menu_StrategiesHudScript.enabled;
            BattleMenu_TitleMessages[entryIdx] = BattleMenu_CenteredMessages[BTL_MENU_TYPE_STRATEGIES];
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STRATEGIES)) {
                BattleMenu_OptionEnabled[entryIdx] = FALSE;
                battle_menu_isMessageDisabled[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                BattleMenu_HudScripts[entryIdx] = battle_menu_StrategiesHudScript.disabled;
            }
            if (battleStatus->lastPartnerMenuSelection[entryIdx] == BTL_MENU_TYPE_STRATEGIES) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // abilities menu category
            BattleMenu_HudScripts[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].enabled;
            battle_menu_submenuIDs[entryIdx] = BTL_MENU_TYPE_ABILITY;
            BattleMenu_OptionEnabled[entryIdx] = TRUE;
            BattleMenu_TitleMessages[entryIdx] = BattleMenu_CenteredMessages[BTL_MENU_TYPE_ABILITY];
            if (battleStatus->menuStatus[3] <= 0) {
                BattleMenu_HudScripts[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].disabled;
                BattleMenu_OptionEnabled[entryIdx] = FALSE;
                battle_menu_isMessageDisabled[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_ABILITIES)) {
                BattleMenu_HudScripts[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].disabled;
                BattleMenu_OptionEnabled[entryIdx] = FALSE;
                battle_menu_isMessageDisabled[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_ABILITY) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // focus menu category
            if (playerData->maxStarPower != 0 && is_ability_active(ABILITY_GROUP_FOCUS)) {
                battle_menu_submenuIDs[entryIdx] = BTL_MENU_TYPE_PARTNER_FOCUS;
                BattleMenu_OptionEnabled[entryIdx] = TRUE;
                battle_menu_isMessageDisabled[entryIdx] = 0;
                BattleMenu_HudScripts[entryIdx] = battle_menu_StarPowerHudScripts.enabled;
                BattleMenu_TitleMessages[entryIdx] = BattleMenu_CenteredMessages[BTL_MENU_TYPE_PARTNER_FOCUS];
                if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_PARTNER_FOCUS)) {
                    BattleMenu_OptionEnabled[entryIdx] = FALSE;
                    battle_menu_isMessageDisabled[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                    BattleMenu_HudScripts[entryIdx] = battle_menu_StarPowerHudScripts.disabled;
                }
                if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_PARTNER_FOCUS) {
                    initialPos = entryIdx;
                }
                entryIdx++;
            }

            BattleMenu_NumOptions = entryIdx;
            D_802AD0A8 = 1;
            D_802AD0B0 = initialPos;
            D_802AD100 = 2 - initialPos;
            if (can_switch_to_player()) {
                BattleMenu_ShowSwapIcons = TRUE;
            } else {
                BattleMenu_ShowSwapIcons = FALSE;
            }
            btl_main_menu_init();
            D_802ACC60 = UNK_MENU_DELAY;
            BattleMenu_SwapDelay = 0;
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
            return;
        case BTL_SUBSTATE_MAIN_MENU_1:
            set_actor_anim(ACTOR_PARTNER, 0, PartnerThinkAnims[playerData->curPartner]);
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_2;
            // fall through
        case BTL_SUBSTATE_MAIN_MENU_2:
            entryIdx = btl_main_menu_update();

            if (BattleMenu_SwapDelay != 0) {
                BattleMenu_SwapDelay--;
            } else if (!(gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) && (gGameStatusPtr->pressedButtons[0] & BUTTON_Z)) {
                if (can_switch_to_player()) {
                    sfx_play_sound(SOUND_PARTNER_SWAP_BATTLE_POS);
                    battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = battle_menu_submenuIDs[BattleMenu_CurPos + BattleMenu_HomePos];
                    btl_main_menu_destroy();
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    gBattleSubState = BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP;
                }
                break;
            }

            if (D_802ACC60 != 0) {
                D_802ACC60--;
                break;
            }

            if (entryIdx != 0) {
                set_actor_anim(ACTOR_PARTNER, 0, PartnerIdleAnims[playerData->curPartner]);
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = battleStatus->curPartnerSubmenu = battle_menu_submenuIDs[entryIdx - 1];
                switch (battleStatus->curPartnerSubmenu) {
                    case BTL_MENU_TYPE_STRATEGIES:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_ABILITY:
                        gBattleSubState = BTL_SUBSTATE_ABILITIES_1;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_STAR_POWERS:
                        gBattleSubState = BTL_SUBSTATE_FOCUS_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_ITEMS:
                        gBattleSubState = BTL_SUBSTATE_ITEMS_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_CHANGE_PARTNER:
                        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    default:
                        battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_MAIN_MENU_5;
                        battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_MAIN_MENU_6;
                        func_802A1030();
                        gBattleSubState = BTL_SUBSTATE_MAIN_MENU_3;
                        break;
                }
            }
            break;
    case BTL_SUBSTATE_MAIN_MENU_3:
        entryIdx = btl_main_menu_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == 0) {
            func_802A1078();
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_4;
            return;
        }
        if (entryIdx != 0) {
            battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
            battleStatus->selectedMoveID = MOVE_FOCUS;
            battleStatus->moveArgument = 0;
            battleStatus->curTargetListFlags = gMoveTable[MOVE_FOCUS].flags;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
            return;
        }
        break;
    case BTL_SUBSTATE_MAIN_MENU_4:
        if (btl_main_menu_update() != 0) {
            D_802ACC60 = UNK_MENU_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
        }
        break;
    case BTL_SUBSTATE_MAIN_MENU_5:
        func_802A1078();
        gBattleSubState = BTL_SUBSTATE_MAIN_MENU_4;
        break;
    case BTL_SUBSTATE_MAIN_MENU_6:
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP:
        if (!can_switch_to_player()) {
            btl_show_variable_battle_message(BTL_MSG_CANT_MOVE, 60, 0);
        } else {
            btl_show_variable_battle_message(BTL_MSG_CANT_SWITCH, 60, 0);
        }
        ShowingErrorMessage = TRUE;
        gBattleSubState = BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP;
        break;
    case BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP:
        if (btl_is_popup_displayed()) {
            break;
        }
        D_802ACC60 = 0;
        ShowingErrorMessage = FALSE;
        BattleMenu_SwapDelay = 4;
        gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
        break;
    case BTL_SUBSTATE_ABILITIES_1:
        for (i = 0; i < battleStatus->submenuMoveCount; i++) {
            moveData = &gMoveTable[battleStatus->submenuMoves[i]];

            BattleMenu_Moves_OptionCantUseMessages[i] = 0;
            if (battleStatus->submenuStatus[i] == 0) {
                BattleMenu_Moves_OptionCantUseMessages[i] = 0;
            }
            if (battleStatus->submenuStatus[i] == -1) {
                battleStatus->submenuStatus[i] = 0;
                BattleMenu_Moves_OptionCantUseMessages[i] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->submenuStatus[i] == -2) {
                battleStatus->submenuStatus[i] = 0;
                BattleMenu_Moves_OptionCantUseMessages[i] = BTL_MSG_CANT_SELECT_NOW;
            }
            battle_menu_moveOptionIconScripts[i] = PartnerMoveHudScripts[playerData->curPartner][i + 1].enabled;
            if (battleStatus->submenuStatus[i] == 0) {
                battle_menu_moveOptionIconScripts[i] = PartnerMoveHudScripts[playerData->curPartner][i + 1].disabled;
            }
            BattleMenu_Moves_OptionIndices[i] = battleStatus->submenuMoves[i];
            BattleMenu_Moves_OptionEnabled[i] = battleStatus->submenuStatus[i];
            battle_menu_moveOptionNames[i] = moveData->nameMsg;
            BattleMenu_Moves_OptionDescMessages[i] = moveData->shortDescMsg;
            battle_menu_moveOptionDisplayCosts[i] = moveData->costFP;
            battle_menu_moveOptionBPCosts[i] = moveData->costBP;
            BattleMenu_Moves_OptionSortPriority[i] = i;

            battle_menu_moveOptionDisplayCostReductions[i] = 0;
            battle_menu_moveOptionDisplayCostReductionColors[i] = 0;
            if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER)) {
                battle_menu_moveOptionDisplayCostReductions[i] += player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER);
                battle_menu_moveOptionDisplayCostReductionColors[i] = 1;
            }
            if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC)) {
                battle_menu_moveOptionDisplayCostReductions[i] += player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC) * 2;
                battle_menu_moveOptionDisplayCostReductionColors[i] = 2;
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] = 0;
        }
        BattleMenu_UsingSpiritsSubmenu = FALSE;
        BattleMenu_Moves_OptionCount = battleStatus->submenuMoveCount;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY];
        D_802AD4A8 = initialPos;
        func_802A2684();
        gBattleSubState = BTL_SUBSTATE_ABILITIES_2;
        break;
    case BTL_SUBSTATE_ABILITIES_2:
        entryIdx = btl_submenu_moves_update();
        if (entryIdx == -1) {
            gBattleSubState = BTL_SUBSTATE_ABILITIES_7;
        } else if (entryIdx  != 0) {
            if (entryIdx == 255) {
                func_802A1050();
                D_802ACC60 = UNK_MENU_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
            } else {
                battleStatus->lastPartnerPowerSelection = entryIdx - 1;
                func_802A27D0();
                func_802A1030();
                gBattleSubState = BTL_SUBSTATE_ABILITIES_3;
            }
        }
        break;
    case BTL_SUBSTATE_ABILITIES_3:
        entryIdx = btl_submenu_moves_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == 0) {
            func_802A2AB8();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_ABILITIES_4;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->moveCategory = BTL_MENU_TYPE_ABILITY;
            battleStatus->selectedMoveID = BattleMenu_Moves_OptionIndices[battleStatus->lastPartnerPowerSelection];
            battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] = battle_menu_moveOptionActive;
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_5;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_6;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_ABILITIES_4:
        btl_submenu_moves_update();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_ABILITIES_2;
        }
        break;
    case BTL_SUBSTATE_ABILITIES_5:
        func_802A2AB8();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_ABILITIES_4;
        break;
    case BTL_SUBSTATE_ABILITIES_6:
        func_802A27E4();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_ABILITIES_7:
        if (btl_submenu_moves_update() != -1) {
            gBattleSubState = BTL_SUBSTATE_ABILITIES_2;
        }
        break;
    case BTL_SUBSTATE_ITEMS_BUILD_MENU:
        popupIndex = 0;
        for (i = 0; i < ARRAY_COUNT(playerData->invItems); i++) {
            ItemData* item;
            HudScript** hudScript;
            if (playerData->invItems[i] == ITEM_NONE) {
                continue;
            }
            item = &gItemTable[playerData->invItems[i]];
            hudScript = &gItemHudScripts[item->hudElemID].enabled;

            if (!(item->typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE)) {
                continue;
            }
            popupMenu->ptrIcon[popupIndex] = hudScript[0];
            popupMenu->userIndex[popupIndex] = playerData->invItems[i];
            popupMenu->enabled[popupIndex] = TRUE;
            popupMenu->nameMsg[popupIndex] = item->nameMsg;
            popupMenu->descMsg[popupIndex] = item->shortDescMsg;
            popupIndex++;
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] = 0;
        }
        popupMenu->popupType = POPUP_MENU_USE_ITEM;
        popupMenu->numEntries = popupIndex;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM];
        popupMenu->initialPos = initialPos;
        create_battle_popup_menu(popupMenu);
        func_800F52BC();
        gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
        break;
    case BTL_SUBSTATE_ITEMS_CHOOSING:
        if (popupMenu->result == POPUP_RESULT_CHOOSING) {
            break;
        } else if (popupMenu->result == POPUP_RESULT_CANCEL) {
            func_802A1050();
            D_802ACC60 = UNK_MENU_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
            btl_state_update_partner_menu();
            btl_state_update_partner_menu();
        } else {
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_CANCELED;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_SELECTED;
            battleStatus->lastSelectedItem = popupMenu->userIndex[popupMenu->result - 1];
            battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
            battleStatus->moveArgument = battleStatus->lastSelectedItem;
            battleStatus->curTargetListFlags = gItemTable[battleStatus->moveArgument].targetFlags | TARGET_FLAG_PRIMARY_ONLY;
            battleStatus->curAttackElement = 0;
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] = popupMenu->result - 1;
            hide_popup_menu();
            func_802A1030();
            gBattleSubState = BTL_SUBSTATE_ITEMS_PREP_TARGET_SELECT;
        }
        break;
    case BTL_SUBSTATE_ITEMS_REOPEN_MENU:
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_ITEMS_PREP_TARGET_SELECT:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && popupMenu->result == POPUP_RESULT_CHOOSING) {
            func_800F16CC();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_ITEMS_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_ITEMS_TARGET_CANCELED:
        func_800F16CC();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_ITEMS_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_ITEMS_TARGET_SELECTED:
        destroy_popup_menu();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU:
        popupIndex = 0;
        for (i = 1; i < ARRAY_COUNT(PartnerIDFromMenuIndex); i++) {
            s32 partnerId = PartnerIDFromMenuIndex[i];
            if (playerData->partners[partnerId].enabled) {
                popupProps = &gPartnerPopupProperties[partnerId];
                popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].enabled;
                popupMenu->enabled[popupIndex] = TRUE;
                popupMenu->userIndex[popupIndex] = partnerId;
                popupMenu->nameMsg[popupIndex] = popupProps->nameMsg;
                popupMenu->descMsg[popupIndex] = popupProps->battleDescMsg;
                popupMenu->value[popupIndex] = playerData->partners[partnerId].level;
                if (playerData->curPartner == partnerId) {
                    popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].disabled;
                    popupMenu->enabled[popupIndex] = FALSE;
                }
                popupIndex++;
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = 0;
        }
        popupMenu->popupType = POPUP_MENU_SWITCH_PARTNER;
        popupMenu->numEntries = popupIndex;
        popupMenu->initialPos = MenuIndexFromPartnerID[playerData->curPartner] - 1;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        create_battle_popup_menu(popupMenu);
        func_800F52BC();
        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2;
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2:
        switch (popupMenu->result) {
            case POPUP_RESULT_INVALID:
                gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_7;
                break;
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_CANCEL:
                func_802A1050();
                D_802ACC60 = UNK_MENU_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_5;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_6;
                battleStatus->unk_1AC = popupMenu->userIndex[popupMenu->result - 1];
                battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                battleStatus->selectedMoveID = MOVE_UNUSED_37;
                battleStatus->curTargetListFlags = TARGET_FLAG_2;
                battleStatus->moveArgument = battleStatus->unk_1AC;
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = popupMenu->result - 1;
                hide_popup_menu();
                func_802A1030();
                gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_3;
                break;
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_3:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && (popupMenu->result == POPUP_RESULT_CHOOSING)) {
            func_800F16CC();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_4;
        } else if (btl_main_menu_update() != 0) {
            gBattleSubState = battleStatus->acceptTargetMenuSubstate;
            btl_state_update_partner_menu();
            btl_set_state(BATTLE_STATE_CHANGE_PARTNER);
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_4:
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2;
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_5:
        func_800F16CC();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_4;
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_6:
        destroy_popup_menu();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_7:
        if (popupMenu->result != POPUP_RESULT_INVALID) {
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2;
        }
        break;
    case BTL_SUBSTATE_FOCUS_BUILD_MENU:
        entryIdx = 1;
        battleStatus->submenuMoveCount = entryIdx;
        battleStatus->submenuMoves[0] = MOVE_FOCUS;
        battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;
        battleStatus->submenuStatus[0] = 1;
        for (i = 0; i < battleStatus->submenuMoveCount; i++) {
            moveData = &gMoveTable[battleStatus->submenuMoves[i]];
            battle_menu_moveOptionIconScripts[i] = battle_menu_StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].enabled;
            if (battleStatus->submenuStatus[i] == 0) {
                battle_menu_moveOptionIconScripts[i] = battle_menu_StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].disabled;
            }
            battle_menu_moveOptionDisplayCosts[i] = moveData->costFP;
            battle_menu_moveOptionBPCosts[i] = moveData->costBP;
            BattleMenu_Moves_OptionIndices[i] = i;
            BattleMenu_Moves_OptionSortPriority[i] = i;
            BattleMenu_Moves_OptionEnabled[i] = battleStatus->submenuStatus[i];
            battle_menu_moveOptionNames[i] = moveData->nameMsg;
            BattleMenu_Moves_OptionDescMessages[i] = moveData->shortDescMsg;
            battle_menu_moveOptionDisplayCostReductions[i] = 0;
            battle_menu_moveOptionDisplayCostReductionColors[i] = 0;
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] = 0;
        }
        BattleMenu_UsingSpiritsSubmenu = TRUE;
        BattleMenu_Moves_OptionCount = battleStatus->submenuMoveCount;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER];
        D_802AD4A8 = initialPos;
        func_802A2684();
        gBattleSubState = BTL_SUBSTATE_FOCUS_CHOOSING;
        break;
    case BTL_SUBSTATE_FOCUS_CHOOSING:
        entryIdx = btl_submenu_moves_update();
        switch (entryIdx) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_CANCEL:
                func_802A1050();
                D_802ACC60 = UNK_MENU_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->lastPartnerPowerSelection = BattleMenu_Moves_OptionIndices[entryIdx - 1];
                func_802A27D0();
                func_802A1030();
                gBattleSubState = BTL_SUBSTATE_FOCUS_3;
                break;
        }
        break;
    case BTL_SUBSTATE_FOCUS_3:
        entryIdx = btl_submenu_moves_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && (entryIdx == 0)) {
            func_802A2AB8();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_FOCUS_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_FOCUS_CANCELED;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_FOCUS_SELECTED;
            battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
            battleStatus->selectedMoveID = battleStatus->submenuMoves[battleStatus->lastPartnerPowerSelection];
            battleStatus->curTargetListFlags = gMoveTable[battleStatus->submenuMoves[battleStatus->lastPartnerPowerSelection]].flags;
            battleStatus->moveArgument = battleStatus->lastPartnerPowerSelection;
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] = battle_menu_moveOptionActive;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_FOCUS_REOPEN_MENU:
        btl_submenu_moves_update();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_FOCUS_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_FOCUS_CANCELED:
        func_802A2AB8();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_FOCUS_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_FOCUS_SELECTED:
        func_802A27E4();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
        popupIndex = 0;
        btl_check_can_change_partner();

        // add 'Change Member' command
        if (battleStatus->changePartnerAllowed >= 0) {
            D_802AD678[popupIndex] = BTL_MENU_TYPE_CHANGE_PARTNER;
            D_802AD658[popupIndex] = BattleMenu_LeftJustMessages[BTL_MENU_TYPE_CHANGE_PARTNER];
            StratsOptionHudScript[popupIndex] = PartnerHudScripts[playerData->curPartner].enabled;
            StratsOptionMessage[popupIndex] = MSG_Menus_Action_ChangePartner;
            StratsOptionEnabled[popupIndex] = TRUE;
            if (battleStatus->changePartnerAllowed <= 0) {
                StratsOptionHudScript[popupIndex] = PartnerHudScripts[playerData->curPartner].disabled;
                StratsOptionEnabled[popupIndex] = FALSE;
                StratsOptionError[popupIndex] = 0;
            }
            popupIndex++;
        }

        // add 'Do Nothing' command
        D_802AD678[popupIndex] = BTL_MENU_TYPE_DO_NOTHING;
        D_802AD658[popupIndex] = BattleMenu_LeftJustMessages[BTL_MENU_TYPE_DO_NOTHING];
        StratsOptionHudScript[popupIndex] = DoNothingHudScripts.enabled;
        StratsOptionMessage[popupIndex] = MSG_Menus_Action_DoNothing;
        StratsOptionEnabled[popupIndex] = TRUE;
        popupIndex++;

        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = 0;
        }
        D_802AD66C = popupIndex;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY];
        StratsMenuLastPos = initialPos;
        func_802A45D8();
        gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
        break;
    case BTL_SUBSTATE_STRATEGIES_CHOOSING:
        entryIdx = btl_update_strats_menu();
        switch (entryIdx) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is selecting an entry
                break;
            case POPUP_RESULT_CANCEL:
                func_802A1050();
                D_802ACC60 = UNK_MENU_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->curPartnerSubmenu = D_802AD678[entryIdx - 1];
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = entryIdx - 1;
                if (battleStatus->curPartnerSubmenu == BTL_MENU_TYPE_CHANGE_PARTNER) {
                    gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_1;
                    btl_state_update_partner_menu();
                    btl_state_update_partner_menu();
                } else {
                    func_802A4718();
                    func_802A1030();
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_3;
                }
                break;
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_3:
        entryIdx = btl_update_strats_menu();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == POPUP_RESULT_CHOOSING) {
            func_802A48FC();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_STRATEGIES_4;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_5;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_6;
            switch (battleStatus->curPartnerSubmenu) {
                case BTL_MENU_TYPE_DO_NOTHING:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_6;
                    btl_state_update_partner_menu();
                    btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
                    break;
                case BTL_MENU_TYPE_RUN_AWAY:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_6;
                    btl_state_update_partner_menu();
                    battleStatus->moveCategory = BTL_MENU_TYPE_RUN_AWAY;
                    battleStatus->selectedMoveID = MOVE_UNUSED_39;
                    btl_set_state(BATTLE_STATE_RUN_AWAY);
                    break;
                case BTL_MENU_TYPE_ACT_LATER:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_6;
                    btl_state_update_partner_menu();
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
                    break;
            }
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_4:
        btl_update_strats_menu();
        if (btl_main_menu_update() != 0) {
            D_802ACC60 = UNK_MENU_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_MENU_1;
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_5:
        func_802A48FC();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_STRATEGIES_4;
        break;
    case BTL_SUBSTATE_STRATEGIES_6:
        func_802A472C();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_1:
        popupIndex = 0;
        for (i = 1; i < ARRAY_COUNT(PartnerIDFromMenuIndex); i++) {
            s32 partnerId = PartnerIDFromMenuIndex[i];
            if (playerData->partners[partnerId].enabled) {
                popupProps = &gPartnerPopupProperties[partnerId];
                popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].enabled;
                popupMenu->enabled[popupIndex] = TRUE;
                popupMenu->userIndex[popupIndex] = partnerId;
                popupMenu->nameMsg[popupIndex] = popupProps->nameMsg;
                popupMenu->descMsg[popupIndex] = popupProps->battleDescMsg;
                popupMenu->value[popupIndex] = playerData->partners[partnerId].level;
                if (playerData->curPartner == partnerId) {
                    popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].disabled;
                    popupMenu->enabled[popupIndex] = FALSE;
                }
                popupIndex++;
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = 0;
        }
        popupMenu->popupType = POPUP_MENU_SWITCH_PARTNER;
        popupMenu->numEntries = popupIndex;
        popupMenu->initialPos = MenuIndexFromPartnerID[playerData->curPartner] - 1;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        create_battle_popup_menu(popupMenu);
        func_800F52BC();
        gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_2;
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_2:
        if (popupMenu->result == POPUP_RESULT_INVALID) {
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_7;
        } else if (popupMenu->result != POPUP_RESULT_CHOOSING) {
            if (popupMenu->result == POPUP_RESULT_CANCEL) {
                func_802A47E0();
                gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
            } else {
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_5;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_6;
                battleStatus->unk_1AC = popupMenu->userIndex[popupMenu->result - 1];
                battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                battleStatus->selectedMoveID = MOVE_UNUSED_37;
                battleStatus->curTargetListFlags = TARGET_FLAG_2;
                battleStatus->moveArgument = battleStatus->unk_1AC;
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = popupMenu->result - 1;
                hide_popup_menu();
                func_802A4718();
                func_802A1030();
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_3;
            }
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_3:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && popupMenu->result == POPUP_RESULT_CHOOSING) {
            func_800F16CC();
            func_802A4A10();
            func_802A1098();
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_4;
        } else {
            btl_update_strats_menu();
            if (btl_main_menu_update() != 0) {
                gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                btl_state_update_partner_menu();
                btl_set_state(BATTLE_STATE_CHANGE_PARTNER);
            }
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_4:
        btl_update_strats_menu();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_2;
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_5:
        func_800F16CC();
        func_802A4A10();
        func_802A1098();
        gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_4;
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_6:
        destroy_popup_menu();
        func_802A472C();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_7:
        set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
        if (popupMenu->result != POPUP_RESULT_INVALID) {
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_9);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_9);
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_2;
        }
        break;
    }
}

void btl_state_draw_partner_menu(void) {
    switch (gBattleSubState) {
        case BTL_SUBSTATE_MAIN_MENU_1:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_MAIN_MENU_2:
        case BTL_SUBSTATE_MAIN_MENU_3:
        case BTL_SUBSTATE_MAIN_MENU_4:
        case BTL_SUBSTATE_MAIN_MENU_5:
        case BTL_SUBSTATE_ABILITIES_1:
        case BTL_SUBSTATE_ABILITIES_2:
        case BTL_SUBSTATE_ABILITIES_3:
        case BTL_SUBSTATE_ABILITIES_4:
        case BTL_SUBSTATE_ABILITIES_5:
        case BTL_SUBSTATE_UNKNOWN_1:
        case BTL_SUBSTATE_UNKNOWN_2:
        case BTL_SUBSTATE_UNKNOWN_3:
        case BTL_SUBSTATE_UNKNOWN_4:
        case BTL_SUBSTATE_UNKNOWN_5:
        case BTL_SUBSTATE_CHANGE_PARTNER_1:
        case BTL_SUBSTATE_CHANGE_PARTNER_2:
        case BTL_SUBSTATE_CHANGE_PARTNER_3:
        case BTL_SUBSTATE_CHANGE_PARTNER_4:
        case BTL_SUBSTATE_CHANGE_PARTNER_5:
        case BTL_SUBSTATE_ITEMS_BUILD_MENU:
        case BTL_SUBSTATE_ITEMS_CHOOSING:
        case BTL_SUBSTATE_ITEMS_PREP_TARGET_SELECT:
        case BTL_SUBSTATE_ITEMS_REOPEN_MENU:
        case BTL_SUBSTATE_ITEMS_TARGET_CANCELED:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_2:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_3:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_4:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_5:
        case BTL_SUBSTATE_FOCUS_CHOOSING:
        case BTL_SUBSTATE_FOCUS_3:
        case BTL_SUBSTATE_FOCUS_REOPEN_MENU:
        case BTL_SUBSTATE_FOCUS_CANCELED:
        case BTL_SUBSTATE_FOCUS_SELECTED:
        case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
        case BTL_SUBSTATE_STRATEGIES_CHOOSING:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_3:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_4:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_5:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_6:
            btl_main_menu_draw();
            break;
    }
}
