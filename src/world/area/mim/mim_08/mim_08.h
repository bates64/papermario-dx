#pragma once

/// @file mim_08.h
/// @brief Forever Forest - Laughing Rock

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "mapfs/mim_08_shape.h"
#include "mapfs/mim_08_hit.h"

#include "sprite/npc/Bzzap.h"
#include "sprite/npc/SmallPiranha.h"

enum {
    NPC_Bzzap                   = 0,
    NPC_PiranhaPlant_01         = 1,
    NPC_PiranhaPlant_01_Hitbox  = 2,
    NPC_PiranhaPlant_02         = 3,
    NPC_PiranhaPlant_02_Hitbox  = 4,
};

enum {
    MV_HitHiveTree      = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
