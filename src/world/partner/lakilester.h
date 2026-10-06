#ifndef _WORLD_PARTNER_LAKILESTER_H_
#define _WORLD_PARTNER_LAKILESTER_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
void pre_battle(Npc*);
void post_battle(Npc*);

void sync_player_position(void);

extern EvtScript EVS_WorldLakilester_TakeOut;
extern EvtScript EVS_WorldLakilester_Update;
extern EvtScript EVS_WorldLakilester_UseAbility;
extern EvtScript EVS_WorldLakilester_PutAway;
extern EvtScript EVS_WorldLakilester_EnterMap;

#endif
