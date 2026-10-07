#pragma once

/// @file kpa_62.h
/// @brief Bowser's Castle - Front Door Exterior

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    MV_EntityID_Padlock  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_kpa_70_0;
extern EvtScript EVS_MakeEntities;
