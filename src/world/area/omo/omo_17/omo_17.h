#pragma once

/// @file omo_17.h
/// @brief Shy Guy's Toybox - PNK Tracks Hallway

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_17_shape.h"
#include "mapfs/omo_17_hit.h"

#include "sprite/npc/TrainToad.h"
#include "sprite/npc/SpyGuy.h"
#include "sprite/npc/PyroGuy.h"
#include "sprite/npc/GrooveGuy.h"

enum {
    NPC_Conductor           = 0,
    NPC_SpyGuy              = 1,
    NPC_SpyGuy_Rock1        = 2,
    NPC_SpyGuy_Rock2        = 3,
    NPC_SpyGuy_Rock3        = 4,
    NPC_PyroGuy             = 5,
    NPC_GrooveGuy           = 6,
};

enum {
    MV_TrainRideState       = MapVar(0),
    MV_TrainPath            = MapVar(1),
    MV_TrainSpeedMode       = MapVar(2),
    MV_TrainPosX            = MapVar(11),
    MV_TrainPosZ            = MapVar(12),
    MV_TrainYaw             = MapVar(13),
};

enum {
    MF_TrainRideActive      = MapFlag(0),
};

#define NAMESPACE omo_17

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupGizmos);
extern EvtScript N(EVS_EnterTrain);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
