#pragma once

/// @file tik_10.h
/// @brief Toad Town Tunnels - Block Puzzle Room (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_10_shape.h"
#include "mapfs/tik_10_hit.h"

enum {
    MV_SuperBlock       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupDrips;
