#pragma once

/// @file kzn_17.h
/// @brief Mt Lavalava - Spike Roller Trap

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    NPC_Kolorado                = 0,
    NPC_Piranha                 = 1,
    NPC_Piranha_Hitbox          = 2,
    NPC_SpikeTop                = 3,
};

enum {
    MV_TrompPosX                = MapVar(0),
    MV_ScreenShakeTID           = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupSpinyTromp;
extern EvtScript EVS_Kolorado_TrompPanic;
extern EvtScript EVS_Kolorado_TrompImpact;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
