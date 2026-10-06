#pragma once

/// @file dgb_07.h
/// @brief Tubba's Castle - Study (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "mapfs/dgb_07_shape.h"
#include "mapfs/dgb_07_hit.h"

enum {
    NPC_Clubba_01           = 0,
    NPC_Clubba_01_Hitbox    = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
