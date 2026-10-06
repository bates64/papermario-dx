#pragma once

/// @file flo_19.h
/// @brief Flower Fields - Cloudy Climb

#include "common.h"
#include "generated.h"
#include "message_ids.h"
#include "map.h"

#include "../flo.h"
#include "mapfs/flo_19_shape.h"
#include "mapfs/flo_19_hit.h"

enum {
    NPC_Dummy_Partner   = 0,
};

enum {
    MV_BeanstalkSceneSync       = MapVar(10),
    MV_BeanstalkGrowthProgress  = MapVar(11),
    MV_Distortion_Platform_01   = MapVar(12),
    MV_Distortion_Platform_02   = MapVar(13),
    MV_Distortion_Platform_03   = MapVar(14),
    MV_Distortion_Platform_04   = MapVar(15),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupClouds;
extern EvtScript EVS_SetupBeanstalk;
extern EvtScript EVS_Scene_BeanstalkGrowing;
extern EvtScript EVS_Enter_Beanstalk;
