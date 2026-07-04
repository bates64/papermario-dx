#pragma once

/// @file omo_16.h
/// @brief Shy Guy's Toybox - Riding the Train

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_16_shape.h"
#include "mapfs/omo_16_hit.h"

#include "sprite/npc/TrainToad.h"

enum {
    NPC_Conductor           = 0,
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

#define NAMESPACE omo_16

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_Scene_TrainTraveling);
extern NpcGroupList N(DefaultNPCs);
