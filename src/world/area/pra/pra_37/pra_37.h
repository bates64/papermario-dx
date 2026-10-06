#pragma once

/// @file pra_37.h
/// @brief Crystal Palace - P-Up, D-Down Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/pra_10_shape.h"
#include "mapfs/pra_10_hit.h"

enum {
    NPC_FrostClubba         = 0,
    NPC_FrostClubba_Hitbox  = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
