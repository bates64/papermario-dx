#pragma once

/// @file kpa_52.h
/// @brief Bowser's Castle - Split Level Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/HammerBros.h"

enum {
    NPC_HammerBros_01           = 10,
    NPC_HammerBros_01_Hammer1   = 11,
    NPC_HammerBros_01_Hammer2   = 12,
    NPC_HammerBros_01_Hammer3   = 13,
    NPC_HammerBros_01_Hammer4   = 14,
    NPC_HammerBros_01_Hammer5   = 15,
    NPC_HammerBros_01_Hammer6   = 16,
    NPC_HammerBros_02           = 20,
    NPC_HammerBros_02_Hammer1   = 21,
    NPC_HammerBros_02_Hammer2   = 22,
    NPC_HammerBros_02_Hammer3   = 23,
    NPC_HammerBros_02_Hammer4   = 24,
    NPC_HammerBros_02_Hammer5   = 25,
    NPC_HammerBros_02_Hammer6   = 26,
};

enum {
    MV_EntityID_Padlock  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_kpa_40_0;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
