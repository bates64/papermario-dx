#pragma once

/// @file iwa_11.h
/// @brief Mt Rugged - Train Ride Scene

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../iwa.h"
#include "mapfs/iwa_11_shape.h"
#include "mapfs/iwa_11_hit.h"

enum {
    NPC_TrainToad        = 0,
};

enum {
    MV_TrainMoveDist    = MapVar(0),
    MV_TrainMoveSpeed   = MapVar(1),
};

enum {
    MF_TrainArriveDoorOpen          = MapFlag(0),
    MF_TrainArrivePlayerDisembark   = MapFlag(1),
    MF_TrainDepartDoorOpen          = MapFlag(2),
    MF_TrainDepartPlayerBoard       = MapFlag(3),
    MF_TrainScrolling               = MapFlag(4),
    MF_TrainReverseDir              = MapFlag(5),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_InitializeTrainScene;
extern EvtScript EVS_TravelToMtRugged;
extern EvtScript EVS_TravelToToadTown;
extern EvtScript EVS_UpdateSceneryPos;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
