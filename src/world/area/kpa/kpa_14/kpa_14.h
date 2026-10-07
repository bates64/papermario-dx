#pragma once

/// @file kpa_14.h
/// @brief Bowser's Castle - Lava Channel 3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    MV_EntityID_Padlock          = MapVar(0),
    MV_LastFloorBeforeLavaFall  = MapVar(10),
    MV_TakingLavaFallDamage     = MapVar(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupPlatforms;
extern EvtScript EVS_ExitDoor_kpa_01_0;
extern EvtScript EVS_MakeEntities;
