#pragma once
#include "wander.h"

#include "world/common/ai/FlyingMagikoopaAI.inc.c"

MobileAISettings N(AISettings_FlyingMagikoopa_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 20.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 20.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_FlyingMagikoopa_Wander) = {
    Call(N(FlyingMagikoopaAI_Main), Ref(N(AISettings_FlyingMagikoopa_Wander)))
    Return
    End
};

EvtScript N(EVS_NpcDefeat_FlyingMagikoopa) = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(OnPlayerFled, false)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

NpcSettings N(NpcSettings_FlyingMagikoopa_Wander) = {
    .height = 33,
    .radius = 32,
    .level = ACTOR_LEVEL_FLYING_MAGIKOOPA,
    .doAI = &N(EVS_NpcAI_FlyingMagikoopa_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &N(EVS_NpcDefeat_FlyingMagikoopa),
};

AnimID N(LimitAnims_FlyingMagikoopa)[] = {
    ANIM_FlyingMagikoopa_Still,
    ANIM_FlyingMagikoopa_Idle,
    ANIM_FlyingMagikoopa_Idle,
    ANIM_FlyingMagikoopa_Idle,
    ANIM_FlyingMagikoopa_Shout,
    ANIM_FlyingMagikoopa_CastSpell,
    ANIM_FlyingMagikoopa_Hurt,
    ANIM_LIST_END
};

EvtScript N(EVS_NpcCreate_FlyingMagikoopa_AltHitbox) = {
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_Y, 10)
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_R, 40)
    Return
    End
};

EvtScript N(EVS_NpcCreate_FlyingMagikoopa_Hitbox) = {
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_Y, 0)
    Call(SetSelfVar, AI_VAR_SPELL_SPAWN_R, 55)
    Return
    End
};

EvtScript N(EVS_NpcAI_FlyingMagikoopa_Hitbox) = {
    Call(N(MagikoopaSpellAI_Main))
    Return
    End
};

EvtScript N(EVS_NpcHit_FlyingMagikoopa_Hitbox) = {
    Call(N(MagikoopaSpellAI_OnHitInit))
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(N(MagikoopaSpellAI_OnHit))
    Exec(EnemyNpcHit)
    Return
    End
};

EvtScript N(EVS_NpcDefeat_FlyingMagikoopa_Hitbox) = {
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

NpcSettings N(NpcSettings_FlyingMagikoopa_AltHitbox) = {
    .defaultAnim = ANIM_Magikoopa_Still,
    .doAI = &N(EVS_NpcAI_FlyingMagikoopa_Hitbox),
    .onCreate = &N(EVS_NpcCreate_FlyingMagikoopa_AltHitbox),
    .onHit = &N(EVS_NpcHit_FlyingMagikoopa_Hitbox),
    .onDefeat = &N(EVS_NpcDefeat_FlyingMagikoopa_Hitbox),
};

NpcSettings N(NpcSettings_FlyingMagikoopa_Hitbox) = {
    .defaultAnim = ANIM_FlyingMagikoopa_Still,
    .doAI = &N(EVS_NpcAI_FlyingMagikoopa_Hitbox),
    .onCreate = &N(EVS_NpcCreate_FlyingMagikoopa_Hitbox),
    .onHit = &N(EVS_NpcHit_FlyingMagikoopa_Hitbox),
    .onDefeat = &N(EVS_NpcDefeat_FlyingMagikoopa_Hitbox),
};
