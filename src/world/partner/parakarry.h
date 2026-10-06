#ifndef _WORLD_PARTNER_PARAKARRY_H_
#define _WORLD_PARTNER_PARAKARRY_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
void pre_battle(Npc*);
void post_battle(Npc*);

extern EvtScript EVS_WorldParakarry_TakeOut;
extern EvtScript EVS_WorldParakarry_Update;
extern EvtScript EVS_WorldParakarry_UseAbility;
extern EvtScript EVS_WorldParakarry_PutAway;

#endif
