#pragma once
#include "base.h"
#include "world/ai.h"

EvtScript N(EVS_NpcAI_BulletBill_Beta) = {
    Return
    End
};

EvtScript N(EVS_NpcCreate_BulletBill_Beta) = {
    Return
    End
};

EvtScript N(EVS_NpcDefeat_BulletBill_Beta) = {
    Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(DoNpcDefeat)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
        CaseEq(OUTCOME_PLAYER_FLED)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EndSwitch
    Return
    End
};

NpcSettings N(NpcSettings_BulletBill_Beta) = {
    .defaultAnim = ANIM_BulletBill_Idle,
    .height = 14,
    .radius = 31,
    .level = ACTOR_LEVEL_BULLET_BILL,
    .doAI = &N(EVS_NpcAI_BulletBill_Beta),
    .onCreate = &N(EVS_NpcCreate_BulletBill_Beta),
    .onHit = &EnemyNpcHit,
    .onDefeat = &N(EVS_NpcDefeat_BulletBill_Beta),
};
