#include "lava_piranha.h"
#include "sprite/npc/LavaBud.h"
#include "sprite/npc/PetitPiranha.h"
#include "ld_addrs.h"

static EvtScript EVS_Init;
static EvtScript EVS_Idle;
static EvtScript EVS_TakeTurn;
static EvtScript EVS_HandleEvent;
static EvtScript EVS_PlayAnimForVine;
static EvtScript EVS_ComboHit;
static EvtScript EVS_Hit;
static EvtScript EVS_BurnHit;
static EvtScript EVS_Death;
static EvtScript EVS_Attack_SpitPetit;
static EvtScript EVS_Move_SummonPetit;
static EvtScript EVS_PlayIdleAnimation;

static Formation LeftPetitFormation;
static Formation RightPetitFormation;

enum ActorPartIDs {
    PRT_MAIN        = 1,
    PRT_TARGET      = 2,
};

enum ActorVars {
    AVAR_SummonDelayTurns   = 4,
};

enum ActorParams {
    DMG_PETIT_SPIT      = 4,
};

static s32 unusedArray[64];

#define EVT_LOAD_BUD_ANIM(whichVine, anim) \
    IfEq(whichVine, VINE_1) \
        Call(LoadVineAnim, anim, VINE_1) \
    Else \
        Call(LoadVineAnim, anim, VINE_2) \
    EndIf

static s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaBud_Idle,
    STATUS_KEY_STOP,      ANIM_LavaBud_Still,
    STATUS_END,
};

s32 BudFieryAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaBud_IdleFiery,
    STATUS_KEY_STOP,      ANIM_LavaBud_Still,
    STATUS_END,
};

static s32 StunnedAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaBud_Dead,
    STATUS_KEY_STOP,      ANIM_LavaBud_Dead,
    STATUS_END,
};

static s32 DefenseTable[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,    0,
    ELEMENT_ICE,      0,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

s32 BudFieryDefense[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,   -2,
    ELEMENT_ICE,     -2,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

static s32 StunnedDefense[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,    0,
    ELEMENT_ICE,      0,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

static s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,              75,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,              30,
    STATUS_KEY_UNUSED,              0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,           75,
    STATUS_KEY_SHRINK,              0,
    STATUS_KEY_STOP,               60,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,         -1,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,         -1,
    STATUS_TURN_MOD_UNUSED,         0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,      -1,
    STATUS_TURN_MOD_SHRINK,        -1,
    STATUS_TURN_MOD_STOP,          -2,
    STATUS_END,
};

static ActorPartBlueprint ActorParts[] = {
    {
        .flags = ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -8 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_IGNORE_BELOW_CHECK | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_TARGET,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = nullptr,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -8 },
    },
};

ActorBlueprint BudBlueprint = {
    .flags = 0,
    .type = ACTOR_TYPE_LAVA_BUD_PHASE_1,
    .level = ACTOR_LEVEL_LAVA_BUD_PHASE_1,
    .maxHP = 8,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 10, -42 },
    .statusIconOffset = { -18, 10 },
    .statusTextOffset = { 0, 0 },
};

static EvtScript EVS_Init = {
    UseArray(unusedArray)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_STUNNED)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
    Call(SetActorVar, ACTOR_SELF, AVAR_Bud_PetitCount, 0)
    Call(SetActorVar, ACTOR_SELF, AVAR_SummonDelayTurns, 0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, 0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, 0)
    Call(RandInt, 20, LVar0)
    Add(LVar0, 15)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaBud_Idle)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaBud_Hurt)
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Return
    End
};

static EvtScript EVS_Idle = {
    Label(0)
        Call(GetActorHP, ACTOR_BOSS, LVar0)
        IfEq(LVar0, 0)
            Goto(99)
        EndIf
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, ACTOR_FLAG_NO_DMG_APPLY)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfNe(LVar0, PIRANHA_STATE_DEAD)
            Goto(99)
        EndIf
        Label(10)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        IfNe(LVar0, 0)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchMode, LVar0)
        Add(LVar0, 1)
        IfGe(LVar0, 3)
            Set(LVar0, 0)
        EndIf
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchMode, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(RandInt, 50, LVar0)
                Add(LVar0, 25)
            CaseEq(1)
                Call(RandInt, 40, LVar0)
                Add(LVar0, 20)
            CaseDefault
                Call(RandInt, 3, LVar0)
                Add(LVar0, 3)
        EndSwitch
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_TWITCH)
        ExecWait(EVS_PlayAnimForVine)
        Label(99)
        Wait(1)
        Goto(0)
    Return
    End
};

