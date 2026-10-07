#pragma once

/// @file jan_04.h
/// @brief Jade Jungle - Sushi Tree

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

#include "sprite/npc/WorldSushie.h"
#include "sprite/npc/YoshiKid.h"

enum {
    NPC_Sushie                  = 0,
    NPC_Bubulb                  = 1,
    NPC_YoshiKid_01             = 2,
    NPC_YoshiKid_02             = 3,
    NPC_YoshiKid_03             = 4,
    NPC_YoshiKid_04             = 5,
    NPC_YoshiKid_05             = 6,
};

enum {
    MF_TreeDrop_Letter  = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushNewPartnerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_GotoMap_kmr_24_0;
extern EvtScript EVS_Scene_TreasureChest;
extern EvtScript EVS_Scene_Epilogue;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_PlayDemoScene;

extern NpcGroupList DefaultNPCs;
extern NpcGroupList EpilogueNPCs;
