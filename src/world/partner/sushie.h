#ifndef _WORLD_PARTNER_SUSHIE_H_
#define _WORLD_PARTNER_SUSHIE_H_

#include "common.h"
#include "script_api/map.h"

void init(Npc*);
void pre_battle(Npc*);
void post_battle(Npc*);

void sync_player_position(void);

extern EvtScript EVS_WorldSushie_TakeOut;
extern EvtScript EVS_WorldSushie_Update;
extern EvtScript EVS_WorldSushie_UseAbility;
extern EvtScript EVS_WorldSushie_PutAway;
extern EvtScript EVS_WorldSushie_EnterMap;

#endif