static EvtScript EVS_PlayAnimForVine = {
    IfEq(LVar0, VINE_1)
        Call(PlayModelAnimation, LVar0, VINE_1_BASE)
    Else
        Call(PlayModelAnimation, LVar0, VINE_2_BASE)
    EndIf
    Return
    End
};

static EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    Call(SetAnimatorFlags, LVar0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(EVENT_BEGIN_FIRST_STRIKE)
        CaseEq(EVENT_HIT_COMBO)
            ExecWait(EVS_ComboHit)
        CaseEq(EVENT_HIT)
            ExecWait(EVS_Hit)
        CaseEq(EVENT_BURN_HIT)
            IfFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_BurnHit)
            Else
                ExecWait(EVS_Hit)
            EndIf
        CaseEq(EVENT_BURN_DEATH)
            ExecWait(EVS_Death)
        CaseEq(EVENT_SPIN_SMASH_HIT)
            ExecWait(EVS_Hit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            ExecWait(EVS_Death)
        CaseEq(EVENT_SHOCK_HIT)
            SetConst(LVar0, PRT_MAIN)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar1)
            ExecWait(EVS_Enemy_ShockHit)
        CaseEq(EVENT_SHOCK_DEATH)
            ExecWait(EVS_Enemy_ShockHit)
        CaseEq(EVENT_ZERO_DAMAGE)
            IfNotFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_ComboHit)
            EndIf
        CaseEq(EVENT_IMMUNE)
            IfNotFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_Hit)
            EndIf
        CaseEq(EVENT_AIR_LIFT_FAILED)
        CaseEq(EVENT_SPIKE_TAUNT)
        CaseEq(EVENT_DEATH)
            ExecWait(EVS_Death)
        CaseEq(EVENT_END_FIRST_STRIKE)
        CaseEq(EVENT_RECOVER_STATUS)
            Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
            Call(SetAnimatorFlags, LVar0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
        CaseEq(EVENT_30)
            SetConst(LVar0, PRT_MAIN)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar1)
            ExecWait(EVS_Enemy_Hit)
            Wait(1000)
        CaseDefault
    EndSwitch
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, STATUS_FLAG_STOP)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        Call(SetAnimatorFlags, LVar0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 1)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static EvtScript EVS_BurnHit = {
    Thread
        Wait(1)
        Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar0)
        IfFalse(LVar0)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar2)
        IfEq(LVar2, PIRANHA_STATE_FIERY)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        IfEq(LVar0, VINE_1)
            Set(LVar0, ACTOR_BUD_1)
        Else
            Set(LVar0, ACTOR_BUD_2)
        EndIf
        ExecWait(EVS_Ignite)
        Label(10)
    EndThread
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar0)
    IfTrue(LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_DEAD)
            Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
            EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_RECOVER)
            ExecWait(EVS_PlayAnimForVine)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaBud_Idle)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaBud_Hurt)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(BudFieryAnims))
            Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(BudFieryDefense))
            Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(BudFieryDefense))
            Thread
                Wait(14)
                Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
                ExecWait(EVS_PlayAnimForVine)
            EndThread
        EndIf
    EndIf
    Return
    End
};

