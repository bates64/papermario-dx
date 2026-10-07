#pragma once

/// @file pra_32.h
/// @brief Crystal Palace - Crystal Summit

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    NPC_CrystalKing_01  = 0,
    NPC_CrystalKing_02  = 1,
    NPC_Kalmar          = 2,
    NPC_CrystalKing_03  = 3,
};

enum {
    MV_CamDistance      = MapVar(0),
    MV_SpiritCardData   = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_RespawnStarCard;
extern EvtScript EVS_SpawnStarCard;
extern EvtScript EVS_80240D3C;
extern NpcGroupList DefaultNPCs;
