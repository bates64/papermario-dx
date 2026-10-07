#pragma once

/// @file sam_09.h
/// @brief Mt Shiver - Shiver Mountain Tunnel

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../sam.h"
#include "map.xml.h"

enum {
    MV_Socket1_ItemID       = MapVar(0),
    MV_Socket2_ItemID       = MapVar(1),
    MV_Socket3_ItemID       = MapVar(2),
    MV_Socket1_ItemEntityID       = MapVar(3),
    MV_Socket2_ItemEntityID       = MapVar(4),
    MV_Socket3_ItemEntityID       = MapVar(5),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupSockets;
extern EvtScript EVS_MakeEntities;
