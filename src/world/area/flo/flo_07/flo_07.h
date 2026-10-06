#pragma once

/// @file flo_07.h
/// @brief Flower Fields - (SW) Posie and Crystal Tree

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_07_shape.h"
#include "mapfs/flo_07_hit.h"

enum {
    NPC_Posie   = 0,
};

enum {
    MV_GroundShakingScript  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushFlowerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_Scene_SunReturns;
extern EvtScript EVS_TryKickingPlayerOut;
extern EvtScript EVS_SetupFoliage;

extern NpcGroupList DefaultNPCs;
