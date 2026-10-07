#pragma once

/// @file flo_00.h
/// @brief Flower Fields - Center

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "map.xml.h"

#include "sprite/npc/WorldLakilester.h"
#include "sprite/npc/WorldParakarry.h"

enum {
    NPC_Dummy_Wisterwood        = 0,
    NPC_Bubulb_01               = 1,
    NPC_Bubulb_02               = 2,
    NPC_Bubulb_03               = 3,
    NPC_Bubulb_04               = 4,
    NPC_Tolielup                = 5,
    NPC_Klevar                  = 6,
    NPC_Lakilulu                = 7,
    NPC_Lakilester_Epilogue     = 0,
    NPC_Lakilulu_Epilogue       = 1,
    NPC_Parakarry_Epilogue      = 2,
};

enum {
    MV_BeanstalkSceneSync       = MapVar(10),
    MV_ItemEntity_Beanstalk     = MapVar(11),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_Scene_Epilogue;
extern EvtScript EVS_Interact_Wisterwood;
extern EvtScript EVS_Wisterwood_Exit;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;

extern EvtScript EVS_Scene_SunReturns;
extern EvtScript EVS_SetupBeanPatch;
extern EvtScript EVS_SetupBeanstalk;
extern EvtScript EVS_Enter_Beanstalk;
extern EvtScript EVS_Scene_BeanstalkGrewRemark;

extern NpcGroupList DefaultNPCs;
extern NpcGroupList EpilogueNPCs;
