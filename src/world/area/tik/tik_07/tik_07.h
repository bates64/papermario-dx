#pragma once

/// @file tik_07.h
/// @brief Toad Town Tunnels - Elevator Attic Room (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_07_shape.h"
#include "mapfs/tik_07_hit.h"

enum {
    NPC_Paragoomba_01           = 0,
    NPC_Paragoomba_02           = 1,
};

enum {
    MV_SuperBlock       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupPlatforms;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupDrips;
extern NpcGroupList DefaultNPCs;
