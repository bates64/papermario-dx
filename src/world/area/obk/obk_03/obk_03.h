#pragma once

/// @file obk_03.h
/// @brief Boo's Mansion - Basement

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "mapfs/obk_03_shape.h"
#include "mapfs/obk_03_hit.h"

#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Boo.h"

enum {
    NPC_Igor    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupShop;
extern EvtScript EVS_SetupStairs;
extern EvtScript EVS_SetupRockingChair;
extern EvtScript EVS_Scene_DropSteps;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
