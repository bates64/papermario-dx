#pragma once

/// @file kpa_63.h
/// @brief Bowser's Castle - Hanger

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kpa.h"
#include "map.xml.h"

enum {
    MV_Starship_PosY    = MapVar(10),
    MV_Starship_Yaw     = MapVar(11),
    MV_PlayerOnBoard    = MapVar(12),
    MV_PartnerOnBoard   = MapVar(13),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Starship_Arrive;
extern EvtScript EVS_Starship_Depart;
extern EvtScript EVS_SetupStarship;
extern EvtScript EVS_MakeEntities;
