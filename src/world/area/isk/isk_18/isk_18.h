#pragma once

/// @file isk_18.h
/// @brief Dry Dry Ruins - Deep Tunnel

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

#include "sprite/npc/BuzzyBeetle.h"

enum {
    NPC_BuzzyBeetle_01          = 0,
    NPC_BuzzyBeetle_02          = 1,
    NPC_BuzzyBeetle_03          = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFlames;
extern NpcGroupList DefaultNPCs;
