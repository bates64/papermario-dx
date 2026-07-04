#pragma once
#include "base.h"

extern EvtScript N(EVS_NpcCreate_HeartPlant);
extern EvtScript N(EVS_HeartPlant_RebindInteractAfterDelay);
extern EvtScript N(EVS_NpcInteract_HeartPlant);
extern NpcSettings N(NpcSettings_HeartPlant);

#define HEART_PLANT_FLAGS \
    ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | \
    ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER
