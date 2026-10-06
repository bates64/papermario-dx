#pragma once

/// @file iwa_04.h
/// @brief Mt Rugged - Suspension Bridge

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../iwa.h"
#include "mapfs/iwa_04_shape.h"
#include "mapfs/iwa_04_hit.h"

#include "sprite/npc/Buzzar.h"

enum {
    NPC_Cleft       = 0,
    NPC_Buzzar      = 1,
};

enum {
    MV_PlayerCliffLevel     = MapVar(9),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
