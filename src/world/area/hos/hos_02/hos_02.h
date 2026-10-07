#pragma once

/// @file hos_02.h
/// @brief Shooting Star Summit - Star Way

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "map.xml.h"

enum {
    NPC_Ember_01    = 0,
    NPC_Ember_02    = 1,
    NPC_Ember_03    = 2,
};

enum {
    MV_StarWarpEffect   = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupModelFX;
extern EvtScript EVS_DescendStarWarp;
extern EvtScript EVS_SetupUnused;
extern NpcGroupList DefaultNPCs;

API_CALLABLE(SetStarWarpIdleParams);
API_CALLABLE(SetStarWarpTravelParams);
