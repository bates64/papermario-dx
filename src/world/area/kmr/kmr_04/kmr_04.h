#pragma once

/// @file kmr_04.h
/// @brief Goomba Region - Jr. Troopa's Playground

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "mapfs/kmr_04_shape.h"
#include "mapfs/kmr_04_hit.h"

#include "sprite/npc/Goompa.h"
#include "sprite/npc/JrTroopa.h"

enum {
    NPC_JrTroopa        = 0,
    NPC_Goompa          = 1,
};

enum {
    MF_Drop_Bush1       = MapFlag(10),
    MF_Drop_Bush2       = MapFlag(11),
    MF_Drop_Bush3A      = MapFlag(12),
    MF_Drop_Bush3B      = MapFlag(13),
    MF_Drop_Bush4       = MapFlag(14),
    MF_Drop_Bush5       = MapFlag(15),
    MF_GotHammerDone    = MapFlag(18),
};

#define NAMESPACE kmr_04

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetNormalMusic);
extern EvtScript N(EVS_SetJrTroopaMusic);
extern EvtScript N(EVS_PlayUpgradeSong);
extern EvtScript N(EVS_SetupFoliage);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);
