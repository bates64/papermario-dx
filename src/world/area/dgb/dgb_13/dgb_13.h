#pragma once

/// @file dgb_13.h
/// @brief Tubba's Castle - Hidden Bedroom (2F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    MV_LowerDrawerOpen       = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupDrawers;
extern EvtScript EVS_MakeEntities;
