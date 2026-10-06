#pragma once
#include "base.h"

#define EVAR_STONE_CHOMP_FLOOR_Y 0 // initialized from NpcData.initVar[0]

extern EvtScript EVS_NpcCreate_StoneChomp;
extern MobileAISettings AISettings_StoneChomp_Wander;
extern EvtScript EVS_NpcAI_StoneChomp_Wander;
extern EvtScript EVS_NpcHit_StoneChomp;
extern EvtScript EVS_NpcDefeat_StoneChomp;
extern NpcSettings NpcSettings_StoneChomp_Wander;
