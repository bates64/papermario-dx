#pragma once

/// @file mac_05.h
/// @brief Toad Town - Port District

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mac.h"
#include "mapfs/mac_05_shape.h"
#include "mapfs/mac_05_hit.h"

#include "sprite/npc/Kolorado.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Fuzzipede.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/WorldKooper.h"
#include "sprite/npc/WorldBombette.h"
#include "sprite/npc/WorldBow.h"
#include "sprite/npc/WorldWatt.h"
#include "sprite/npc/JrTroopa.h"
#include "sprite/npc/Fishmael.h"
#include "sprite/npc/Toad.h"

enum {
    NPC_Whale                   = 0,
    NPC_Kolorado                = 1,
    NPC_Fishmael                = 2,
    NPC_Fuzzipede               = 3,
    NPC_JrTroopa_01             = 4,
    NPC_JrTroopa_02             = 5,
    NPC_ChuckQuizmo             = 6,
    NPC_Bartender               = 7,
    NPC_Toad_02                 = 8,
    NPC_Chanterelle             = 9,
    NPC_ArtistToad              = 10,
    NPC_TradeEventToad          = 11,
    NPC_Toad_04                 = 12,
    NPC_Toad_05                 = 13,
    NPC_Toad_06                 = 14,
    NPC_Toad_07                 = 15,
};

enum {
    MF_WhaleDepartureReady      = MapFlag(1),
    MF_DivaSongPlaying          = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_Scene_ArriveByWhale;
extern EvtScript EVS_Scene_FuzzipedeDefeated;
extern EvtScript EVS_SetupWhale;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_AnimateClub64Sign;
extern EvtScript EVS_MakeEntities;

extern EvtScript EVS_80244298;
extern EvtScript EVS_802442C4;
extern EvtScript EVS_802442E8;
extern EvtScript EVS_80244314;
extern EvtScript EVS_80244340;

extern NpcGroupList NpcSetA;
extern NpcGroupList NpcSetB;
extern NpcGroupList NpcSetC;
