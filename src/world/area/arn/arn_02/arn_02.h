#pragma once

/// @file arn_02.h
/// @brief Gusty Gulch - Wasteland Ascent 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

#include "sprite/npc/Cleft.h"
#include "sprite/npc/Goomba.h"

enum {
    NPC_HyperCleft_01       = 0,
    NPC_HyperCleft_02       = 1,
    NPC_HyperGoomba         = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
