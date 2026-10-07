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

// Shared animation buffers owned by this overlay. LoadVineAnim takes (animation, vine).
extern u8 Vine0Base[];
extern u8 Vine1Base[];
extern u8 Vine2Base[];
extern u8 Vine3Base[];
#define VINE_0_BASE (s32) Vine0Base
#define VINE_1_BASE (s32) Vine1Base
#define VINE_2_BASE (s32) Vine2Base
#define VINE_3_BASE (s32) Vine3Base
API_CALLABLE(LoadVineAnim);

extern StaticAnimatorNode* ShatterGroundModel[];
extern StaticAnimatorNode* MainHeadVineModel[];
extern StaticAnimatorNode* SideHeadVineModel[];
extern StaticAnimatorNode* ExtraVineModel[];
extern AnimScript AS_ShatterGround;
