#pragma once

/// @file mim_01.h
/// @brief Forever Forest - Flower Sounds

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "map.xml.h"

#include "sprite/npc/SmallPiranha.h"

enum {
    NPC_PiranhaPlant            = 1,
    NPC_PiranhaPlant_Hitbox     = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupExitHint;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_BindExitTriggers;
extern NpcGroupList DefaultNPCs;
