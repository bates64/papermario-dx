#pragma once

/// @file jan_03.h
/// @brief Jade Jungle - Village Buildings

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "mapfs/jan_03_shape.h"
#include "mapfs/jan_03_hit.h"

enum {
    NPC_Toad                = 0,
    NPC_Yoshi_01            = 1,
    NPC_VillageLeader       = 2,
    NPC_Yoshi_02            = 3,
    NPC_Yoshi_03            = 4,
    NPC_YoshiKid_01         = 5,
    NPC_YoshiKid_02         = 6,
    NPC_YoshiKid_03         = 7,
    NPC_YoshiKid_04         = 8,
    NPC_YoshiKid_05         = 9,
    NPC_Raven_01            = 10,
    NPC_Raven_02            = 11,
    NPC_Raven_03            = 12,
    NPC_Raven_04            = 13,
    NPC_Raven_05            = 14,
    NPC_Kolorado            = 15,
    NPC_Sushie              = 16,
    NPC_ChuckQuizmo         = 17,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupShop;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList CrisisNPCs;
extern NpcGroupList ChapterNPCs;
extern NpcGroupList AfterNPCs;
extern NpcGroupList DefaultNPCs;
