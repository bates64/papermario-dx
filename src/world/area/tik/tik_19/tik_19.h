#pragma once

/// @file tik_19.h
/// @brief Toad Town Tunnels - Under the Toad Town Pond

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../tik.h"
#include "map.xml.h"

enum {
    MV_SuperBlock   = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
