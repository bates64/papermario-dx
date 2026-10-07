#pragma once

/// @file jan_13.h
/// @brief Jade Jungle - Deep Jungle 2 (Block Puzzle)

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../jan.h"
#include "map.xml.h"

enum {
    MV_PuzzleProgress       = MapVar(0),
};

enum {
    MF_GeyserSoundPlaying   = MapFlag(10),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupPuzzle;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_MakeEntities;
