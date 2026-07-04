#pragma once
#include "base.h"

#define EVAR_STONE_CHOMP_FLOOR_Y 0 // initialized from NpcData.initVar[0]

extern EvtScript N(EVS_NpcCreate_StoneChomp);
extern MobileAISettings N(AISettings_StoneChomp_Wander);
extern EvtScript N(EVS_NpcAI_StoneChomp_Wander);
extern EvtScript N(EVS_NpcHit_StoneChomp);
extern EvtScript N(EVS_NpcDefeat_StoneChomp);
extern NpcSettings N(NpcSettings_StoneChomp_Wander);
