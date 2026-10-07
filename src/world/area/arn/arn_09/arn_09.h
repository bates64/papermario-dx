#pragma once

/// @file arn_09.h
/// @brief Gusty Gulch - Windmill Tunnel Entry

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

#include "sprite/npc/TubbasHeart.h"

enum {
    NPC_TubbasHeart             = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_LandFromWell;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