static EvtScript EVS_TakeTurn = {
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, ACTOR_FLAG_NO_DMG_APPLY)
        Return
    EndIf
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar0)
    IfFalse(LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_DEAD)
            Return
        EndIf
        ExecWait(EVS_Attack_SpitPetit)
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_SummonDelayTurns, LVar1)
        IfNe(LVar1, 0)
            Sub(LVar1, 1)
            Call(SetActorVar, ACTOR_SELF, AVAR_SummonDelayTurns, LVar1)
            Return
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_FIERY)
            IfNe(LVar1, 0)
                Return
            EndIf
            Call(SetActorVar, ACTOR_SELF, AVAR_SummonDelayTurns, 1)
            ExecWait(EVS_Move_SummonPetit)
        Else
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, LVar0)
            Sub(LVar0, 1)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, LVar0)
            IfLe(LVar0, 0)
                Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
                Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
                IfEq(LVar0, VINE_1)
                    Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
                    Call(SetBattleCamTarget, 40, 30, 0)
                    Call(SetBattleCamDist, 270)
                    Call(SetBattleCamOffsetY, 20)
                    Call(MoveBattleCamOver, 30)
                Else
                    Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
                    Call(SetBattleCamTarget, 110, 35, 0)
                    Call(SetBattleCamDist, 300)
                    Call(SetBattleCamOffsetY, 20)
                    Call(MoveBattleCamOver, 30)
                EndIf
                Wait(30)
                Loop(10)
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_TWITCH)
                    ExecWait(EVS_PlayAnimForVine)
                    Wait(4)
                EndLoop
                Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
                Call(MoveBattleCamOver, 15)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_IdleFiery)
                Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
                IfEq(LVar0, VINE_1)
                    Set(LVar0, ACTOR_BUD_1)
                Else
                    Set(LVar0, ACTOR_BUD_2)
                EndIf
                Call(PlaySoundAtActor, LVar0, SOUND_LAVA_BUD_RECOVER)
                ExecWait(EVS_Ignite)
                Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_RECOVER)
                ExecWait(EVS_PlayAnimForVine)
                Wait(14)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
                ExecWait(EVS_PlayAnimForVine)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            EndIf
        EndIf
    EndIf
    ExecWait(EVS_PlayIdleAnimation)
    Return
    End
};

static EvtScript EVS_PlayIdleAnimation = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar3)
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar3)
    IfEq(LVar3, PIRANHA_STATE_DEAD)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_TWITCH)
        ExecWait(EVS_PlayAnimForVine)
    Else
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
        ExecWait(EVS_PlayAnimForVine)
    EndIf
    Return
    End
};

static EvtScript EVS_Move_SummonPetit = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
    IfEq(LVar0, PIRANHA_STATE_DEAD)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_PetitCount, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(8)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 30)
        Wait(45)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_ATTACK)
    ExecWait(EVS_PlayAnimForVine)
    Thread
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_SpitWindupFiery)
        Wait(34)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_SpitReleaseFiery)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_IdleFiery)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
        ExecWait(EVS_PlayAnimForVine)
    EndThread
    Wait(56)
    IfEq(LVar0, 1)
        Call(SummonEnemy, Ref(LeftPetitFormation), false)
    Else
        Call(SummonEnemy, Ref(RightPetitFormation), false)
    EndIf
    Set(LVar5, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_PetitCount, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, AVAR_Bud_PetitCount, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    IfEq(LVar0, VINE_1)
        Call(SetActorVar, LVar5, AVAR_Petit_Parent, ACTOR_BUD_1)
    Else
        Call(SetActorVar, LVar5, AVAR_Petit_Parent, ACTOR_BUD_2)
    EndIf
    Call(GetPartOffset, ACTOR_SELF, PRT_MAIN, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Sub(LVar1, 15)
    Call(SetActorPos, LVar5, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Sub(LVar1, 15)
    Call(PlaySoundAtActor, LVar5, SOUND_LAVA_BUD_SPIT_PETIT)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar9)
    IfEq(LVar9, VINE_1)
        Call(GetActorPos, LVar5, LVar0, LVar1, LVar2)
        Set(LVar0, -12)
        Set(LVar1, 80)
        Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
        Call(SetHomePos, LVar5, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, LVar5, Float(4.0))
        Call(SetActorJumpGravity, LVar5, Float(1.0))
        Call(FlyToGoal, LVar5, 24, -42, EASING_QUARTIC_OUT)
    Else
        Call(GetActorPos, LVar5, LVar0, LVar1, LVar2)
        Set(LVar0, 18)
        Set(LVar1, 28)
        Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
        Call(SetHomePos, LVar5, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, LVar5, Float(5.0))
        Call(SetActorJumpGravity, LVar5, Float(1.2))
        Call(FlyToGoal, LVar5, 16, -15, EASING_CUBIC_OUT)
    EndIf
    Call(HPBarToHome, LVar5)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
    ExecWait(EVS_PlayAnimForVine)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static Vec3i SummonPos = { 260, 0, 0 };

static Formation LeftPetitFormation = {
    OVL_ACTOR_BY_POS("petit_piranha", SummonPos, 95, -12, 85),
};

static Formation RightPetitFormation = {
    OVL_ACTOR_BY_POS("petit_piranha", SummonPos, 94, 18, 38),
};

static Formation PetitBombFormation = {
    OVL_ACTOR_BY_POS("petit_piranha_bomb", SummonPos, 95),
};

static EvtScript EVS_Death = {
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar0)
    IfTrue(LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_DEAD)
            ExecWait(EVS_Hit)
            Return
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar0)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
        ExecWait(EVS_PlayAnimForVine)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, 2)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(RemoveEffect, LVar0)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
        EndIf
        Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(StunnedAnims))
        Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(StunnedDefense))
        Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(StunnedDefense))
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaBud_Dead)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaBud_Hurt)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_Dead)
        Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, false)
        Call(SetPartEventBits, ACTOR_SELF, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, false)
        Wait(29)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_BUD_WITHER)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUN)
        ExecWait(EVS_PlayAnimForVine)
        Wait(14)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_DEAD)
        Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_Dying, LVarF)
        IfEq(LVarF, 0)
            ExecWait(EVS_PlayIdleAnimation)
        EndIf
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
    IfEq(LVar0, PIRANHA_STATE_STUNNED)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
        ExecWait(EVS_PlayAnimForVine)
        Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(StunnedAnims))
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaBud_Dead)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaBud_Hurt)
        Wait(29)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_BUD_WITHER)
        Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUN)
        ExecWait(EVS_PlayAnimForVine)
        Wait(14)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_DEAD)
        ExecWait(EVS_PlayIdleAnimation)
        Call(SetPartFlagBits, ACTOR_SELF, PRT_TARGET, ACTOR_PART_FLAG_DAMAGE_IMMUNE | ACTOR_PART_FLAG_NO_TARGET, true)
        Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_HEALTH_BAR, true)
    Else
        ExecWait(EVS_Hit)
        Return
    EndIf
    Return
    End
};

