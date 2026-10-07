#pragma once

/// @file pra_34.h
/// @brief Crystal Palace - Mirror Hole Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    MV_FarPadlockEntityID   = MapVar(0),
    MV_NearPadlockEntityID  = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ExitDoors_pra_31_0;
extern EvtScript EVS_ExitDoors_pra_31_2;
extern EvtScript EVS_MakeEntities;
