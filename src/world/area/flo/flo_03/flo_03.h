#pragma once

/// @file flo_03.h
/// @brief Flower Fields - (East) Petunia's Field

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

#include "sprite/npc/Dayzee.h"

enum {
    NPC_Petunia                 = 0,
    NPC_Dayzee                  = 1,
    NPC_MontyMole_01            = 2,
    NPC_MontyMole_02            = 3,
    NPC_MontyMole_03            = 4,
    NPC_MontyMole_04            = 5,
};

enum {
    MV_NextBurrowTime_Mole_01   = MapVar(10),
    MV_NextBurrowTime_Mole_02   = MapVar(11),
    MV_NextBurrowTime_Mole_03   = MapVar(12),
    MV_NextBurrowTime_Mole_04   = MapVar(13),
    MV_PauseBurrowing           = MapVar(14),
    MV_NextBurrowTriggerRadius  = MapVar(15),
};

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_PushFlowerSong;
extern EvtScript EVS_PopSong;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

extern EvtScript EVS_Scene_SunReturns;
extern EvtScript EVS_SetupMoles;
extern EvtScript EVS_EmptyEntityHandler;
