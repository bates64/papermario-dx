#pragma once
#include "base.h"

extern EvtScript EVS_NpcAI_HurtPlant;
extern EvtScript EVS_NpcInteract_HurtPlant;
extern EvtScript EVS_NpcDefeat_HurtPlant;
extern NpcSettings NpcSettings_HurtPlant;

#define HURT_PLANT_FLAGS \
    BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER
