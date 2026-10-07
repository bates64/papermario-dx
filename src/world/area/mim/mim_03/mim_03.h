#pragma once

/// @file mim_03.h
/// @brief Forever Forest - Flowers (Oaklie)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../mim.h"
#include "map.xml.h"

enum {
    NPC_Oaklie                  = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupExitHint;
extern EvtScript EVS_SetupGates;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;
