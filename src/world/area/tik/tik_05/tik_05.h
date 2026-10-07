#pragma once

/// @file tik_05.h
/// @brief Toad Town Tunnels - Spring Room (B2)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "map.xml.h"

enum {
    NPC_SpikedGoomba_01         = 0,
    NPC_SpikedGoomba_02         = 1,
};

enum {
    MV_EntityID_Spring          = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrips;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
