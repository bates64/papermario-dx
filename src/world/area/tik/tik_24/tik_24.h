#pragma once

/// @file tik_24.h
/// @brief Toad Town Tunnels - Hall to Ultra Boots (B3)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_18_shape.h"
#include "mapfs/tik_18_hit.h"

enum {
    NPC_DarkTroopa_01       = 0,
    NPC_DarkTroopa_02       = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
