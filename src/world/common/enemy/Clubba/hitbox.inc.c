#pragma once
#include "hitbox.h"

EvtScript N(EVS_NpcDefeat_Clubba) = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(RemoveNpc, NPC_SELF)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            Call(OnPlayerFled, true)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

AnimID N(LimitAnims_Clubba)[] = {
    ANIM_WorldClubba_Still,
    ANIM_WorldClubba_Idle,
    ANIM_WorldClubba_Walk,
    ANIM_WorldClubba_Run,
    ANIM_WorldClubba_Hurt,
    ANIM_WorldClubba_Sleep,
    ANIM_WorldClubba_WakeUp,
    ANIM_WorldClubba_RaiseClub,
    ANIM_WorldClubba_SwingClub,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Clubba_Hitbox)[] = {
    ANIM_WorldClubba_Still,
    ANIM_LIST_END
};

#include "world/common/ai/MeleeAttack.inc.c"

EvtScript N(EVS_NpcAI_Clubba_Hitbox) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, AI_VAR_HITBOX_YOFFSET, 4)
    Call(SetSelfVar, AI_VAR_HITBOX_DIST, 32)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_RANGE, 50)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_ANGLE, 32)
    Call(SetSelfVar, AI_VAR_HITBOX_STRIKE_TIME, 3)
    Call(SetSelfVar, AI_VAR_HITBOX_SOUND, SOUND_CLUBBA_SWING)
    Call(N(MeleeHitbox_Main))
    Return
    End
};

NpcSettings N(NpcSettings_Clubba_Hitbox) = {
    .height = 14,
    .radius = 18,
    .level = ACTOR_LEVEL_CLUBBA,
    .doAI = &N(EVS_NpcAI_Clubba_Hitbox),
    .onDefeat = &N(EVS_NpcDefeat_Clubba),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
