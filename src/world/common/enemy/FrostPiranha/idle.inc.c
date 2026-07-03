#pragma once
#include "idle.h"

#include "world/common/ai/PiranhaPlantAI.inc.c"

#include "world/common/ai/GenericHitboxDefeat.inc.c"

MobileAISettings N(AISettings_FrostPiranha) = {
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 150.0f,
    .playerSearchInterval = 1,
};

EvtScript N(EVS_NpcAI_FrostPiranha) = {
    Call(SetSelfVar, AI_VAR_PIRANHA_PATH_USING_COLLISION, true)
    Call(SetSelfVar, AI_VAR_PIRANHA_BURROW_TIME, 10)
    Call(SetSelfVar, AI_VAR_PIRANHA_INTANGIBLE_TIME, 9)
    Call(SetSelfVar, AI_VAR_PIRANHA_EMERGE_TIME, 12)
    Call(SetSelfVar, AI_VAR_PIRANHA_TANGIBLE_TIME, 7)
    Call(SetSelfVar, AI_VAR_PIRANHA_WINDUP_ANIM_TIME, 15)
    Call(SetSelfVar, AI_VAR_PIRANHA_BEGIN_ATTACK_TIME, 18)
    Call(SetSelfVar, AI_VAR_PIRANHA_END_ATTACK_TIME, 30)
    Call(SetSelfVar, AI_VAR_PIRANHA_COOLDOWN_TIME, 15)
    Call(N(PiranhaPlantAI_Main), Ref(N(AISettings_FrostPiranha)))
    Return
    End
};

NpcSettings N(NpcSettings_FrostPiranha) = {
    .height = 50,
    .radius = 36,
    .level = ACTOR_LEVEL_FROST_PIRANHA,
    .doAI = &N(EVS_NpcAI_FrostPiranha),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

EvtScript N(EVS_NpcAI_FrostPiranha_Hitbox) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, AI_VAR_HITBOX_YOFFSET, 14)
    Call(SetSelfVar, AI_VAR_HITBOX_DIST, 28)
    Call(SetSelfVar, AI_VAR_HITBOX_STRIKE_TIME, 3)
    Call(SetSelfVar, AI_VAR_HITBOX_SOUND, SOUND_PIRANHA_BITE)
    Call(N(MeleeHitbox_Main))
    Return
    End
};

EvtScript N(EVS_802425A8) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_NONE)
        CaseOrEq(ENCOUNTER_TRIGGER_JUMP)
        CaseOrEq(ENCOUNTER_TRIGGER_HAMMER)
        CaseOrEq(ENCOUNTER_TRIGGER_PARTNER)
            Call(GetSelfAnimationFromTable, ENEMY_ANIM_INDEX_HIT, LVar0)
            ExecWait(EVS_NpcHitRecoil)
        EndCaseGroup
    EndSwitch
    Return
    End
};

NpcSettings N(NpcSettings_FrostPiranha_Hitbox) = {
    .height = 20,
    .radius = 28,
    .level = ACTOR_LEVEL_FROST_PIRANHA,
    .doAI = &N(EVS_NpcAI_FrostPiranha_Hitbox),
    .onDefeat = &N(EVS_GenericHitboxDefeat),
};

AnimID N(LimitAnims_FrostPiranha_Hitbox)[] = {
    ANIM_LargePiranha_Frost_Still,
    ANIM_LIST_END
};

AnimID N(LimitAnims_FrostPiranha)[] = {
    ANIM_LargePiranha_Frost_Still,
    ANIM_LargePiranha_Frost_Idle,
    ANIM_LargePiranha_Frost_Hurt,
    ANIM_LargePiranha_Frost_Windup,
    ANIM_LargePiranha_Frost_Bite,
    ANIM_LargePiranha_Frost_Burrow,
    ANIM_LargePiranha_Frost_Emerge,
    ANIM_LIST_END
};