static EvtScript EVS_ComboHit = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar1)
    IfFalse(LVar1)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar5)
        IfNe(LVar5, PIRANHA_STATE_DEAD)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Wait(29)
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar5)
        IfEq(LVar5, PIRANHA_STATE_FIERY)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Sub(LVar2, 25)
            Add(LVar3, 2)
            PlayEffect(EFFECT_EMBERS, 0, LVar1, LVar2, LVar3, 40, 50, Float(1.2), 24, 42, Float(0.8), Float(0.6))
            Wait(29)
        EndIf
    EndIf
    Return
    End
};

static EvtScript EVS_Hit = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar5)
    IfFalse(LVar5)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar5)
        IfEq(LVar5, PIRANHA_STATE_STUNNED)
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Wait(29)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar5)
            IfLt(LVar5, 4)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_LIGHT_HIT)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_HEAVY_HIT)
            EndIf
            ExecWait(EVS_PlayAnimForVine)
            Wait(29)
        EndIf
    Else
        IfFlag(LVarE, DAMAGE_TYPE_ICE | DAMAGE_TYPE_WATER)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar3)
            IfEq(LVar3, PIRANHA_STATE_DEAD)
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_LIGHT_HIT)
                Else
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_HEAVY_HIT)
                EndIf
                ExecWait(EVS_PlayAnimForVine)
                Wait(29)
            Else
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
                ExecWait(EVS_PlayAnimForVine)
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, 2)
                Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, LVar0)
                IfNe(LVar0, nullptr)
                    Call(RemoveEffect, LVar0)
                    Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    PlayEffect(EFFECT_COLD_BREATH, 0, LVar0, LVar1, LVar2, Float(2.0), 45)
                EndIf
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(StunnedAnims))
                Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(StunnedDefense))
                Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(StunnedDefense))
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaBud_Dead)
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaBud_Hurt)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_Dead)
                Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, false)
                Call(SetPartEventBits, ACTOR_SELF, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, false)
                Wait(29)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_BUD_WITHER)
                Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
                EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUN)
                ExecWait(EVS_PlayAnimForVine)
                Wait(14)
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_DEAD)
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar3)
            IfEq(LVar3, PIRANHA_STATE_DEAD)
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfEq(LVar5, 0)
                    Return
                EndIf
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_LIGHT_HIT)
                Else
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_STUNNED_HEAVY_HIT)
                EndIf
                ExecWait(EVS_PlayAnimForVine)
                Wait(29)
            Else
                Call(GetLastDamage, ACTOR_SELF, LVar5)
                IfLt(LVar5, 4)
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_LIGHT_HIT)
                Else
                    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_HEAVY_HIT)
                EndIf
                ExecWait(EVS_PlayAnimForVine)
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                Sub(LVar2, 25)
                Add(LVar3, 2)
                PlayEffect(EFFECT_EMBERS, 0, LVar1, LVar2, LVar3, 40, 50, Float(1.2), 24, 42, Float(0.8), Float(0.6))
                Wait(29)
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_Dying, LVarF)
    IfEq(LVarF, 0)
        ExecWait(EVS_PlayIdleAnimation)
    EndIf
    Return
    End
};

