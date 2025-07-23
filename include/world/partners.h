#ifndef _WORLD_PARTNERS_H
#define _WORLD_PARTNERS_H

#include "npc.h"

extern Npc* wPartnerNpc;

s32 partner_init_get_out(Npc*);
s32 partner_get_out(Npc*);
s32 partner_init_put_away(Npc* partner);
s32 partner_put_away(Npc* partner);
s32 partner_can_use_ability(void);
s32 partner_use_ability(void);
bool partner_dismount(void);
void partner_do_player_collision(Npc* partner);
void partner_walking_follow_player(Npc* partner);
s32 func_800EA52C(s32);
s32 partner_force_player_flip_done(void);
void partner_suspend_ability_script(void);
void partner_resume_ability_script(void);
void partner_enable_input(void);

#endif
