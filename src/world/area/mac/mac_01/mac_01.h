#pragma once

/// @file mac_01.h
/// @brief Toad Town - Plaza District

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mac.h"
#include "map.xml.h"

#include "sprite/npc/Merlon.h"
#include "sprite/npc/Toad.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Kolorado.h"
#include "sprite/npc/DarkToad.h"
#include "sprite/npc/KoopaBros.h"
#include "sprite/npc/Ninji.h"
#include "sprite/npc/Rowf.h"
#include "sprite/npc/Postmaster.h"
#include "sprite/npc/ShyGuy.h"
#include "sprite/npc/MinhT.h"
#include "sprite/npc/Bubulb.h"
#include "sprite/npc/Twink.h"
#include "sprite/npc/Luigi.h"
#include "sprite/npc/KoloradoWife.h"
#include "sprite/npc/KoopaKoot.h"
#include "sprite/npc/WorldBobomb.h"
#include "sprite/npc/Koopa.h"
#include "sprite/npc/Dryite.h"

enum {
    // intro NPCs
    NPC_Luigi                   = 0,
    NPC_IntroToad1              = 1,
    NPC_IntroToad2              = 2,
    NPC_IntroToad3              = 3,
    // standard NPCs
    NPC_Merlon                  = 0,
    NPC_Rowf                    = 1,
    NPC_Rhuff                   = 2,
    NPC_Postmaster              = 3,
    NPC_Parakarry               = 4,
    NPC_ChuckQuizmo             = 5,
    NPC_PostOfficeShyGuy        = 6,
    NPC_ToadHouseShyGuy         = 7,
    NPC_GardenShyGuy1           = 8,
    NPC_GardenShyGuy2           = 9,
    NPC_Toad_04                 = 10,
    NPC_Toad_05                 = 11,
    NPC_Toad_06                 = 12,
    NPC_Toad_07                 = 13,
    NPC_Toad_08                 = 14,
    NPC_Toad_09                 = 15,
    NPC_ToadHouseToad           = 16,
    NPC_Bubulb                  = 17,
    NPC_MinhT                   = 18,
    NPC_Kolorado                = 19,
    NPC_DarkToad_01             = 20,
    NPC_DarkToad_02             = 21,
    NPC_DarkToad_03             = 22,
    NPC_DarkToad_04             = 23,
    NPC_KoopaBros_01            = 24,
    NPC_KoopaBros_02            = 25,
    NPC_KoopaBros_03            = 26,
    NPC_KoopaBros_04            = 27,
    NPC_Twink                   = 28,
    NPC_Ninji                   = 29,
    NPC_KoloradoWife            = 30,
    NPC_KoopaKoot               = 31,
    NPC_Koopa                   = 32,
    NPC_Bobomb                  = 33,
    NPC_Dryite_01               = 34,
    NPC_Dryite_02               = 35,
    NPC_Chanterelle             = 36,
    NPC_Poet                    = 37,
    NPC_Composer                = 38,
};

enum {
    MV_RowfRugRippleAmount  = MapVar(0),
    MV_RowfRugRotateAngle   = MapVar(1),
    MV_RowfShopBuyFlags     = MapVar(2),
    MV_FortuneFXHandles     = MapVar(12),
    MV_BadgeShopOpenState   = MapVar(13),
    MV_BadgeShopCloseState  = MapVar(14),
};

enum {
    MF_BadgeShopOpen        = MapFlag(11),
    MF_MusicMixTrigger1     = MapFlag(10),
    MF_MusicMixTrigger2     = MF_BadgeShopOpen,
    MF_MusicMixTrigger3     = MapFlag(12),
    MF_SpawnFlag_Tree1      = MapFlag(13),
    MF_SetupMusicMixes      = MapFlag(14),
    MF_InsideToadHouse      = MapFlag(15),
    MF_KoopaBrosSceneLock   = MapFlag(20),
};

#include "world/common/npc/Luigi/idle.h"
#include "world/common/npc/Dummy/idle.h"
#include "world/common/npc/Toad/idle.h"
#include "world/common/npc/Toad/patrol.h"
#include "world/common/npc/Kolorado/idle.h"
#include "world/common/npc/KoloradoWife/idle.h"
#include "world/common/npc/KoopaKoot/idle.h"
#include "world/common/npc/Koopa/idle.h"
#include "world/common/npc/Bobomb/idle.h"
#include "world/common/npc/Dryite/idle.h"
#include "world/common/npc/Chanterelle/idle.h"
#include "world/common/npc/MusicianPoet/idle.h"
#include "world/common/npc/MusicianComposer/idle.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupMusicMix;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_PlaySpellcastSong;
extern EvtScript EVS_PlayFlowerGateSong;
extern EvtScript EVS_ResetMusicAfterFortune;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupBadgeShop;
extern EvtScript EVS_SetupBulletinBoard;
extern EvtScript EVS_SetupCrystalBallGfx;
extern EvtScript EVS_SetupFlowerModels;
extern EvtScript EVS_EnterFlowerGate;
extern EvtScript EVS_ExitFlowerGate;
extern EvtScript EVS_Merlon_GiveHint;
extern EvtScript EVS_MerlonShooAway;
extern EvtScript EVS_SetupQuickChangeTrigger;
extern EvtScript EVS_Scene_IntroWalking;
extern EvtScript EVS_Scene_MailbagTheft;
extern EvtScript EVS_Scene_MerlonAndNinji;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList IntroNPCs;
extern NpcGroupList EpilogueNPCs;
extern NpcGroupList Chapter0NPCs;
extern NpcGroupList Chapter1NPCs;
extern NpcGroupList TwinkMeetingNPCs;
extern NpcGroupList Chapter4NPCs;
extern NpcGroupList NinjiMeetingNPCs;
extern NpcGroupList DefaultNPCs;

extern NpcData NpcData_Townsfolk[10];

extern ShopItemData RowfBadgeInventory[16];

extern EvtScript EVS_PlayShyGuyRunSounds;
