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

#define NAMESPACE dgb_01

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_ExitDoors_dgb_08_0);
extern EvtScript N(EVS_ExitDoors_dgb_08_1);
extern EvtScript N(EVS_SetupBridges);
extern EvtScript N(EVS_UnlockPrompt_Door);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
extern NpcGroupList N(FirstFloorEscapeNPCs);
extern NpcGroupList N(SecondFloorEscapeNPCs);
extern NpcGroupList N(ThirdFloorEscapeNPCs);

extern StaticAnimatorNode* N(SmashBridgesSkeleton)[];
extern AnimScript N(AS_SmashBridges);

API_CALLABLE(InitAnimatedModels);
API_CALLABLE(SetAnimatedModelRenderMode);
API_CALLABLE(DeleteAnimatedModel);
