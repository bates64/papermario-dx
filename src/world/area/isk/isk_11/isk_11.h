#pragma once

/// @file isk_11.h
/// @brief Dry Dry Ruins - Stone Puzzle Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "map.xml.h"

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

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupPuzzle;
extern EvtScript EVS_ManageSecretPassage;
extern EvtScript EVS_SetupLock;
extern EvtScript EVS_MakeEntities;
