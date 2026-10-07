#pragma once

/// @file hos_20.h
/// @brief Shooting Star Summit - Riding Star Ship Scene

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "map.xml.h"

enum {
    MV_Starship_PosX    = MapVar(10),
    MV_Starship_Yaw     = MapVar(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_Starship_Flight1;
extern EvtScript EVS_Starship_Flight2;
extern EvtScript EVS_Starship_Return;
