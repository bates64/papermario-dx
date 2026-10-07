#pragma once

/// @file kmr_05.h
/// @brief Goomba Region - Behind the Village

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/Goompa.h"
#include "sprite/npc/Goomba.h"
#include "sprite/npc/SpikedGoomba.h"
#include "sprite/npc/Paragoomba.h"

enum {
    NPC_Goomba_01               = 0,
    NPC_Goomba_02               = 2,
    NPC_SpikedGoomba            = 3,
    NPC_Paragoomba              = 4,
};

enum {
    MF_Tree1CoinDropped     = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_GoompaRemark;
extern NpcGroupList NpcsBefore;
extern NpcGroupList NpcsAfter;
