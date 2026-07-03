#pragma once
#include "hitbox.h"

EvtScript N(EVS_NpcDefeat_FrostClubba) = {
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

AnimID N(LimitAnims_FrostClubba)[] = {
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

AnimID N(LimitAnims_FrostClubba_Hitbox)[] = {
    ANIM_WorldClubba_Still,
    ANIM_LIST_END
};

#include "world/common/ai/MeleeAttack.inc.c"

EvtScript N(EVS_NpcAI_FrostClubba_Hitbox) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, AI_VAR_HITBOX_YOFFSET, 4)
    Call(SetSelfVar, AI_VAR_HITBOX_DIST, 32)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_RANGE, 48)
    Call(SetSelfVar, AI_VAR_HITBOX_SIGHT_ANGLE, 30)
    Call(SetSelfVar, AI_VAR_HITBOX_STRIKE_TIME, 3)
    Call(SetSelfVar, AI_VAR_HITBOX_SOUND, SOUND_CLUBBA_SWING)
    Call(N(MeleeHitbox_Main))
    Return
    End
};

NpcSettings N(NpcSettings_FrostClubba_Hitbox) = {
    .height = 14,
    .radius = 16,
    .level = ACTOR_LEVEL_WHITE_CLUBBA,
    .doAI = &N(EVS_NpcAI_FrostClubba_Hitbox),
    .onDefeat = &N(EVS_NpcDefeat_FrostClubba),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
