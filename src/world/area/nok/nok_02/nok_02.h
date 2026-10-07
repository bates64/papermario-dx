#pragma once

/// @file nok_02.h
/// @brief Koopa Region - Koopa Village 2

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "map.xml.h"

#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/KooperWithoutShell.h"
#include "sprite/npc/KoopaWithoutShell.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/npc/WorldBobomb.h"
#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/Kolorado.h"
#include "sprite/npc/KoloradoWife.h"
#include "sprite/npc/KoopaKoot.h"

enum {
    NPC_Koopa_01                = 0,
    NPC_FuzzyThief              = 1,
    NPC_KoopaShell_01           = 2,
    NPC_Koopa_02                = 3,
    NPC_KoopaShell_02           = 4,
    NPC_Koopa_03                = 5,
    NPC_Koopa_04                = 6,
    NPC_Kolorado                = 7,
    NPC_KoloradoWife            = 8,
    NPC_KoopaKoot               = 9,
    NPC_Kooper                  = 10,
    NPC_KoopersShell            = 11,
    NPC_FuzzyBoss               = 12,
    NPC_MiscFuzzy1              = 13,
    NPC_MiscFuzzy2              = 14,
    NPC_Fuzzy_Later             = 15,
    NPC_Bobomb_01               = 16,
    NPC_Bobomb_02               = 17,
    NPC_Bobomb_03               = 18,
    NPC_ChuckQuizmo             = 19,
    // epilogue
    NPC_Parakarry               = 0,
    NPC_Bombette                = 1,
    NPC_KoloradoWife_Epilogue   = 2,
};

enum {
    MV_KoopaChaseThiefScript    = MapVar(0),
    MV_KoopaChaseMonitorScript  = MapVar(1),
    MV_IsPlayerNearbyThief      = MapVar(2),
    MV_KooperFightSoundsScript  = MapVar(3),
    MV_StarPieceItem            = MapVar(10),
};

enum {
    MF_FuzzyBossTaunt   = MapFlag(0),
    MF_Bush1_Drop       = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Scene_Epilogue;
extern EvtScript EVS_BreakBlock_DropShell;
extern EvtScript EVS_Scene_MeetKooper;
extern EvtScript EVS_FuzzyBoss_PlayerEntersKoopersHouse;
extern EvtScript EVS_SetupKootFavors;
extern EvtScript EVS_NpcInteract_KoopaKoot;
extern EvtScript EVS_Setup_Bookshelf;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_SetupDemo;

extern NpcGroupList EpilogueNPCs;
extern NpcGroupList CrisisNPCs;
extern NpcGroupList NormalNPCs;
