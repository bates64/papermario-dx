#pragma once

/// @file flo_11.h
/// @brief Flower Fields - (West) Maze

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_11_shape.h"
#include "mapfs/flo_11_hit.h"

enum {
    NPC_Lakitu_01       = 0,
    NPC_Lakitu_02       = 1,
};

enum {
    MV_LakituAmbushState    = MapVar(0),
    MV_LakituSearchSync     = MapVar(10),
    MV_FlyingSoundsScript   = MapVar(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_Scene_LakituAmbush;
extern NpcGroupList DefaultNPCs;
