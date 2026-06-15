#pragma once

/// @file omo_06.h
/// @brief Shy Guy's Toybox - PNK Station

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_06_shape.h"
#include "mapfs/omo_06_hit.h"

#include "sprite/npc/TrainToad.h"

enum {
    NPC_Conductor           = 0,
    NPC_TrainToad           = 1,
};

enum {
    MV_TrainRideState       = MapVar(0),
    MV_TrainPath            = MapVar(1),
    MV_TrainSpeedMode       = MapVar(2),
    MV_ArrowTexUOffset      = MapVar(9),
    MV_TrainPosX            = MapVar(11),
    MV_TrainPosZ            = MapVar(12),
    MV_TrainYaw             = MapVar(13),
};

enum {
    MF_TrainRideActive      = MapFlag(0),
    MF_EitherSwitchPressed  = MapFlag(1),
};

#define NAMESPACE omo_06

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupGizmos);
extern EvtScript N(EVS_SetupTrain);
extern EvtScript N(EVS_Conductor_ChooseRoute);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
