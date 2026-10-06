#pragma once
#include "stone_thrower.h"

#include "world/common/ai/MontyMoleAI.inc.c"
#include "world/common/ai/WanderRangedAI.inc.c"

EvtScript EVS_NpcDefeat_MontyMole_Stone = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_DONE)
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

MobileAISettings AISettings_MontyMole_StoneThrower = {
    .moveSpeed = 1.7f,
    .moveTime = 90,
    .alertRadius = 110.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 7.5f,
    .chaseRadius = 110.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_MontyMole_StoneThrower = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE | NPC_FLAG_FLIP_INSTANTLY, true)
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(RandInt, 15, LVar0)
    Add(LVar0, 15)
    Wait(LVar0)
    Call(MontyMoleAI_Main, Ref(AISettings_MontyMole_StoneThrower))
    Return
    End
};

NpcSettings NpcSettings_MontyMole_StoneThrower = {
    .height = 20,
    .radius = 24,
    .level = ACTOR_LEVEL_MONTY_MOLE,
    .doAI = &EVS_NpcAI_MontyMole_StoneThrower,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};

MobileAISettings AISettings_MontyMole_Stone = {
    .moveSpeed = 8.3f,
    .alertRadius = 2.5f,
    .alertOffsetDist = 0.4f,
    .playerSearchInterval = -1,
};

EvtScript EVS_NpcAI_MontyMole_Stone = {
    Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
    Call(SetSelfVar, AI_VAR_MISSILE_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_Y, 17)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_R, 17)
    Call(MissileAI_Main, Ref(AISettings_MontyMole_Stone))
    Return
    End
};

EvtScript EVS_NpcHit_MontyMole_Stone_DoNothing = {
    Return
    End
};

EvtScript EVS_NpcHit_MontyMole_Stone = {
    Call(GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcHit_MontyMole_Stone_DoNothing))
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseOrEq(ENCOUNTER_TRIGGER_HAMMER)
        CaseOrEq(ENCOUNTER_TRIGGER_SPIN)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_REFLECTING)
            Call(MissileAI_Reflect)
            IfEq(LVar0, 0)
                Return
            EndIf
        EndCaseGroup
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_DESTROYED)
            Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
            PlayEffect(EFFECT_WALKING_DUST, 2, LVar0, LVar1, LVar2, 0, 0)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
        CaseDefault
            Call(SetBattleAsScripted)
    EndSwitch
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_MontyMole_Stone))
    Return
    End
};

NpcSettings NpcSettings_MontyMole_Stone = {
    .height = 12,
    .radius = 12,
    .doAI = &EVS_NpcAI_MontyMole_Stone,
    .onHit = &EVS_NpcHit_MontyMole_Stone,
    .onDefeat = &EVS_NpcDefeat_MontyMole_Stone,
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
