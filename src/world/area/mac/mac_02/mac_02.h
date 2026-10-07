#pragma once

/// @file mac_02.h
/// @brief Toad Town - Southern District

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mac.h"
#include "map.xml.h"

#include "sprite/npc/TayceT.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/FiceT.h"
#include "sprite/npc/ShyGuy.h"

enum {
    NPC_TayceT                  = 0,
    NPC_FiceT                   = 1,
    NPC_Bubulb                  = 2,
    NPC_Toad_01                 = 3,
    NPC_CookingApprentice       = 4,
    NPC_Toad_02                 = 5,
    NPC_ToadKid                 = 6,
    NPC_Toad_03                 = 7,
    NPC_Toad_04                 = 8,
    NPC_Bootler                 = 9,
    NPC_ShyGuy                  = 11,
    NPC_ChuckQuizmo             = 12,
};

enum {
    MV_BlueHouseLockEntityID    = MapVar(0),
};

enum {
    MF_MusicMixTrigger1         = MapFlag(10),
    MF_MusicMixTrigger2         = MapFlag(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupMusicTriggers;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList NpcGroup1;
extern NpcGroupList NpcGroup3;
extern NpcGroupList NpcGroup4;
