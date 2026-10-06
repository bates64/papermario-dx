#pragma once

/// @file flo_15.h
/// @brief Flower Fields - (NW) Sun Tower

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_15_shape.h"
#include "mapfs/flo_15_hit.h"

#include "sprite/npc/Sun.h"

enum {
    NPC_Sun_01                  = 10,
    NPC_Sun_02                  = 11,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_MonitorFallingStairs;
extern EvtScript EVS_Scene_SunReturns;
extern NpcGroupList DefaultNPCs;
