#pragma once

/// @file kmr_02.h
/// @brief Goomba Region - Goomba Village

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "mapfs/kmr_02_shape.h"
#include "mapfs/kmr_02_hit.h"

#include "sprite/npc/Goompa.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/Goombaria.h"
#include "sprite/npc/Gooma.h"
#include "sprite/npc/Goompapa.h"
#include "sprite/npc/Goomama.h"
#include "sprite/npc/Toad.h"
#include "sprite/npc/WorldEldstar.h"
#include "sprite/npc/WorldKammy.h"

enum {
    NPC_Goompa                  = 0,
    NPC_Goombaria               = 1,
    NPC_Goombario               = 2,
    NPC_Goompapa                = 3,
    NPC_Goomama                 = 4,
    NPC_Gooma                   = 5,
    NPC_Toad                    = 6,
    NPC_Kammy                   = 7,
    NPC_ChuckQuizmo             = 8,
    NPC_Eldstar_01              = 11,
    NPC_Eldstar_02              = 12,
    NPC_Parakarry               = 13,
};

enum {
    MV_HologramNoiseBase    = MapVar(0),
    MV_HologramAlpha        = MapVar(1),
    MV_KammySoundsTID       = MapVar(4),
    MV_TrackKammyTID        = MapVar(5),
};

enum {
    MF_SpawnFlag_BushCoin   = MapFlag(10),
    MF_SpawnFlag_Goomnut    = MapFlag(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_FadeOutMusic;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_PushNewPartnerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_SetupToadHouse;
extern EvtScript EVS_SetWallsDown_ToadHouse;
extern EvtScript EVS_Scene_KammyCrushesGate;
extern EvtScript EVS_NpcAux_Kammy;
extern EvtScript EVS_SummonGateBlock;
extern EvtScript EVS_NpcInteract_ToadHouse;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList EpilogueNPCs;
extern NpcGroupList NpcGroup1;
extern NpcGroupList PrologueNPCs;
extern NpcGroupList DefaultNPCs;

extern API_CALLABLE(SetWanderTerritory);
extern EvtScript EVS_NpcIdle_SwitchedWander;


#include "world/common/npc/Goombaria/wander.h"
#include "world/common/npc/Goombario/wander.h"
#include "world/common/npc/Gooma/wander.h"
#include "world/common/npc/Goompa/wander.h"
#include "world/common/npc/Goomama/wander.h"
#include "world/common/npc/Goompapa/wander.h"

extern IMG_BIN kmr_02_heart_block_img[];
extern PAL_BIN kmr_02_heart_block_pal[];
