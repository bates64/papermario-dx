#pragma once

/// @file tik_20.h
/// @brief Toad Town Tunnels - Room with Spikes (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_20_shape.h"
#include "mapfs/tik_20_hit.h"

enum {
    NPC_DarkTroopa_01          = 0,
    NPC_DarkTroopa_02          = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;
