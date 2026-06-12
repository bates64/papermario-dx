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

#define NAMESPACE omo_06

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupGizmos);
extern EvtScript N(EVS_80244F40);
extern EvtScript N(D_80244B10_DBC420);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
