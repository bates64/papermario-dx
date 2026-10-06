#pragma once

/// @file tik_15.h
/// @brief Toad Town Tunnels - Rip Cheato's Home (B3)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_15_shape.h"
#include "mapfs/tik_15_hit.h"

enum {
    NPC_RipCheato               = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
