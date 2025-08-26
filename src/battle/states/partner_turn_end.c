#include "states.h"

void btl_state_update_end_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
        if (btl_check_enemies_defeated()) {
            return;
        }
        battleStatus->flags1 &= ~BS_FLAGS1_PARTNER_ACTING;
        battleStatus->flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;

        if (battleStatus->unk_94 < 0) {
            battleStatus->unk_94 = 0;
            btl_set_state(BATTLE_STATE_END_TURN);
        } else {
            btl_set_state(BATTLE_STATE_9);
        }
    }
}

void btl_state_draw_end_partner_turn(void) {
}
