#pragma once

/// @file kzn_06.h
/// @brief Mt Lavalava - Flowing Lava Puzzle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "mapfs/kzn_06_shape.h"
#include "mapfs/kzn_06_hit.h"

enum {
    MV_GlowIntensity        = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupLavaPuzzle;
