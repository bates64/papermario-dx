#pragma once

/// @file isk_11.h
/// @brief Dry Dry Ruins - Stone Puzzle Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "mapfs/isk_11_shape.h"
#include "mapfs/isk_11_hit.h"

#define NAMESPACE isk_11

enum {
    MV_LockEntityID             = MapVar(0),
    MV_HiddenStairsRevealed     = MapVar(1),
    MV_PlayerPanicDone          = MapVar(2),
    MV_ItemEntity_Socket1       = MapVar(10),
    MV_ItemEntity_Socket2       = MapVar(11),
    MV_ItemEntity_Socket3       = MapVar(12),
    MV_ItemEntity_Socket4       = MapVar(13),
    MV_ItemEntity_Socket5       = MapVar(14),
};

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_SetupPuzzle);
extern EvtScript N(EVS_ManageSecretPassage);
extern EvtScript N(EVS_SetupLock);
extern EvtScript N(EVS_MakeEntities);
