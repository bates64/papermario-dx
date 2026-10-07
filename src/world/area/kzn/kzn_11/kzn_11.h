#pragma once

/// @file kzn_11.h
/// @brief Mt Lavalava - Second Lava Lake

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    NPC_FireBar_1A              = 0,
    NPC_FireBar_1B              = 1,
    NPC_FireBar_1C              = 2,
    NPC_FireBar_1D              = 3,
    NPC_FireBar_2A              = 5,
    NPC_FireBar_2B              = 6,
    NPC_FireBar_2C              = 7,
    NPC_FireBar_2D              = 8,
    NPC_FireBar_3A              = 10,
    NPC_FireBar_3B              = 11,
    NPC_FireBar_3C              = 12,
    NPC_FireBar_3D              = 13,
    NPC_Bubble_01               = 100,
    NPC_Bubble_02               = 101,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_UpdateLeftPlatform;
extern EvtScript EVS_UpdateRightPlatform;
extern NpcGroupList DefaultNPCs;
