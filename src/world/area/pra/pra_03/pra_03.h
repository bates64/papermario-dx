#pragma once

/// @file pra_03.h
/// @brief Crystal Palace - Save Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/pra_03_shape.h"
#include "mapfs/pra_03_hit.h"

enum {
    MV_PlayerFloor  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
