#pragma once

/// @file pra_36.h
/// @brief Crystal Palace - Palace Key Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/w_pra_10_shape.h"
#include "mapfs/w_pra_10_hit.h"
#include "map.xml.h"

#include "sprite/npc/Duplighost.h"

enum {
    NPC_Duplighost  = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
