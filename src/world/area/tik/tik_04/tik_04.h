#pragma once

/// @file tik_04.h
/// @brief Toad Town Tunnels - Scales Room (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_04_shape.h"
#include "mapfs/tik_04_hit.h"

enum {
    NPC_SpikedGoomba_01         = 0,
    NPC_SpikedGoomba_02         = 1,
};

enum {
    MV_PlatformShadowsArray     = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_SetupPlatforms;
extern NpcGroupList DefaultNPCs;
