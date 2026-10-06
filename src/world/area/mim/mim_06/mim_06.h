#pragma once

/// @file mim_06.h
/// @brief Forever Forest - Bee Hive (Path Splits)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "mapfs/mim_06_shape.h"
#include "mapfs/mim_06_hit.h"

#include "sprite/npc/SmallPiranha.h"
#include "sprite/npc/Fuzzy.h"

enum {
    NPC_PiranhaPlant_01         = 0,
    NPC_PiranhaPlant_01_Hitbox  = 1,
    NPC_PiranhaPlant_02         = 2,
    NPC_PiranhaPlant_02_Hitbox  = 3,
    NPC_Fuzzy                   = 4,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFlowerHints;
extern NpcGroupList DefaultNPCs;

