#ifndef _BATTLE_STATES_H_
#define _BATTLE_STATES_H_

#include "common.h"

enum BattleSubStates {
    // shared
    BTL_SUBSTATE_INIT                                       = 0,

    // accessed across states
    BTL_SUBSTATE_END_BATTLE_EXEC_STAGE_SCRIPT               = 2,
    BTL_SUBSTATE_PLAYER_CONTINUE_DIP                        = 70,
};

extern s16 EndDemoWhiteOut;
extern b32 BattleSkipActorTurn;
extern b32 BattleCanShowFirstStrike;
extern s32 BattleStatusUpdateDelay;
extern s32 BattleSubstateDelay;
extern s32 BattleScreenFadeAmt;

void btl_state_update_normal_start(void);
void btl_state_draw_normal_start(void);
void btl_state_update_begin_turn(void);
void btl_state_draw_begin_turn(void);
void btl_state_update_begin_player_turn(void);
void btl_state_draw_begin_player_turn(void);
void btl_state_update_switch_to_player(void);
void btl_state_draw_switch_to_player(void);
void btl_state_update_begin_partner_turn(void);
void btl_state_draw_begin_partner_turn(void);
void btl_state_update_switch_to_partner(void);
void btl_state_draw_switch_to_partner(void);
void btl_state_update_transfer_turn(void);
void btl_state_draw_transfer_turn(void);
void btl_state_update_prepare_menu(void);
void btl_state_draw_prepare_menu(void);
void btl_state_update_end_turn(void);
void btl_state_draw_end_turn(void);
void btl_state_update_victory(void);
void btl_state_draw_victory(void);
void btl_state_update_end_training_battle(void);
void btl_state_draw_end_training_battle(void);
void btl_state_update_end_battle(void);
void btl_state_draw_end_battle(void);
void btl_state_update_defend(void);
void btl_state_draw_defend(void);
void btl_state_update_run_away(void);
void btl_state_draw_run_away(void);
void btl_state_update_defeat(void);
void btl_state_draw_defeat(void);
void btl_state_update_change_partner(void);
void btl_state_draw_change_partner(void);
void btl_state_update_player_move(void);
void btl_state_draw_player_move(void);
void btl_state_update_end_player_turn(void);
void btl_state_update_partner_move(void);
void btl_state_draw_end_player_turn(void);
void btl_state_draw_partner_move(void);
void btl_state_update_end_partner_turn(void);
void btl_state_draw_end_partner_turn(void);
void btl_state_update_next_enemy(void);
void btl_state_draw_next_enemy(void);
void btl_state_update_enemy_move(void);
void btl_state_draw_enemy_move(void);
void btl_state_update_first_strike(void);
void btl_state_draw_first_stike(void);
void btl_state_update_partner_striking_first(void);
void btl_state_draw_partner_striking_first(void);
void btl_state_update_enemy_striking_first(void);
void btl_state_draw_enemy_striking_first(void);
void btl_state_update_end_demo_battle(void);
void btl_state_draw_end_demo_battle(void);

void btl_state_update_player_menu(void);
void btl_state_draw_player_menu(void);
void btl_state_update_partner_menu(void);
void btl_state_draw_partner_menu(void);
void btl_state_update_peach_menu(void);
void btl_state_draw_peach_menu(void);
void btl_state_update_twink_menu(void);
void btl_state_draw_twink_menu(void);
void btl_state_update_select_target(void);
void btl_state_draw_select_target(void);

void btl_state_update_celebration(void);
void btl_state_draw_celebration(void);

#endif
