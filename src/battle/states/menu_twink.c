#include "states.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"
#include "sprite/npc/Twink.h"

enum {
    // BTL_SUBSTATE_INIT                        = 0,
    BTL_SUBSTATE_CHOOSE_CATEGORY                = 1,
    BTL_SUBSTATE_CHOOSE_TARGET                  = 2,
    BTL_SUBSTATE_UNUSED_3                       = 3,
    BTL_SUBSTATE_TARGET_CANCEL                  = 4,
    BTL_SUBSTATE_TARGET_CHOSEN                  = 5,
    BTL_SUBSTATE_UNUSED_6                       = 6,
    BTL_SUBSTATE_UNUSED_7                       = 7,
    BTL_SUBSTATE_SHOW_CANT_SWITCH               = 8,
    BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP        = 9,
    BTL_SUBSTATE_SWAP_PEACH_BACK                = 10,
    BTL_SUBSTATE_CREATE_MAIN_MENU               = 11,
};

IconHudScriptPair TwinkStarPowerHudScripts = { &HES_MenuStarPower, &HES_MenuStarPowerDisabled };

s32 TwinkMenuMessages[] = {
    MSG_Menus_Dash_Centered,
};

void btl_state_update_twink_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 selection;
    s32 shouldSkipTurn;
    s32 initialPos;
    s32 entryIdx;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            shouldSkipTurn = FALSE;

            switch (player->debuff) {
                case STATUS_KEY_SLEEP:
                case STATUS_KEY_FEAR:
                case STATUS_KEY_DIZZY:
                case STATUS_KEY_PARALYZE:
                case STATUS_KEY_FROZEN:
                case STATUS_KEY_STOP:
                    shouldSkipTurn = TRUE;
                    break;
                default:
                    break;
            }

            if (player->stoneStatus == STATUS_KEY_STONE) {
                shouldSkipTurn = TRUE;
            }

            if (player->koStatus == STATUS_KEY_DAZE) {
                shouldSkipTurn = TRUE;
            }

            if (shouldSkipTurn) {
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                break;
            }

            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(10);
            if (!(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK)) {
                // if the player (Peach) is in front, we need to swap her to the back before opening the menu
                player->state.curPos.x = player->homePos.x;
                player->state.curPos.z = player->homePos.z;
                player->state.goalPos.x = partner->homePos.x;
                player->state.goalPos.z = partner->homePos.z;
                player->state.moveTime = 4;
                player->state.angle = 0.0f;
                gBattleSubState = BTL_SUBSTATE_SWAP_PEACH_BACK;
            } else {
                gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
            }
            break;
        case BTL_SUBSTATE_SWAP_PEACH_BACK:
            if (player->state.moveTime != 0) {
                player->curPos.x += (player->state.goalPos.x - player->curPos.x) / player->state.moveTime;
                player->curPos.z += (player->state.goalPos.z - player->curPos.z) / player->state.moveTime;
                partner->curPos.x += (player->state.curPos.x - partner->curPos.x) / player->state.moveTime;
                partner->curPos.z += (player->state.curPos.z - partner->curPos.z) / player->state.moveTime;
            }
            player->curPos.z += sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
            player->yaw = clamp_angle(-player->state.angle);
            partner->curPos.z -= sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
            partner->yaw = clamp_angle(-player->state.angle);
            player->state.angle += 90.0f;
            if (player->state.moveTime != 0) {
                player->state.moveTime--;
                break;
            }
            player->curPos.x = player->state.goalPos.x;
            player->curPos.z = player->state.goalPos.z;
            partner->curPos.x = player->state.curPos.x;
            partner->curPos.z = player->state.curPos.z;
            player->homePos.x = player->curPos.x;
            player->homePos.z = player->curPos.z;
            partner->homePos.x = partner->curPos.x;
            partner->homePos.z = partner->curPos.z;
            gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
            // fallthrough
        case BTL_SUBSTATE_CREATE_MAIN_MENU:
            gBattleStatus.flags1 |= BS_FLAGS1_MENU_OPEN;
            player->flags &= ~ACTOR_FLAG_USING_IDLE_ANIM;
            player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partner != NULL) {
                partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
                partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            }

            // add main menu entry for star powers
            entryIdx = 0;
            battleStatus->selectedMoveID = MOVE_NONE;
            battle_menu_submenuIDs[entryIdx] = BTL_MENU_TYPE_STAR_POWERS;
            BattleMenu_OptionEnabled[entryIdx] = TRUE;
            battle_menu_isMessageDisabled[entryIdx] = 0;
            BattleMenu_HudScripts[entryIdx] = TwinkStarPowerHudScripts.enabled;
            BattleMenu_TitleMessages[entryIdx] = TwinkMenuMessages[entryIdx];
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STAR_POWERS)) {
                BattleMenu_OptionEnabled[entryIdx] = FALSE;
                battle_menu_isMessageDisabled[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                BattleMenu_HudScripts[entryIdx] = TwinkStarPowerHudScripts.disabled;
            }
            entryIdx++;

            initialPos = 0;
            BattleMenu_NumOptions = entryIdx;
            D_802AD0A8 = 0;
            D_802AD0B0 = initialPos;
            D_802AD100 = 2 - initialPos;

            if (gBattleStatus.flags2 & BS_FLAGS2_PLAYER_TURN_USED) {
                BattleMenu_ShowSwapIcons = FALSE;
            } else {
                BattleMenu_ShowSwapIcons = TRUE;
            }

            btl_main_menu_init();
            D_802ACC60 = UNK_MENU_DELAY;
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            break;
        case BTL_SUBSTATE_CHOOSE_CATEGORY:
            set_actor_anim(ACTOR_PARTNER, 0, ANIM_Twink_Idle);
            selection = btl_main_menu_update();
            if (D_802ACC60 != 0) {
                D_802ACC60--;
                break;
            }
            if (selection != 0) {
                set_actor_anim(ACTOR_PARTNER, 0, ANIM_Twink_Angry);
                battleStatus->curSubmenu = battle_menu_submenuIDs[selection - 1];
                func_802A1030();
                D_802ACC60 = UNK_MENU_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_CHOOSE_TARGET;
            }
            break;
        case BTL_SUBSTATE_CHOOSE_TARGET:
            if (btl_main_menu_update() != 0) {
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_TARGET_CHOSEN;
                battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                battleStatus->selectedMoveID = MOVE_TWINK_DASH;
                battleStatus->moveArgument = 0;
                battleStatus->curTargetListFlags = gMoveTable[MOVE_TWINK_DASH].flags;
                btl_set_state(BATTLE_STATE_SELECT_TARGET);
            }
            break;
        case BTL_SUBSTATE_TARGET_CANCEL:
            func_802A1050();
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            btl_state_update_twink_menu();
            btl_state_update_twink_menu();
            break;
        case BTL_SUBSTATE_TARGET_CHOSEN:
            btl_main_menu_destroy();
            break;
        case BTL_SUBSTATE_SHOW_CANT_SWITCH:
            btl_show_variable_battle_message(BTL_MSG_CANT_SWITCH, 60, 0);
            ShowingErrorMessage = TRUE;
            gBattleSubState = BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP;
            break;
        case BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP:
            if (btl_is_popup_displayed()) {
                break;
            }
            ShowingErrorMessage = FALSE;
            D_802ACC60 = 0;
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            break;
    }
}

void btl_state_draw_twink_menu(void) {
    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHOOSE_CATEGORY:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_CHOOSE_TARGET:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_UNUSED_3:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_TARGET_CANCEL:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_TARGET_CHOSEN:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_UNUSED_6:
        case BTL_SUBSTATE_UNUSED_7:
        case BTL_SUBSTATE_SHOW_CANT_SWITCH:
        case BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP:
            break;
    }
}
