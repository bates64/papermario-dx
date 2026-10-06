#pragma once

/// @file pra_18.h
/// @brief Crystal Palace - Bridge Mirror Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/pra_18_shape.h"
#include "mapfs/pra_18_hit.h"

enum {
    NPC_Clubba_01       = 0,
    NPC_Clubba_02       = 1,
    NPC_Clubba_03       = 2,
    NPC_Clubba_01_Aux   = 3,
    NPC_Clubba_02_Aux   = 4,
    NPC_Clubba_03_Aux   = 5,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_pra_33_1;
extern NpcGroupList DefaultNPCs;
