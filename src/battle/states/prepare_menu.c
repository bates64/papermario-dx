#include "states.h"
#include "battle/menu.h"
#include "dx/overlay.h"

static Overlay* LoadedBattleMenuOverlay;
static const BattleMenuInterface* LoadedBattleMenu;

void load_battle_menu(void) {
    if (LoadedBattleMenu != nullptr) {
        return;
    }

    ASSERT_MSG(LoadedBattleMenuOverlay == nullptr,
               "Battle menu overlay loaded without an interface");

    LoadedBattleMenuOverlay = ovl_load("battle_menu", OVL_BATTLE_MENU);
    LoadedBattleMenu = ovl_import(LoadedBattleMenuOverlay, BATTLE_MENU_EXPORT_NAME);
    ASSERT_MSG(LoadedBattleMenu != nullptr,
               "Battle menu overlay has no %s export", BATTLE_MENU_EXPORT_NAME);
    ASSERT_MSG(LoadedBattleMenu->update != nullptr && LoadedBattleMenu->draw != nullptr,
               "Battle menu overlay has an incomplete interface");
}

void unload_battle_menu(void) {
    ovl_unload(LoadedBattleMenuOverlay);
    LoadedBattleMenuOverlay = nullptr;
    LoadedBattleMenu = nullptr;
}

void update_battle_menu(s32 state) {
    ASSERT_MSG(LoadedBattleMenu != nullptr, "No battle menu overlay is loaded");
    LoadedBattleMenu->update(state);
}

void draw_battle_menu(s32 state) {
    ASSERT_MSG(LoadedBattleMenu != nullptr, "No battle menu overlay is loaded");
    LoadedBattleMenu->draw(state);
}

void btl_state_update_prepare_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;

    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_JUMP] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_SMASH] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_ITEMS] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_PARTNER] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STAR_POWER] = -1;
    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY] = -1;
    battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] = -1;
    battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] = -1;
    battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = -1;

    load_battle_menu();

    if (battleStatus->flags1 & BS_FLAGS1_PARTNER_ACTING) {
        btl_set_state(BATTLE_STATE_PARTNER_MENU);
    } else if (gBattleSubState == BTL_SUBSTATE_PLAYER_CONTINUE_DIP) {
        btl_set_state(BATTLE_STATE_PLAYER_MENU);
        gBattleSubState = BTL_SUBSTATE_PLAYER_CONTINUE_DIP; // maintain substate
    } else {
        btl_set_state(BATTLE_STATE_PLAYER_MENU);
    }
}

void btl_state_draw_prepare_menu(void) {
}