static API_CALLABLE(SetPetitFlameSize) {
    Bytecode* args = script->ptrReadPos;
    FlameFXData* data = ((EffectInstance*) evt_get_variable(script, *args++))->data.flame;
    f32 scale = evt_get_float_variable(script, *args++);

    data->scaleH = scale;
    data->scaleW = scale;
    return ApiStatus_DONE2;
}

static EvtScript EVS_Attack_SpitPetit = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Thread
        Wait(8)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar1, 25)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 30)
        Wait(45)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(GetActorVar, ACTOR_SELF, AVAR_Bud_WhichVine, LVar0)
    EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_ATTACK)
    ExecWait(EVS_PlayAnimForVine)
    Thread
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_SpitWindup)
        Wait(39)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_SpitRelease)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaBud_Idle)
        EVT_LOAD_BUD_ANIM(LVar0, VINE_ANIM_BUD_IDLE)
        ExecWait(EVS_PlayAnimForVine)
    EndThread
    Wait(56)
    Call(SummonEnemy, Ref(PetitBombFormation), false)
    Set(LVar5, LVar0)
    Call(GetPartOffset, ACTOR_SELF, PRT_MAIN, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Sub(LVar1, 15)
    Call(SetActorPos, LVar5, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Sub(LVar1, 15)
    Call(SetAnimation, LVar5, 1, ANIM_PetitPiranha_Dive)
    Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, LVar5, Float(6.0))
    Call(SetActorJumpGravity, LVar5, Float(1.8))
    Call(PlaySoundAtActor, LVar5, SOUND_PETIT_PIRANHA_DIVE)
    Call(SetTargetActor, LVar5, ACTOR_PLAYER)
    Call(SetGoalToTarget, LVar5)
    Call(EnemyTestTarget, LVar5, LVar9, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVar9)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Call(SetGoalToTarget, LVar5)
            Call(GetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Set(LVar0, -180)
            Call(SetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, LVar5, Float(13.0))
            Call(SetActorJumpGravity, LVar5, Float(1.8))
            Call(FlyToGoal, LVar5, 0, 0, EASING_LINEAR)
            IfEq(LVar9, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, LVar5, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(RemoveActor, LVar5)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetTargetActor, LVar5, ACTOR_PLAYER)
    Call(SetGoalToTarget, LVar5)
    Call(SetActorSpeed, LVar5, Float(13.0))
    Call(SetActorJumpGravity, LVar5, Float(1.8))
    Call(FlyToGoal, LVar5, 0, 0, EASING_LINEAR)
    Wait(2)
    Call(SetGoalToTarget, LVar5)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar9, DAMAGE_TYPE_FIRE, SUPPRESS_EVENT_ALL, 0, DMG_PETIT_SPIT, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar9)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
        CaseOrEq(HIT_RESULT_10)
            Call(SetPartFlagBits, LVar5, 1, ACTOR_PART_FLAG_INVISIBLE, true)
            Call(SetGoalToTarget, LVar5)
            Call(GetGoalPos, LVar5, LVar0, LVar1, LVar2)
            Set(LVar1, 10)
            Add(LVar2, 2)
            PlayEffect(EFFECT_FLAME, FX_FLAME_SMALL_BLUE, LVar0, LVar1, LVar2, Float(0.3), LVarA)
            Call(MakeLerp, 120, 10, 20, EASING_QUADRATIC_IN)
            Loop(0)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.01))
                Call(SetPetitFlameSize, LVarA, LVar0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Wait(1)
            Call(RemoveEffect, LVarA)
            Call(RemoveActor, LVar5)
            Wait(15)
            IfEq(LVar9, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};
