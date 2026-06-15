#pragma once

/// @file omo_08.h
/// @brief Shy Guy's Toybox - GRN Station

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_08_shape.h"
#include "mapfs/omo_08_hit.h"

#include "sprite/npc/TrainToad.h"
#include "sprite/npc/ShyGuy.h"

enum {
    NPC_Conductor           = 0,
    NPC_TrainToad           = 1,
    NPC_ShyGuy_01           = 2,
    NPC_ShyGuy_02           = 3,
    NPC_ShyGuy_03           = 4,
    NPC_ShyGuy_04           = 5,
};

enum {
    MV_TrainRideState       = MapVar(0),
    MV_TrainPath            = MapVar(1),
    MV_TrainSpeedMode       = MapVar(2),
    MV_ArrowTexUOffset      = MapVar(9),
    MV_TrainPosX            = MapVar(11),
    MV_TrainPosZ            = MapVar(12),
    MV_TrainYaw             = MapVar(13),
    MV_BoxHitCount          = MapVar(14),
    MV_BoxHitSequence       = MapVar(15),
};

enum {
    MF_TrainRideActive      = MapFlag(0),
    MF_EitherSwitchPressed  = MapFlag(1),
};

#define NAMESPACE omo_08

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupTrain);
extern EvtScript N(EVS_Conductor_ChooseRoute);
extern EvtScript N(EVS_SetupBoxes);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
