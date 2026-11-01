#pragma once

/// @file pra_38.h
/// @brief Crystal Palace - Blue Key Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/w_pra_10_shape.h"
#include "mapfs/w_pra_10_hit.h"
#include "map.xml.h"

enum {
    NPC_Swoopula_01     = 0,
    NPC_Swoopula_02     = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
