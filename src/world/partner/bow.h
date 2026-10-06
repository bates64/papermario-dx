#ifndef _WORLD_PARTNER_BOW_H_
#define _WORLD_PARTNER_BOW_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
void pre_battle(Npc*);

extern EvtScript EVS_WorldBow_TakeOut;
extern EvtScript EVS_WorldBow_Update;
extern EvtScript EVS_WorldBow_UseAbility;
extern EvtScript EVS_WorldBow_PutAway;

#endif
