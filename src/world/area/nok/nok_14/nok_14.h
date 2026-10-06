#pragma once

/// @file nok_14.h
/// @brief Koopa Region - Path to Fortress 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "mapfs/nok_14_shape.h"
#include "mapfs/nok_14_hit.h"

enum {
    NPC_KoopaTroopa_01          = 0,
    NPC_SpikedGoomba            = 2,
    NPC_ParaTroopa              = 3,
    NPC_KoopaTroopa_02          = 4,
};

enum {
    MV_Item_ThunderBolt         = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupBridge;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
