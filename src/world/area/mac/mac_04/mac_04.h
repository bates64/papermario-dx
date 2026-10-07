#pragma once

/// @file mac_04.h
/// @brief Toad Town - Residental District

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mac.h"
#include "map.xml.h"

#include "sprite/npc/ShyGuy.h"
#include "sprite/npc/WorldGoombario.h"

enum {
    NPC_HarryT                  = 0,
    NPC_NewResident1            = 1,
    NPC_NewResident2            = 2,
    NPC_Toad_01                 = 3,
    NPC_Toad_02                 = 4,
    NPC_ToadKid_01              = 5,
    NPC_ToadKid_02              = 6,
    NPC_ToadKid_03              = 7,
    NPC_Toadette_03             = 8,
    NPC_Toad_03                 = 9,
    NPC_GossipTrio1             = 10,
    NPC_GossipTrio2             = 11,
    NPC_GossipTrio3             = 12,
    NPC_ChetRippo               = 13,
    NPC_ShyGuy_01               = 14,
    NPC_ShyGuy_02               = 15,
    NPC_Twink                   = 16,
    NPC_Muskular                = 17,
    NPC_Goomama                 = 18,
    NPC_Goombaria               = 19,
    NPC_ChuckQuizmo             = 20,
    NPC_WishingToadKid          = 21,
};

enum {
    MV_StoreroomLockEntityID        = MapVar(0),
    MV_PlayerShrinkScale            = MapVar(10),
    MV_DrawShinkingPlayerWorker     = MapVar(11),
};

enum {
    MF_MusicMixTrigger              = MapFlag(10),
};

#include "world/common/npc/Toad/idle.h"
#include "world/common/npc/Toad/wander.h"
#include "world/common/npc/ToadKid/idle.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupMusicTriggers;
extern EvtScript EVS_SetupShop;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_MakeStoreroom;
extern EvtScript EVS_MakeHiddenRoom;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern EvtScript EVS_OnEnterShop;
extern EvtScript EVS_HiddenRoom_WaitForOuttaSight;
extern EvtScript EVS_ExitToybox;
extern EvtScript EVS_Toybox_SetupTrainPrompt;
extern EvtScript EVS_ForceStoreroomUnlock;
extern EvtScript EVS_Scene_WishingToadKid;

extern NpcGroupList DefaultNPCs;
extern NpcGroupList Chapter4NPCs;
extern NpcGroupList PostChapter4NPCs;
extern NpcGroupList Chapter7NPCs;
extern NpcGroupList WishSceneNPCs;
