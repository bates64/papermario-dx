#pragma once

/// @file mim_02.h
/// @brief Forever Forest - Stump Eyes

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "mapfs/mim_02_shape.h"
#include "mapfs/mim_02_hit.h"

#include "sprite/npc/Oaklie.h"
#include "sprite/npc/Fuzzy.h"

enum {
    NPC_Oaklie                  = 0,
    NPC_Fuzzy_01                = 1,
    NPC_Fuzzy_02                = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_SetupExitHint;
extern EvtScript EVS_EnableWestGate;
extern NpcGroupList DefaultNPCs;
