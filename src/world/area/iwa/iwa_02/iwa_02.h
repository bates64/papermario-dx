#pragma once

/// @file iwa_02.h
/// @brief Mt Rugged - Mt Rugged 3

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../iwa.h"
#include "map.xml.h"

enum {
    NPC_Cleft_01                = 0,
    NPC_Cleft_02                = 1,
    NPC_Cleft_03                = 2,
    NPC_MontyMole               = 3,
    NPC_MontyMole_Hole          = 4,
    NPC_Bubulb                  = 5,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
