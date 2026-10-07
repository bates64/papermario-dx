#pragma once

/// @file kpa_133.h
/// @brief Bowser's Castle - Left Water Puzzle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    NPC_Dummy   = 0,
};

enum {
    MV_SpringEntityID       = MapVar(0),
    MV_RevealHiddenSpring   = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetWaterLevel;
extern EvtScript EVS_OnHitSwitch;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
