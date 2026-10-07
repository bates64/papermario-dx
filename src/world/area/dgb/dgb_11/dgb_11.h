#pragma once

/// @file dgb_11.h
/// @brief Tubba's Castle - Covered Tables Room (1F)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dgb.h"
#include "map.xml.h"

enum {
    MV_SpringEntityID   = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
