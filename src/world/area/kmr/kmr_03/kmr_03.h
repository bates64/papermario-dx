#pragma once

/// @file kmr_03.h
/// @brief Goomba Region - Bottom of the Cliff

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/Goompa.h"

enum {
    NPC_Goompa          = 0,
};

enum {
    MV_GoompaHitCount   = MapVar(0),
};

enum {
    MF_Tree1_Mushroom   = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_Scene_FallingDown;
extern NpcGroupList DefaultNPCs;
