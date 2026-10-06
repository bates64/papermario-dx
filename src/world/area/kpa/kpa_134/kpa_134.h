#pragma once

/// @file kpa_134.h
/// @brief Bowser's Castle - Right Water Puzzle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "mapfs/kpa_134_shape.h"
#include "mapfs/kpa_134_hit.h"

#include "sprite/npc/Toad.h"

enum {
    NPC_Dummy   = 0,
};

enum {
    MV_SwitchEntityID   = MapVar(0),
    MV_EntityID_Padlock  = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_kpa_130_0;
extern EvtScript EVS_SetupChains;
extern EvtScript EVS_FlipWallPanels;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
