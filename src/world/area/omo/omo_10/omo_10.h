/// @file omo_10.h
/// @brief Shy Guy's Toybox - RED Station

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "mapfs/omo_10_shape.h"
#include "mapfs/omo_10_hit.h"

#include "sprite/npc/TrainToad.h"

enum {
    NPC_Conductor           = 0,
    NPC_TrainToad    = 1,
};

enum {
    MV_TrainRideState          = MapVar(0),
    MV_TrainPath          = MapVar(1),
    MV_TrainUnk_02          = MapVar(2),
    MV_ArrowTexUOffset      = MapVar(9),
    MV_TrainPosX             = MapVar(11),
    MV_TrainPosZ          = MapVar(12),
    MV_TrainYaw          = MapVar(13),
};

enum {
    MF_TrainRideActive          = MapFlag(0),
    MF_EitherSwitchPressed  = MapFlag(1),
    MF_Unk_0A               = MapFlag(10),
};

#define NAMESPACE omo_10

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupGizmos);
extern EvtScript N(EVS_SetupTrain);
extern EvtScript N(D_802444A0_DDBE50);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
