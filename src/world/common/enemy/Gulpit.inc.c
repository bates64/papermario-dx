#include "Gulpit.h"

#include "world/common/enemy/ai/WanderMeleeAI.inc.c"

#include "world/common/enemy/ai/GenericHitboxDefeat.inc.c"

MobileAISettings N(AISettings_Gulpit) = {
    .moveSpeed = 0.5f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 100.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 20,
    .chaseRadius = 150.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Gulpit) = {
    Call(SetSelfVar, AI_VAR_MELEE_STATUS, MELEE_ATTACK_PHASE_NONE)
    Call(SetSelfVar, AI_VAR_MELEE_PRE_TIME, 5)
    Call(SetSelfVar, AI_VAR_MELEE_SWING_TIME, 13)
    Call(SetSelfVar, AI_VAR_MELEE_POST_TIME, 30)
    Call(N(WanderMeleeAI_Main), Ref(N(AISettings_Gulpit)))
    Return
    End
};

NpcSettings N(NpcSettings_Gulpit) = {
    .height = 48,
    .radius = 36,
    .level = ACTOR_LEVEL_GULPIT,
    .doAI = &N(EVS_NpcAI_Gulpit),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

EvtScript N(EVS_NpcAI_Gulpit_Hitbox) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, AI_VAR_HITBOX_YOFFSET, 6)
    Call(SetSelfVar, AI_VAR_HITBOX_DIST, 28)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_RANGE, 55)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_ANGLE, 32)
    Call(SetSelfVar, AI_VAR_HITBOX_STRIKE_TIME, 10)
    Call(SetSelfVar, AI_VAR_HITBOX_SOUND, SOUND_NONE)
    Call(N(MeleeHitbox_Main))
    Return
    End
};

NpcSettings N(NpcSettings_Gulpit_Hitbox) = {
    .height = 32,
    .radius = 22,
    .level = ACTOR_LEVEL_GULPIT,
    .doAI = &N(EVS_NpcAI_Gulpit_Hitbox),
    .onDefeat = &N(EVS_GenericHitboxDefeat),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};

AnimID N(ExtraAnims_Gulpit_Hitbox)[] = {
    ANIM_Gulpit_Anim00,
    ANIM_LIST_END
};

AnimID N(ExtraAnims_Gulpit)[] = {
    ANIM_Gulpit_Anim00,
    ANIM_Gulpit_Anim01,
    ANIM_Gulpit_Anim0B,
    ANIM_Gulpit_Anim04,
    ANIM_Gulpit_Anim02,
    ANIM_Gulpit_Anim03,
    ANIM_LIST_END
};
