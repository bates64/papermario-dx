#pragma once

/// @file hos_04.h
/// @brief Shooting Star Summit - Outside the Sanctuary

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../hos.h"
#include "map.xml.h"

#include "sprite/npc/Twink.h"

enum {
    NPC_Twink   = 0,
};

enum {
    MV_Starship_PosX    = MapVar(10),
    MV_Starship_PosY    = MapVar(11),
    MV_Starship_PosZ    = MapVar(12),
    MV_Starship_Yaw     = MapVar(13),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Starship_FlyingAway;
extern EvtScript EVS_SetupNarrator;
extern EvtScript EVS_Intro_PreHeist_Unused;
extern EvtScript EVS_Intro_PostHeist;
extern EvtScript EVS_SetupFountains;
extern EvtScript EVS_BetaStarship_Flight1;
extern EvtScript EVS_BetaStarship_Flight2;
extern EvtScript EVS_BetaStarship_Return;
extern NpcGroupList DefaultNPCs;
