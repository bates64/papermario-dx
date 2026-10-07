#pragma once

/// @file nok_12.h
/// @brief Koopa Region - Pleasant Path Bridge

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../nok.h"
#include "map.xml.h"

#include "sprite/npc/SpikedGoomba.h"
#include "sprite/npc/KoopaTroopa.h"
#include "sprite/npc/Goomba.h"

enum {
    NPC_KoopaTroopa_01          = 0,
    NPC_KoopaTroopa_02          = 1,
    NPC_Goomba                  = 2,
    NPC_SpikedGoomba            = 3,
};

enum {
    MV_SwitchEntityID   = MapVar(0),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_OnShakeTree_DropSwitch;
extern EvtScript EVS_SetupBridge;
extern EvtScript EVS_PlayDemoScene1;
extern EvtScript EVS_PlayDemoScene2;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;
extern NpcGroupList DefaultNPCs;
extern NpcGroupList DemoNPCs;
