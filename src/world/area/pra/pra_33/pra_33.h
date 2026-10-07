#pragma once

/// @file pra_33.h
/// @brief Crystal Palace - Turnstyle Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../pra.h"
#include "map.xml.h"

enum {
    MV_WallFlipped  = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
