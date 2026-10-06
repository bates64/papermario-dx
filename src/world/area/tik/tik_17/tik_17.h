#pragma once

/// @file tik_17.h
/// @brief Toad Town Tunnels - Frozen Room (B3)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_17_shape.h"
#include "mapfs/tik_17_hit.h"

enum {
    MV_SuperBlock   = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
