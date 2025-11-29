#include "states.h"

void btl_state_update_switch_to_partner(void) {
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        reset_actor_turn_info();
        gBattleStatus.flags1 |= BS_FLAGS1_PARTNER_ACTING;
        gBattleStatus.selectedMoveID = MOVE_NONE;
        gBattleStatus.actionResult = ACTION_RESULT_NONE;
        gBattleStatus.blockResult = BLOCK_RESULT_NONE;
        gBattleStatus.flags1 |= BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
        player->flags |= (ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
        partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;

        for (i = 0; i < ARRAY_COUNT(gBattleStatus.enemyActors); i++) {
            Actor* enemy = gBattleStatus.enemyActors[i];
            if (enemy != NULL) {
                enemy->flags |= ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
        }

        btl_set_state(BATTLE_STATE_PREPARE_MENU);
    }
}

void btl_state_draw_switch_to_partner(void) {
}
