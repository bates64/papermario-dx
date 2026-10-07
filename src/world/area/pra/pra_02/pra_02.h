#pragma once

/// @file pra_02.h
/// @brief Crystal Palace - Entry Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    MV_WallPosOffset    = MapVar(0),
    MV_NearRedPadlock   = MapVar(1),
    MV_FarRedPadlock    = MapVar(2),
    MV_NearBluePadlock  = MapVar(3),
    MV_FarBluePadlock   = MapVar(4),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ManagePoundableSwitch;
extern EvtScript EVS_UpdateShiftingWallPos;
extern EvtScript EVS_ExitDoors_pra_16_0;
extern EvtScript EVS_ExitDoors_pra_16_3;
extern EvtScript EVS_ExitDoors_pra_13_0;
extern EvtScript EVS_ExitDoors_pra_13_3;
extern EvtScript EVS_MakeEntities;
