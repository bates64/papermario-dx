#pragma once

/// @file omo_05.h
/// @brief Shy Guy's Toybox - PNK Gourmet Guy Crossing

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_05_shape.h"
#include "mapfs/omo_05_hit.h"

#include "sprite/npc/GourmetGuy.h"
#include "sprite/npc/GrooveGuy.h"

enum {
    NPC_GourmetGuy          = 0,
    NPC_GourmetGuy_Knife    = 1,
    NPC_GourmetGuy_Fork     = 2,
    NPC_GrooveGuy           = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGizmos;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
