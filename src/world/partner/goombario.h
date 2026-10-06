#ifndef _WORLD_PARTNER_GOOMBARIO_H_
#define _WORLD_PARTNER_GOOMBARIO_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc* partner);
s32 can_open_menus(Npc* partner);
void pre_battle(Npc* partner);

extern EvtScript EVS_WorldGoombario_TakeOut;
extern EvtScript EVS_WorldGoombario_Update;
extern EvtScript EVS_WorldGoombario_UseAbility;
extern EvtScript EVS_WorldGoombario_PutAway;

#endif
