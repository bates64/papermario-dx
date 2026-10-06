#pragma once

/// @file dgb_01.h
/// @brief Tubba's Castle - Great Hall

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "mapfs/dgb_01_shape.h"
#include "mapfs/dgb_01_hit.h"

#include "sprite/npc/WorldTubba.h"
#include "sprite/npc/Sentinel.h"
#include "animation_script.h"

enum {
    NPC_Sentinel_01     = 0,
    NPC_Sentinel_02     = 1,
    NPC_Sentinel_03     = 2,
    NPC_Sentinel_04     = 3,
    NPC_Tubba           = 4,
};

enum {
    MV_EntityID_Padlock  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_dgb_08_0;
extern EvtScript EVS_ExitDoors_dgb_08_1;
extern EvtScript EVS_SetupBridges;
extern EvtScript EVS_UnlockPrompt_Door;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
extern NpcGroupList FirstFloorEscapeNPCs;
extern NpcGroupList SecondFloorEscapeNPCs;
extern NpcGroupList ThirdFloorEscapeNPCs;

extern StaticAnimatorNode* SmashBridgesSkeleton[];
extern AnimScript AS_SmashBridges;

API_CALLABLE(InitAnimatedModels);
API_CALLABLE(SetAnimatedModelRenderMode);
API_CALLABLE(DeleteAnimatedModel);
