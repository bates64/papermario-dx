#pragma once
#include "base.h"

extern EvtScript EVS_NpcAI_MBush;
extern EvtScript EVS_NpcInteract_MBush;
extern EvtScript EVS_NpcDefeat_MBush;
extern NpcSettings NpcSettings_MBush;

#define MBUSH_FLAGS \
    BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER
