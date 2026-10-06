#pragma once

/// @file nok_01.h
/// @brief Koopa Region - Koopa Village 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "mapfs/nok_01_shape.h"
#include "mapfs/nok_01_hit.h"

#include "sprite/npc/WorldBombette.h"

enum {
    NPC_Koover                  = 0,
    NPC_FuzzyWithShell          = 1,
    NPC_KooversShell            = 2,
    NPC_Koopa_02                = 3,
    NPC_KoopaShell_02           = 4,
    NPC_Koopa_03                = 5,
    NPC_KoopaShell_03           = 6,
    NPC_RelaxedKoopa            = 7,
    NPC_MortT                   = 8,
    NPC_Koopa_ShopOwner         = 9,
    NPC_MiscFuzzy1              = 10,
    NPC_MiscFuzzy2              = 11,
    NPC_Bobomb_01               = 12,
    NPC_Bobomb_02               = 13,
    NPC_Bobomb_03               = 14,
    NPC_ChuckQuizmo             = 15,
};

enum {
    MF_Bush8_Drop       = MapFlag(10),
    MF_Bush9_Drop       = MapFlag(11),
    MF_Bush3_Drop       = MapFlag(12),
    MF_Bush1_Drop       = MapFlag(13),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_BreakBlock_DropShell;
extern EvtScript EVS_Scene_RecoverTreeShell;
extern EvtScript EVS_SetupShop;
extern EvtScript EVS_SetupRadio;
extern EvtScript EVS_MakeRooms;
extern EvtScript EVS_80242C38;
extern EvtScript EVS_80242DE0;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern NpcGroupList CrisisNPCs;
extern NpcGroupList NormalNPCs;

API_CALLABLE(InitializeRadio);
API_CALLABLE(SetRadioVolumeMax);
API_CALLABLE(SetRadioVolumeMute);
API_CALLABLE(MuteAllRadioStations);
API_CALLABLE(StopAllRadioStations);
