#include "states.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"
#include "sprite/player.h"

enum {
    // BTL_SUBSTATE_INIT                        = 0,
    BTL_SUBSTATE_CHOOSE_CATEGORY                = 1,
    BTL_SUBSTATE_CHOOSE_TARGET                  = 2,
    BTL_SUBSTATE_TARGET_CANCEL                  = 4,
    BTL_SUBSTATE_TARGET_CHOSEN                  = 5,
    BTL_SUBSTATE_SHOW_CANT_SWITCH               = 8,
    BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP        = 9,
    BTL_SUBSTATE_SWAP_PEACH_FRONT               = 10,
    BTL_SUBSTATE_CREATE_MAIN_MENU               = 11,
};

IconHudScriptPair PeachStarPowerHudScripts = { &HES_MenuStarPower, &HES_MenuStarPowerDisabled };

s32 PeachMenuMessages[] = {
    MSG_Menus_Focus_Centered,
};

void btl_state_update_peach_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 selectedOption;
    s32 initialPos;
    s32 entryIdx;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(10);
            if (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
                // if the player (Peach) is in back, we need to swap her to the front before opening the menu
                player->state.curPos.x = player->homePos.x;
                player->state.curPos.z = player->homePos.z;
                player->state.goalPos.x = partner->homePos.x;
                player->state.goalPos.z = partner->homePos.z;
                player->state.moveTime = 4;
                player->state.angle = 0.0f;
                gBattleSubState = BTL_SUBSTATE_SWAP_PEACH_FRONT;
            } else {
                gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
            }
            break;
        case BTL_SUBSTATE_SWAP_PEACH_FRONT:
            if (player->state.moveTime != 0) {
                player->curPos.x += (player->state.goalPos.x - player->curPos.x) / player->state.moveTime;
                player->curPos.z += (player->state.goalPos.z - player->curPos.z) / player->state.moveTime;
                partner->curPos.x += (player->state.curPos.x - partner->curPos.x) / player->state.moveTime;
                partner->curPos.z += (player->state.curPos.z - partner->curPos.z) / player->state.moveTime;
            }

            player->curPos.z -= sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
            player->yaw = clamp_angle(-player->state.angle);
            partner->curPos.z += sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
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
            gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
            // fallthrough
        case BTL_SUBSTATE_CREATE_MAIN_MENU:
            gBattleStatus.flags1 |= BS_FLAGS1_MENU_OPEN;
            player->flags &= ~ACTOR_FLAG_USING_IDLE_ANIM;
            player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partner != nullptr) {
                partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
                partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            }

            // add main menu entry for star powers
            entryIdx = 0;
            battleStatus->selectedMoveID = MOVE_NONE;
            WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_STAR_POWERS;
            WheelOptionEnabled[entryIdx] = true;
            WheelOptionError[entryIdx] = 0;
            WheelOptionHudScript[entryIdx] = PeachStarPowerHudScripts.enabled;
            WheelOptionName[entryIdx] = PeachMenuMessages[entryIdx];
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STAR_POWERS)) {
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                WheelOptionHudScript[entryIdx] = PeachStarPowerHudScripts.disabled;
            }
            entryIdx++;

            initialPos = 0;
            WheelOptionCount = entryIdx;
            BattleMenu_PrevSelected = initialPos;
            BattleMenu_WheelBase = 2 - initialPos;

            if (gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED) {
                BattleMenu_ShowSwapIcons = false;
            } else {
                BattleMenu_ShowSwapIcons = true;
            }

            btl_main_menu_init();
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            break;
        case BTL_SUBSTATE_CHOOSE_CATEGORY:
            set_actor_anim(ACTOR_PLAYER, 0, ANIM_Peach2_Delighted);
            selectedOption = btl_main_menu_update();
            if (BattleMenu_ChooseDelay != 0) {
                BattleMenu_ChooseDelay--;
                break;
            }
            if (selectedOption != 0) {
                set_actor_anim(ACTOR_PLAYER, 0, ANIM_Peach1_Walk);
                battleStatus->curSubmenu = WheelOptionSubmenu[selectedOption - 1];
                btl_main_menu_hide();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_CHOOSE_TARGET;
            }
            break;
        case BTL_SUBSTATE_CHOOSE_TARGET:
            if (btl_main_menu_update() != 0) {
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_TARGET_CHOSEN;
                battleStatus->curTargetListFlags = gMoveTable[MOVE_PEACH_FOCUS].flags;
                battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                battleStatus->selectedMoveID = MOVE_PEACH_FOCUS;
                battleStatus->moveArgument = STAR_POWER_INDEX(MOVE_PEACH_FOCUS);
                btl_set_state(BATTLE_STATE_SELECT_TARGET);
            }
            break;
        case BTL_SUBSTATE_TARGET_CANCEL:
            btl_main_menu_resume_choose();
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            btl_state_update_peach_menu();
            btl_state_update_peach_menu();
            break;
        case BTL_SUBSTATE_TARGET_CHOSEN:
            btl_main_menu_destroy();
            break;
        case BTL_SUBSTATE_SHOW_CANT_SWITCH:
            btl_show_variable_battle_message(BTL_MSG_CANT_SWITCH, 60, 0);
            ShowingErrorMessage = true;
            gBattleSubState = BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP;
            break;
        case BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP:
            if (btl_is_popup_displayed()) {
                break;
            }
            ShowingErrorMessage = false;
            BattleMenu_ChooseDelay = 0;
            gBattleSubState = BTL_SUBSTATE_CHOOSE_CATEGORY;
            break;
    }
}

void btl_state_draw_peach_menu(void) {
    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHOOSE_CATEGORY:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_CHOOSE_TARGET:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_TARGET_CANCEL:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_TARGET_CHOSEN:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_SHOW_CANT_SWITCH:
        case BTL_SUBSTATE_AWAIT_CANT_SWITCH_POPUP:
            break;
    }
}
