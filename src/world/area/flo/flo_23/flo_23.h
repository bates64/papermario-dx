#pragma once

/// @file flo_23.h
/// @brief Flower Fields - (West) Path to Maze

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_23_shape.h"
#include "mapfs/flo_23_hit.h"

enum {
    NPC_Spiny_01                = 0,
    NPC_Spiny_02                = 1,
    NPC_GateFlower              = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
