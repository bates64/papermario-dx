#include "PiranhaPlant.h"

#include "world/common/enemy/ai/PiranhaPlantAI.inc.c"

#include "world/common/enemy/ai/GenericHitboxDefeat.inc.c"

MobileAISettings N(AISettings_PiranhaPlant) = {
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 150.0f,
    .playerSearchInterval = 1,
};

EvtScript N(EVS_NpcAI_PiranhaPlant) = {
    Call(SetSelfVar, AI_VAR_PIRANHA_PATH_USING_COLLISION, false)
    Call(SetSelfVar, AI_VAR_PIRANHA_BURROW_TIME, 12)
    Call(SetSelfVar, AI_VAR_PIRANHA_INTANGIBLE_TIME, 11)
    Call(SetSelfVar, AI_VAR_PIRANHA_EMERGE_TIME, 14)
    Call(SetSelfVar, AI_VAR_PIRANHA_TANGIBLE_TIME, 9)
    Call(SetSelfVar, AI_VAR_PIRANHA_WINDUP_ANIM_TIME, -1)
    Call(SetSelfVar, AI_VAR_PIRANHA_BEGIN_ATTACK_TIME, 10)
    Call(SetSelfVar, AI_VAR_PIRANHA_END_ATTACK_TIME, 25)
    Call(SetSelfVar, AI_VAR_PIRANHA_COOLDOWN_TIME, 15)
    Call(N(PiranhaPlantAI_Main), Ref(N(AISettings_PiranhaPlant)))
    Return
    End
};

NpcSettings N(NpcSettings_PiranhaPlant) = {
    .height = 32,
    .radius = 26,
    .level = ACTOR_LEVEL_PIRANHA_PLANT,
    .doAI = &N(EVS_NpcAI_PiranhaPlant),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

EvtScript N(EVS_NpcAI_PiranhaPlant_Hitbox) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, AI_VAR_HITBOX_YOFFSET, 10)
    Call(SetSelfVar, AI_VAR_HITBOX_DIST, 18)
    Call(SetSelfVar, AI_VAR_HITBOX_STRIKE_TIME, 3)
    Call(SetSelfVar, AI_VAR_HITBOX_SOUND, SOUND_PIRANHA_BITE)
    Call(N(MeleeHitbox_Main))
    Return
    End
};

NpcSettings N(NpcSettings_PiranhaPlant_Hitbox) = {
    .height = 18,
    .radius = 18,
    .level = ACTOR_LEVEL_PIRANHA_PLANT,
    .doAI = &N(EVS_NpcAI_PiranhaPlant_Hitbox),
    .onDefeat = &N(EVS_GenericHitboxDefeat),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
