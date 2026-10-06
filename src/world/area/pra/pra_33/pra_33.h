#pragma once

/// @file pra_33.h
/// @brief Crystal Palace - Turnstyle Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/pra_33_shape.h"
#include "mapfs/pra_33_hit.h"

enum {
    MV_WallFlipped  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
