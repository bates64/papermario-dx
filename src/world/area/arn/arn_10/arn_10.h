#pragma once

/// @file arn_10.h
/// @brief Gusty Gulch - Tunnel 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "mapfs/arn_10_shape.h"
#include "mapfs/arn_10_hit.h"

enum {
    NPC_TubbasHeart     = 0,
    NPC_HyperGoomba     = 1,
};

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
