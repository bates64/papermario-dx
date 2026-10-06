#pragma once

/// @file tik_18.h
/// @brief Toad Town Tunnels - Hall to Blooper 1 (B1)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_18_shape.h"
#include "mapfs/tik_18_hit.h"

enum {
    NPC_Gloomba             = 0,
    NPC_SpikedGloomba       = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
