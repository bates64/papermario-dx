#pragma once

/// @file tik_01.h
/// @brief Toad Town Tunnels - Warp Zone 1 (B1)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "mapfs/tik_01_shape.h"
#include "mapfs/tik_01_hit.h"

enum {
    NPC_Blooper             = 0,
};

enum {
    MV_EntityID_Switch      = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayBlooperSong;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SpawnSwitch;
extern EvtScript EVS_SetupDrips;
extern NpcGroupList DefaultNPCs;
