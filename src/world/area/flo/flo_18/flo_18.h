#pragma once

/// @file flo_18.h
/// @brief Flower Fields - (NE) Puff Puff Machine

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_18_shape.h"
#include "mapfs/flo_18_hit.h"

#include "sprite/npc/WorldLakilester.h"

enum {
    NPC_Lakitu_01           = 0,
    NPC_Lakitu_02           = 1,
    NPC_Lakitu_03           = 2,
    NPC_Magikoopa           = 3,
    NPC_FlyingMagikoopa     = 4,
};

enum {
    MF_HitGuardedMachine    = MapFlag(1),
    MF_MachineShaking       = MapFlag(2),
    MF_MachineBeingDamaged  = MapFlag(3),
};

enum {
    MV_ReactingNpc          = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupMachine;
extern EvtScript EVS_SetupMachineDamageReactions;
extern EvtScript EVS_Scene_LakilesterLikesBeingGood;
extern NpcGroupList DefaultNPCs;
