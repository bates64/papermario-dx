#pragma once

/// @file omo_04.h
/// @brief Shy Guy's Toybox - BLU Block City

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../omo.h"
#include "map.xml.h"

#include "sprite/npc/WorldKammy.h"

enum {
    NPC_Goomba      = 0,
    NPC_Clubba      = 1,
    NPC_Kammy       = 2,
    NPC_ShyGuy      = 3,
    NPC_SkyGuy      = 4,
};

enum {
    MV_AmbushID                 = MapVar(10), // npcID or itemID depending on GB_OMO_PeachChoice1
    MV_FlightSoundsScriptID     = MapVar(11),
};

enum {
    MF_KammyFlying      = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_NpcIdle_Kammy;
extern EvtScript EVS_NpcAux_Kammy;
extern EvtScript EVS_SetupGizmos;
extern EvtScript EVS_Scene_KammySetAmbush;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList KammySceneNPCs;
extern NpcGroupList GoombaAmbushNPCs;
extern NpcGroupList ClubbaAmbushNPCs;
extern NpcGroupList DefaultNPCs;
