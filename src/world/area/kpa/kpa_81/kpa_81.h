#pragma once

/// @file kpa_81.h
/// @brief Bowser's Castle - Guard Door 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "mapfs/w_kpa_80_shape.h"
#include "mapfs/w_kpa_80_hit.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"

enum {
    NPC_Door    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
