#pragma once

/// @file mim_05.h
/// @brief Forever Forest - Mushrooms (HP Plus)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "mapfs/mim_05_shape.h"
#include "mapfs/mim_05_hit.h"

#include "sprite/npc/SmallPiranha.h"

enum {
    NPC_PiranhaPlant_01         = 0,
    NPC_PiranhaPlant_01_Hitbox  = 1,
    NPC_PiranhaPlant_02         = 2,
    NPC_PiranhaPlant_02_Hitbox  = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_SetupExitHint;
extern NpcGroupList DefaultNPCs;
