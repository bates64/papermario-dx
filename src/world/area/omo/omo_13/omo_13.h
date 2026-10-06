#pragma once

/// @file omo_13.h
/// @brief Shy Guy's Toybox - BLU Anti-Guy Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_13_shape.h"
#include "mapfs/omo_13_hit.h"

#include "sprite/npc/ShyGuy.h"
#include "sprite/npc/GrooveGuy.h"

enum {
    NPC_AntiGuy     = 0,
    NPC_ShyGuy      = 1,
    NPC_GrooveGuy   = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGizmos;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
