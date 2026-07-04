#pragma once
#include "base.h"

extern EvtScript N(EVS_NpcAI_MBush);
extern EvtScript N(EVS_NpcInteract_MBush);
extern EvtScript N(EVS_NpcDefeat_MBush);
extern NpcSettings N(NpcSettings_MBush);

#define MBUSH_FLAGS \
    BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER
