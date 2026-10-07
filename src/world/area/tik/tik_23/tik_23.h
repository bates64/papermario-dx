#pragma once

/// @file tik_23.h
/// @brief Toad Town Tunnels - Windy Path (B3)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "map.xml.h"

enum {
    NPC_Spiny_01                = 0,
    NPC_Spiny_02                = 1,
    NPC_Spiny_03                = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
