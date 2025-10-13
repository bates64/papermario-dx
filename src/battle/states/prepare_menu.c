#include "states.h"
#include "ld_addrs.h"

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

    DMA_COPY_SEGMENT(btl_states_menus);

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
