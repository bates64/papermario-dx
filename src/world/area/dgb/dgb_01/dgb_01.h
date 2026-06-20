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

// Temporary visualization aid for identifying animated bridge meshes.
#define DEBUG_DGB_01_MESH_COLORS

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

extern Gfx N(Gfx_SetupTex_Wood)[];
extern Gfx N(Gfx_SetupTex_FloorTile)[];
extern Gfx N(Gfx_SetupTex_WoodPanelTrim)[];
extern Gfx N(Gfx_SetupTex_FloorSmooth)[];
extern Gfx N(Gfx_SetupTex_RailingPost)[];
extern Gfx N(Gfx_SetupTex_RailingPostDestroyed)[];
extern Gfx N(Gfx_SetupTex_WoodPanelCeiling)[];
extern Gfx N(Gfx_SetupTex_RailingPostDamaged)[];
extern Gfx N(Gfx_DrawMesh_StaticWoodPanelCeiling)[];

extern Mtx N(UpperBridgeLeftMtx);
extern Mtx N(UpperBridgeRightCollapseMtx);
extern Mtx N(UpperRailingDebris11Mtx);
extern Mtx N(UpperRailingDebris10Mtx);
extern Mtx N(UpperRailingDebris9Mtx);
extern Mtx N(UpperRailingDebris8Mtx);
extern Mtx N(UpperRailingDebris7Mtx);
extern Mtx N(UpperRailingDebris6Mtx);
extern Mtx N(UpperRailingDebris5Mtx);
extern Mtx N(UpperRailingDebris4Mtx);
extern Mtx N(UpperRailingDebris3Mtx);
extern Mtx N(UpperRailingDebris2Mtx);
extern Mtx N(UpperRailingDebris1Mtx);
extern Mtx N(SmashBridgesNode077Mtx);
extern Mtx N(SmashBridgesNode082Mtx);
extern Mtx N(SmashBridgesNode079Mtx);
extern Mtx N(SmashBridgesNode081Mtx);
extern Mtx N(SmashBridgesNode076Mtx);
extern Mtx N(SmashBridgesNode075Mtx);
extern Mtx N(SmashBridgesNode074Mtx);
extern Mtx N(SmashBridgesNode080Mtx);
extern Mtx N(SmashBridgesNode073Mtx);
extern Mtx N(UpperBridgeRearRailingMtx);
extern Mtx N(SmashBridgesIdentityMtx);
extern Mtx N(SmashBridgesNode020Mtx);
extern Mtx N(SmashBridgesNode019Mtx);
extern Mtx N(LowerBridgeLeftCollapseMtx);
extern Mtx N(LowerBridgeCenterCollapseMtx);
extern Mtx N(SmashBridgesNode029Mtx);
extern Mtx N(SmashBridgesNode043Mtx);
extern Mtx N(SmashBridgesNode071Mtx);
extern Mtx N(SmashBridgesNode070Mtx);
extern Mtx N(SmashBridgesNode069Mtx);
