#pragma once

/// @file kzn_03.h
/// @brief Mt Lavalava - Central Cavern

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    NPC_Kolorado                = 0,
    NPC_ZiplineDummy1           = 1,
    NPC_ZiplineDummy2           = 2,
    NPC_SpikeTop_01             = 3,
    NPC_SpikeTop_02             = 4,
    NPC_SpikeTop_03             = 5,
    NPC_Piranha                 = 6,
    NPC_Piranha_Hitbox          = 7,
};

enum {
    MV_PlayerCliffState         = MapVar(9)
};

enum {
    MF_RidingZipline1           = MapFlag(10),
    MF_RidingZipline2           = MapFlag(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupZiplines;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SyncZiplineDummyNPC1;
extern EvtScript EVS_SyncZiplineDummyNPC2;
extern NpcGroupList DefaultNPCs;
