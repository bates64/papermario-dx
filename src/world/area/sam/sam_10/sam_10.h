#pragma once

/// @file sam_10.h
/// @brief Mt Shiver - Shiver Mountain Peaks

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sam.h"
#include "mapfs/sam_10_shape.h"
#include "mapfs/sam_10_hit.h"

enum {
    NPC_FrostClubba         = 0,
    NPC_FrostClubba_Hitbox  = 1,
};

enum {
    MV_StarStoneItemID  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupStairs;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
