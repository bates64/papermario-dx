#pragma once

/// @file arn_04.h
/// @brief Gusty Gulch - Wasteland Ascent 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

#include "sprite/npc/Paragoomba.h"
#include "sprite/npc/Goomba.h"
#include "sprite/npc/Cleft.h"

enum {
    NPC_HyperParagoomba     = 0,
    NPC_HyperGoomba         = 1,
    NPC_HyperCleft_01       = 2,
    NPC_HyperCleft_02       = 3,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
