#pragma once

#include "common.h"
#include "script_api/map.h"

void world_twink_init(Npc* partner);

extern EvtScript EVS_WorldTwink_TakeOut;
extern EvtScript EVS_WorldTwink_Update;
extern EvtScript EVS_WorldTwink_UseAbility;
extern EvtScript EVS_WorldTwink_PutAway;
