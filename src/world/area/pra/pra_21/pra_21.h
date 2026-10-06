#pragma once

/// @file pra_21.h
/// @brief Crystal Palace - Huge Statue Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "mapfs/pra_21_shape.h"
#include "mapfs/pra_21_hit.h"

enum {
    MV_PlayerFloor  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
