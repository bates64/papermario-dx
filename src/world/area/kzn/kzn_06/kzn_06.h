#pragma once

/// @file kzn_06.h
/// @brief Mt Lavalava - Flowing Lava Puzzle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    MV_GlowIntensity        = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupLavaPuzzle;
