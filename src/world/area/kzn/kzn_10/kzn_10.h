#pragma once

/// @file kzn_10.h
/// @brief Mt Lavalava - Descent Toward Boss

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kzn.h"
#include "map.xml.h"

enum {
    MV_TrompPosX        = MapVar(0),
    MV_ScreenShakeTID   = MapVar(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupSpinyTromp;
