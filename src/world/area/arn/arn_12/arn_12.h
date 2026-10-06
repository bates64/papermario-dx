#pragma once

/// @file arn_12.h
/// @brief Gusty Gulch - Tunnel 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "mapfs/arn_12_shape.h"
#include "mapfs/arn_12_hit.h"

enum {
    NPC_TubbasHeart     = 0,
    NPC_HyperGoomba     = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
