#ifndef _WORLD_BOMBETTE_H_
#define _WORLD_BOMBETTE_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
s32 test_first_strike(Npc*, Npc*);
s32 can_use_ability(Npc* npc);
s32 can_open_menus(Npc* );
void pre_battle(Npc*);

extern EvtScript EVS_WorldBombette_TakeOut;
extern EvtScript EVS_WorldBombette_Update;
extern EvtScript EVS_WorldBombette_UseAbility;
extern EvtScript EVS_WorldBombette_PutAway;

#endif
