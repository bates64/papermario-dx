#pragma once

/// @file isk_10.h
/// @brief Dry Dry Ruins - Vertical Shaft

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

enum {
    MV_SuperBlock       = MapVar(0),
    MV_LastFloorLevel   = MapVar(9),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupBombableWall;
extern EvtScript EVS_MakeEntities;
