#pragma once
#include "wander.h"

#include "world/common/ai/MagikoopaAI.inc.c"

MobileAISettings AISettings_Magikoopa_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 120,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 15,
    .chaseRadius = 200.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Magikoopa_Wander = {
    Call(MagikoopaAI_Main, Ref(AISettings_Magikoopa_Wander))
    Return
    End
};

EvtScript EVS_NpcHit_Magikoopa = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_NONE)
            // do nothing
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

EvtScript EVS_NpcDefeat_Magikoopa = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(MagikoopaAI_OnPlayerWon)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(MagikoopaAI_OnPlayerFled)
            Call(OnPlayerFled, false)
    EndSwitch
    Return
    End
};

NpcSettings NpcSettings_Magikoopa_Wander = {
    .height = 32,
    .radius = 28,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .doAI = &EVS_NpcAI_Magikoopa_Wander,
    .onHit = &EVS_NpcHit_Magikoopa,
    .onDefeat = &EVS_NpcDefeat_Magikoopa,
};

AnimID LimitAnims_Magikoopa[] = {
    ANIM_Magikoopa_Still,
    ANIM_Magikoopa_Idle,
    ANIM_Magikoopa_Idle,
    ANIM_Magikoopa_Idle,
    ANIM_Magikoopa_Shout,
    ANIM_Magikoopa_CastSpell,
    ANIM_Magikoopa_Hurt,
    ANIM_LIST_END
};

EvtScript EVS_NpcCreate_Magikoopa_GroundHitbox = {
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_Y, 10)
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_R, 40)
    Return
    End
};

EvtScript EVS_NpcCreate_Magikoopa_FlyingHitbox = {
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_Y, 0)
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_R, 55)
    Return
    End
};

EvtScript EVS_NpcAI_Magikoopa_Hitbox = {
    Call(MagikoopaSpellAI_Main)
    Return
    End
};

EvtScript EVS_NpcHit_Magikoopa_Hitbox = {
    Call(MagikoopaSpellAI_OnHitInit)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(MagikoopaSpellAI_OnHit)
    Exec(EnemyNpcHit)
    Return
    End
};

EvtScript EVS_NpcDefeat_Magikoopa_Hitbox = {
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

NpcSettings NpcSettings_Magikoopa_GroundHitbox = {
    .defaultAnim = ANIM_Magikoopa_Still,
    .doAI = &EVS_NpcAI_Magikoopa_Hitbox,
    .onCreate = &EVS_NpcCreate_Magikoopa_GroundHitbox,
    .onHit = &EVS_NpcHit_Magikoopa_Hitbox,
    .onDefeat = &EVS_NpcDefeat_Magikoopa_Hitbox,
};

NpcSettings NpcSettings_Magikoopa_FlyingHitbox = {
    .defaultAnim = ANIM_FlyingMagikoopa_Still,
    .doAI = &EVS_NpcAI_Magikoopa_Hitbox,
    .onCreate = &EVS_NpcCreate_Magikoopa_FlyingHitbox,
    .onHit = &EVS_NpcHit_Magikoopa_Hitbox,
    .onDefeat = &EVS_NpcDefeat_Magikoopa_Hitbox,
};
