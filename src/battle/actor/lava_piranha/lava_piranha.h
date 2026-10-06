#pragma once

#include "battle/battle.h"
#include "script_api/battle.h"
#include "effects.h"
#include "battle/common/lava_piranha.h"

// Shared only within this overlay. Buds are internal actors, not public variants.
extern ActorBlueprint BudBlueprint;
extern s32 BudFieryAnims[];
extern s32 BudFieryDefense[];
extern EvtScript EVS_Ignite;

extern StaticAnimatorNode* ShatterGroundModel[];
extern StaticAnimatorNode* MainHeadVineModel[];
extern StaticAnimatorNode* SideHeadVineModel[];
extern StaticAnimatorNode* ExtraVineModel[];
extern AnimScript AS_ShatterGround;
