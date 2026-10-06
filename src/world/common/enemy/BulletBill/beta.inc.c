#pragma once
#include "base.h"
#include "world/ai.h"

EvtScript EVS_NpcAI_BulletBill_Beta = {
    Return
    End
};

EvtScript EVS_NpcCreate_BulletBill_Beta = {
    Return
    End
};

EvtScript EVS_NpcDefeat_BulletBill_Beta = {
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

NpcSettings NpcSettings_BulletBill_Beta = {
    .defaultAnim = ANIM_BulletBill_Idle,
    .height = 14,
    .radius = 31,
    .level = ACTOR_LEVEL_BULLET_BILL,
    .doAI = &EVS_NpcAI_BulletBill_Beta,
    .onCreate = &EVS_NpcCreate_BulletBill_Beta,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EVS_NpcDefeat_BulletBill_Beta,
};
