#pragma once

/// @file arn_08.h
/// @brief Gusty Gulch - Windmill Interior

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../arn.h"
#include "map.xml.h"

#include "sprite/npc/TubbasHeart.h"
#include "sprite/npc/Yakkey.h"

enum {
    NPC_TubbasHeart             = 0,
    NPC_Yakkey                  = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_AnimateGears;
extern EvtScript EVS_SetupHole;
extern EvtScript EVS_PlayDemoScene;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
