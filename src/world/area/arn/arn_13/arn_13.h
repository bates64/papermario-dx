#pragma once

/// @file arn_13.h
/// @brief Gusty Gulch - Tunnel 3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

enum {
    NPC_TubbasHeart     = 0,
    NPC_HyperGoomba     = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
