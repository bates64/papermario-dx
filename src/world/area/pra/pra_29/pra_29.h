#pragma once

/// @file pra_29.h
/// @brief Crystal Palace - Hidden Bridge Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    MV_BridgeExtendAmt      = MapVar(0),
    MV_UnusedBridgeAlpha    = MapVar(1),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupBridge;
extern EvtScript EVS_MakeEntities;
