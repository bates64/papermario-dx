#pragma once

/// @file kmr_11.h
/// @brief Goomba Region - Goomba King's Castle

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/GoombaKing.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/GoombaBros.h"
#include "sprite/npc/WorldKammy.h"

#include "animation_script.h"

enum {
    NPC_BlueGoombaBro   = 0,
    NPC_RedGoombaBro    = 1,
    NPC_GoombaKing      = 2,
    NPC_Kammy           = 4,
};

enum {
    MV_SwitchEntityID       = MapVar(0),
};

enum {
    MF_SpawnFlag_StarPiece  = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_Interact_SwitchBush;
extern EvtScript EVS_Scene_MeetGoombaKing;
extern EvtScript EVS_Scene_SelfDestruct;
extern EvtScript EVS_PlayFortressAnimation;
extern EvtScript EVS_PlayBridgeAnimation;
extern EvtScript EVS_Scene_KammyWatching;
extern EvtScript EVS_BadExit_kmr_24_0;

extern NpcGroupList DefaultNPCs;

extern StaticAnimatorNode* AnimSkeleton_Fortress[];
extern StaticAnimatorNode* AnimSkeleton_Bridge[];
extern AnimScript AnimScript_Fortress;
extern AnimScript AnimScript_Bridge;

API_CALLABLE(SetCameraVFov);
API_CALLABLE(SetupFog);

API_CALLABLE(InitAnimatedModels);
API_CALLABLE(SetAnimatedModelRenderMode);
API_CALLABLE(DeleteAnimatedModel);
