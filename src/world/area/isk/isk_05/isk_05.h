#pragma once

/// @file isk_05.h
/// @brief Dry Dry Ruins - Pyramid Stone Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "mapfs/isk_05_shape.h"
#include "mapfs/isk_05_hit.h"

#include "sprite/npc/StoneChomp.h"

enum {
    NPC_StoneChomp              = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
