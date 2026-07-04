#pragma once

/// @file trd_04.h
/// @brief Koopa Bros Fortress - Right Starway

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../trd.h"
#include "mapfs/trd_04_shape.h"
#include "mapfs/trd_04_hit.h"

#include "sprite/npc/KoopaTroopa.h"
#include "sprite/npc/ParaTroopa.h"

enum {
    NPC_KoopaTroopa             = 0,
    NPC_ParaTroopa              = 1,
};

enum {
    MV_EntityID_PadlockUpper    = MapVar(0),
    MV_EntityID_PadlockLower    = MapVar(1),
    MV_EntityID_Switch          = MapVar(2),
};

#define NAMESPACE trd_04
