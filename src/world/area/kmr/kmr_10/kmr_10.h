#pragma once

/// @file kmr_10.h
/// @brief Goomba Region - Toad Town Entrance

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "mapfs/kmr_10_shape.h"
#include "mapfs/kmr_10_hit.h"

#include "sprite/npc/Toad.h"

enum {
    NPC_Dummy   = 0, // for controlling the spring as it falls from the tree
};

enum {
    MV_EntityID_Spring      = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_OnShakeTree1;
extern NpcGroupList DefaultNPCs;
