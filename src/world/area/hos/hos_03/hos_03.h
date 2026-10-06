#pragma once

/// @file hos_03.h
/// @brief Shooting Star Summit - Star Haven

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "mapfs/hos_03_shape.h"
#include "mapfs/hos_03_hit.h"

enum {
    NPC_StarMan_01              = 0,
    NPC_StarMan_02              = 1,
    NPC_StarMan_03              = 2,
    NPC_StarMan_04              = 3,
    NPC_StarMan_05              = 4,
    NPC_StarMan_ToadHouse       = 5,
    NPC_StarMan_ShopOwner       = 6,
    NPC_ChuckQuizmo             = 7,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_SetupAurora;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupShop;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
