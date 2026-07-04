#pragma once

/// @file hos_02.h
/// @brief Shooting Star Summit - Star Way

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "mapfs/hos_02_shape.h"
#include "mapfs/hos_02_hit.h"

enum {
    NPC_Ember_01    = 0,
    NPC_Ember_02    = 1,
    NPC_Ember_03    = 2,
};

enum {
    MV_StarWarpEffect   = MapVar(10),
};

#define NAMESPACE hos_02

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupModelFX);
extern EvtScript N(EVS_DescendStarWarp);
extern EvtScript N(EVS_SetupUnused);
extern NpcGroupList N(DefaultNPCs);

API_CALLABLE(N(SetStarWarpIdleParams));
API_CALLABLE(N(SetStarWarpTravelParams));
