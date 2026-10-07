#pragma once

/// @file kpa_01.h
/// @brief Bowser's Castle - Dark Cave 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    NPC_BonyBeetle_01           = 0,
    NPC_BonyBeetle_02           = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
