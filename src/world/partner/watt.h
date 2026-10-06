#ifndef _WORLD_PARTNER_WATT_H_
#define _WORLD_PARTNER_WATT_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
void pre_battle(Npc*);
void post_battle(Npc*);

void sync_held_position(void);

extern EvtScript EVS_WorldWatt_TakeOut;
extern EvtScript EVS_WorldWatt_Update;
extern EvtScript EVS_WorldWatt_UseAbility;
extern EvtScript EVS_WorldWatt_PutAway;
extern EvtScript EVS_WorldWatt_EnterMap;

#endif
