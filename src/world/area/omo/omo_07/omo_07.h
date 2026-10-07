#pragma once

/// @file omo_07.h
/// @brief Shy Guy's Toybox - PNK Playhouse

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "map.xml.h"

#include "sprite/npc/ShyGuy.h"
#include "sprite/npc/Fuzzy.h"
#include "sprite/npc/HammerBros.h"
#include "sprite/npc/SkyGuy.h"
#include "sprite/npc/WorldKammy.h"

enum {
    NPC_ShyGuy_01       = 1,
    NPC_ShyGuy_02       = 2,
    NPC_ShyGuy_03       = 3,
    NPC_ShyGuy_04       = 4, // never appears
    NPC_Fuzzy           = 5,
    NPC_HammerBros      = 6,
    NPC_Kammy           = 7,
    NPC_SkyGuy_01       = 8,
    NPC_SkyGuy_02       = 9,
};

enum {
    MV_SecretDoorAngle  = MapVar(0),
    MV_AmbushID         = MapVar(10), // npcID or itemID depending on GB_OMO_PeachChoice1
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupGizmos;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupShyGuyPool;
extern EvtScript EVS_Scene_KammySetAmbush;
extern EvtScript EVS_NpcIdle_Kammy;
extern NpcGroupList KammySceneNPCs;
extern NpcGroupList FuzzyAmbushNPCs;
extern NpcGroupList HammerBrosAmbushNPCs;
extern NpcGroupList DefaultNPCs;
