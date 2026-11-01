#pragma once

/// @file kpa_53.h
/// @brief Bowser's Castle - Fake Peach Hallway

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "mapfs/w_kpa_50_shape.h"
#include "mapfs/w_kpa_50_hit.h"
#include "map.xml.h"

#include "sprite/npc/Duplighost.h"

enum {
    NPC_Follower        = 0,
    NPC_Guardian        = 1,
    NPC_Duplighost      = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_kpa_83_0;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
