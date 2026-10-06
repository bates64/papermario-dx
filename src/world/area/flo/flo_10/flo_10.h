#pragma once

/// @file flo_10.h
/// @brief Flower Fields - (SE) Lily's Fountain

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_10_shape.h"
#include "mapfs/flo_10_hit.h"

enum {
    NPC_Lily                    = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushFlowerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFountain;
extern EvtScript EVS_SetupWaterStoneSocket;
extern EvtScript EVS_SetupWaterEffect;

extern EvtScript EVS_Scene_ReleaseFountain;
extern EvtScript EVS_Scene_PostReleaseFountain;
extern EvtScript EVS_Scene_SunReturns;

extern NpcGroupList DefaultNPCs;
