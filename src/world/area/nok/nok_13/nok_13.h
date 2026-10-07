#pragma once

/// @file nok_13.h
/// @brief Koopa Region - Pleasant Crossroads

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "map.xml.h"

enum {
    NPC_UnusedFuzzy     = 1,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupMusicalHill;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;

