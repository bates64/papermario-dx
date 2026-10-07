#pragma once

/// @file kpa_95.h
/// @brief Bowser's Castle - West Upper Jail

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

#include "sprite/npc/Toad.h"
#include "sprite/npc/ToadGuard.h"
#include "sprite/npc/Penguin.h"
#include "sprite/npc/WorldKoopatrol.h"

enum {
    NPC_Toad_01                 = 0,
    NPC_Toad_02                 = 1,
    NPC_ToadGuard               = 2,
    NPC_Penguin                 = 3,
    NPC_Koopatrol               = 4,
};

enum {
    MV_EntityID_Padlock  = MapVar(0),
    MV_LastPlayerPosX   = MapVar(1),
    MV_LastPlayerPosY   = MapVar(2),
    MV_LastPlayerPosZ   = MapVar(3),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_OpenCellDoor;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
