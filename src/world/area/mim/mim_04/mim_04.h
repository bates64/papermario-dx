#pragma once

/// @file mim_04.h
/// @brief Forever Forest - Tree Face (Bub-ulb)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "mapfs/mim_04_shape.h"
#include "mapfs/mim_04_hit.h"

#include "sprite/npc/Bubulb.h"
#include "sprite/npc/Fuzzy.h"

enum {
    NPC_Bubulb                  = 0,
    NPC_Fuzzy                   = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_SetupExitHint;
extern NpcGroupList DefaultNPCs;
