#pragma once
#include "base.h"

extern EvtScript N(EVS_NpcDefeat_MontyMole_Stone);
extern MobileAISettings N(AISettings_MontyMole_StoneThrower);
extern EvtScript N(EVS_NpcAI_MontyMole_StoneThrower);
extern NpcSettings N(NpcSettings_MontyMole_StoneThrower);
extern MobileAISettings N(AISettings_MontyMole_Stone);
extern EvtScript N(EVS_NpcAI_MontyMole_Stone);
extern EvtScript N(EVS_NpcHit_MontyMole_Stone_DoNothing);
extern EvtScript N(EVS_NpcHit_MontyMole_Stone);
extern NpcSettings N(NpcSettings_MontyMole_Stone);

#define MONTY_MOLE_STONE_HITBOX(npcID) \
{ \
    .id = npcID, \
    .settings = &N(NpcSettings_MontyMole_Stone), \
    .pos = { NPC_DISPOSE_LOCATION }, \
    .yaw = 90, \
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DROPS, \
    .drops = NO_DROPS, \
    .territory = { \
        .wander = { \
            .isFlying = true, \
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED, \
            .wanderShape = SHAPE_CYLINDER, \
            .centerPos  = { NPC_DISPOSE_LOCATION }, \
            .wanderSize = { 0 }, \
            .detectShape = SHAPE_CYLINDER, \
            .detectPos  = { 0, 0, 0 }, \
            .detectSize = { 0 }, \
        } \
    }, \
    .animations = { \
        .idle   = ANIM_MontyMole_Anim0F, \
        .walk   = ANIM_MontyMole_Anim0F, \
        .run    = ANIM_MontyMole_Anim0F, \
        .chase  = ANIM_MontyMole_Anim0F, \
        .alert  = ANIM_MontyMole_Anim0F, \
        .unused = ANIM_MontyMole_Anim0F, \
        .death  = ANIM_MontyMole_Anim0F, \
        .hit    = ANIM_MontyMole_Anim0F, \
        .anim_8 = ANIM_MontyMole_Anim0F, \
        .anim_9 = ANIM_MontyMole_Anim0F, \
        .anim_A = ANIM_MontyMole_Anim0F, \
        .anim_B = ANIM_MontyMole_Anim0F, \
        .anim_C = ANIM_MontyMole_Anim0F, \
        .anim_D = ANIM_MontyMole_Anim0F, \
        .anim_E = ANIM_MontyMole_Anim0F, \
        .anim_F = ANIM_MontyMole_Anim0F, \
    }, \
}
