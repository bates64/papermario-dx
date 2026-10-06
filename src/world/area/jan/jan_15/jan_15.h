#pragma once

/// @file jan_15.h
/// @brief Jade Jungle - Deep Jungle 4 (Ambush)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "mapfs/jan_15_shape.h"
#include "mapfs/jan_15_hit.h"

#include "sprite/npc/LargePiranha.h"

enum {
    NPC_PutridPiranha_01        = 0,
    NPC_PutridPiranha_02        = 1,
    NPC_PutridPiranha_03        = 2,
    NPC_HeartPlant_01           = 3,
    NPC_HeartPlant_02           = 4,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList DefaultNPCs;
