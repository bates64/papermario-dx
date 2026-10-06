#include "duplighost.h"
#include "sprite/npc/Duplighost.h"

static EvtScript EVS_Init;
static EvtScript EVS_Idle;
static EvtScript EVS_TakeTurn;
static EvtScript EVS_HandleEvent;
static EvtScript EVS_HandlePhase;

enum ActorParams {
    DMG_FLYING_LEAP     = 4,
};

static s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Duplighost_Idle,
    STATUS_KEY_STONE,     ANIM_Duplighost_Still,
    STATUS_KEY_SLEEP,     ANIM_Duplighost_Sleep,
    STATUS_KEY_POISON,    ANIM_Duplighost_Idle,
    STATUS_KEY_STOP,      ANIM_Duplighost_Still,
    STATUS_KEY_STATIC,    ANIM_Duplighost_Idle,
    STATUS_KEY_PARALYZE,  ANIM_Duplighost_Still,
    STATUS_KEY_DIZZY,     ANIM_Duplighost_Dizzy,
    STATUS_KEY_UNUSED,    ANIM_Duplighost_Dizzy,
    STATUS_END,
};

static s32 FlailingAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Duplighost_Hurt,
    STATUS_END,
};

static s32 RunAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Duplighost_Run,
    STATUS_END,
};

static s32 DefenseTable[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

static s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,              60,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,              75,
    STATUS_KEY_UNUSED,              0,
    STATUS_KEY_STATIC,             75,
    STATUS_KEY_PARALYZE,           75,
    STATUS_KEY_SHRINK,             75,
    STATUS_KEY_STOP,               80,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,         -1,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,         -1,
    STATUS_TURN_MOD_UNUSED,         0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       1,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,          -1,
    STATUS_END,
};

static ActorPartBlueprint ActorParts[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 25 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { -2, -10 },
    },
};

OVL_DEF_ACTOR() = {
    .flags = 0,
    .type = ACTOR_TYPE_DUPLIGHOST,
    .level = ACTOR_LEVEL_DUPLIGHOST,
    .maxHP = 15,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 36, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

static EvtScript EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, AVAR_State, AVAL_State_ReadyToCopy)
    Return
    End
};

static EvtScript EVS_HandlePhase = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(PHASE_PLAYER_BEGIN)
        CaseEq(PHASE_ENEMY_BEGIN)
        CaseEq(PHASE_ENEMY_END)
            Call(GetActorVar, ACTOR_SELF, AVAR_State, LVar0)
            IfEq(LVar0, AVAL_State_WaitToTackle)
                Call(SetActorVar, ACTOR_SELF, AVAR_State, AVAL_State_ReadyToTackle)
            EndIf
    EndSwitch
    Return
    End
};

static EvtScript EVS_Idle = {
    Return
    End
};

static EvtScript EVS_ReturnHome = {
    SetConst(LVar0, PRT_MAIN)
    SetConst(LVar1, ANIM_Duplighost_Run)
    ExecWait(EVS_Enemy_ReturnHome)
    Return
    End
};

static EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_BurnHurt)
            SetConst(LVar2, -1)
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_BurnHurt)
            SetConst(LVar2, -1)
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_BurnHurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SHOCK_HIT)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Knockback)
            ExecWait(EVS_ReturnHome)
        CaseEq(EVENT_SHOCK_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
        CaseOrEq(EVENT_AIR_LIFT_FAILED)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Idle)
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Wait(10)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Idle)
            ExecWait(EVS_Enemy_Recover)
        CaseEq(EVENT_SCARE_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Run)
            SetConst(LVar2, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_ScareAway)
            Return
        CaseEq(EVENT_BEGIN_AIR_LIFT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Run)
            ExecWait(EVS_Enemy_AirLift)
        CaseEq(EVENT_BLOW_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Duplighost_Hurt)
            ExecWait(EVS_Enemy_BlowAway)
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static EvtScript EVS_Attack_FlyingTackle = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(UseBattleCamPreset, BTL_CAM_ENEMY_APPROACH)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Crouch)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP, SOUND_DUPLIGHOST_LEAP, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Leap)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -100, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.3))
            Call(JumpToGoal, ACTOR_SELF, 17, false, true, false)
            IfEq(LVarA, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Idle)
            Call(ResetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP)
            Wait(15)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
            ExecWait(EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Leap)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, STATUS_FLAG_SHRINK)
        Call(AddGoalPos, ACTOR_SELF, Float(4.0), Float(-6.0), 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 10, -15, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.3))
    Call(JumpToGoal, ACTOR_SELF, 12, false, true, false)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, DMG_FLYING_LEAP, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(ResetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Land)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, false, true, false)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, false, true, false)
            Wait(10)
            Call(YieldTurn)
            ExecWait(EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_Copy_OnDeath = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Copy_ParentActorID, LVar0)
    Call(RemoveActor, LVar0)
    Return
    End
};

EvtScript EVS_Copy_OnHitElectric = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(30)
    Call(GetActorVar, ACTOR_SELF, AVAR_Copy_ParentActorID, LVarA)
    Call(UseIdleAnimation, LVarA, false)
    Call(HideHealthBar, LVarA)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMOKE_BURST)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Call(SetEnemyHP, LVarA, LVarB)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetActorPos, LVarA, LVarB, LVarC, LVarD)
    Call(SetPartFlagBits, LVarA, 1, ACTOR_PART_FLAG_PRIMARY_TARGET, true)
    Call(SetPartFlagBits, LVarA, 1, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET, false)
    Call(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW | ACTOR_FLAG_NO_DMG_APPLY, false)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, true)
    Call(SetActorVar, LVarA, AVAR_State, AVAL_State_ReadyToTackle)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, ACTOR_PART_FLAG_INVISIBLE, true)
    Call(SetIdleAnimations, LVarA, PRT_MAIN, Ref(FlailingAnims))
    Call(SetAnimation, LVarA, 1, ANIM_Duplighost_Hurt)
    Wait(30)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(GetActorPos, LVarA, LVarB, LVarC, LVarD)
    IfGt(LVarC, 0)
        Set(LVarC, 0)
        Call(SetActorJumpGravity, LVarA, Float(0.5))
        Call(SetActorSounds, LVarA, ACTOR_SOUND_JUMP, SOUND_FALL_QUICK, 0)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 15, false, true, false)
        Call(ResetActorSounds, LVarA, ACTOR_SOUND_JUMP)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 10, false, true, false)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 5, false, true, false)
    EndIf
    Call(ForceHomePos, LVarA, LVarB, LVarC, LVarD)
    Call(HPBarToHome, LVarA)
    Call(SetIdleAnimations, LVarA, PRT_MAIN, Ref(DefaultAnims))
    Call(SetAnimation, LVarA, 1, ANIM_Duplighost_Idle)
    Call(SetActorPos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(ForceHomePos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(HPBarToHome, ACTOR_SELF)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};

EvtScript EVS_Copy_OnShockHit = {
    Set(LVar9, LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Add(LVar2, 10)
    Add(LVar3, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
    ExecWait(EVS_Enemy_ShockHit)
    Call(GetActorVar, ACTOR_SELF, AVAR_Copy_ParentActorID, LVarA)
    Call(UseIdleAnimation, LVarA, false)
    Call(HideHealthBar, LVarA)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMOKE_BURST)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Call(SetEnemyHP, LVarA, LVarB)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetActorPos, LVarA, LVarB, LVarC, LVarD)
    Call(SetPartFlagBits, LVarA, 1, ACTOR_PART_FLAG_PRIMARY_TARGET, true)
    Call(SetPartFlagBits, LVarA, 1, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET, false)
    Call(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW | ACTOR_FLAG_NO_DMG_APPLY, false)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, true)
    Call(SetActorVar, LVarA, AVAR_State, AVAL_State_WaitToTackle)
    Call(SetPartFlagBits, ACTOR_SELF, LVar9, ACTOR_PART_FLAG_INVISIBLE, true)
    Call(SetIdleAnimations, LVarA, PRT_MAIN, Ref(FlailingAnims))
    Call(SetAnimation, LVarA, 1, ANIM_Duplighost_Hurt)
    Wait(15)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(SetActorJumpGravity, LVarA, Float(0.5))
    Call(GetActorPos, LVarA, LVarB, LVarC, LVarD)
    Add(LVarB, 30)
    Set(LVarC, 0)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 15, false, true, false)
    Add(LVarB, 20)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 10, false, true, false)
    Add(LVarB, 10)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 5, false, true, false)
    Wait(20)
    Call(AddActorDecoration, LVarA, 1, 0, ACTOR_DECORATION_SWEAT)
    Call(SetActorYaw, LVarA, 180)
    Call(SetIdleAnimations, LVarA, PRT_MAIN, Ref(RunAnims))
    Call(SetAnimation, LVarA, 1, ANIM_Duplighost_Run)
    Call(SetActorSpeed, LVarA, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetGoalPos, LVarA, LVarB, 0, LVarD)
    Call(RunToGoal, LVarA, 0, false)
    Call(SetAnimation, LVarA, 1, ANIM_Duplighost_Idle)
    Call(SetActorYaw, LVarA, 0)
    Call(RemoveActorDecoration, LVarA, 1, 0)
    Call(SetIdleAnimations, LVarA, PRT_MAIN, Ref(DefaultAnims))
    Call(ForceHomePos, LVarA, LVarB, 0, LVarD)
    Call(HPBarToHome, LVarA)
    Call(SetActorPos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(ForceHomePos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(HPBarToHome, ACTOR_SELF)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};

EvtScript EVS_Copy_OnShockDeath = {
    Call(HideHealthBar, ACTOR_SELF)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Add(LVar1, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.1))
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, false, false, false)
    Set(LVar0, LVarA)
    Set(LVar1, LVarB)
    ExecWait(EVS_Enemy_ShockHit)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, LVarC, 0)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, -48)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.4))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, false, true, false)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, false, true, false)
    Add(LVar0, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 4, false, true, false)
    Return
    End
};

Vec3i SummonPos = { NPC_DISPOSE_LOCATION };

#include "common/UnkBackgroundFunc3.inc.c"
#include "common/SetBackgroundAlpha.inc.c"

static API_CALLABLE(GetPartnerAndLevel) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gPlayerData.curPartner);
    evt_set_variable(script, *args++, gPlayerData.partners[gPlayerData.curPartner].level);
    return ApiStatus_DONE2;
}

static API_CALLABLE(AdjustFormationPriority) {
    s32 partnerID = evt_get_variable(script, *script->ptrReadPos);
    Actor* actor = get_actor(script->owner1.actorID);
    FormationRow* formation = nullptr;

    switch (partnerID) {
        case PARTNER_GOOMBARIO:
            formation = GoombarioFormation;
            break;
        case PARTNER_KOOPER:
            formation = KooperFormation;
            break;
        case PARTNER_BOMBETTE:
            formation = BombetteFormation;
            break;
        case PARTNER_PARAKARRY:
            formation = ParakarryFormation;
            break;
        case PARTNER_BOW:
            formation = BowFormation;
            break;
        case PARTNER_WATT:
            formation = WattFormation;
            break;
        case PARTNER_SUSHIE:
            formation = SushieFormation;
            break;
        case PARTNER_LAKILESTER:
            formation = LakilesterFormation;
            break;
    }

    ASSERT_MSG(formation != nullptr, "Unsupported Duplighost partner %ld", partnerID);
    formation->priority = actor->turnPriority;

    return ApiStatus_DONE2;
}

static EvtScript EVS_CopyPartner = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseBattleCamPreset, BTL_CAM_ACTOR)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_GHOST_TRANSFORM)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Duplighost_Threaten)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, STATUS_FLAG_SHRINK)
        Add(LVar1, 8)
        SetF(LVar3, Float(0.4))
    Else
        Add(LVar1, 20)
        SetF(LVar3, Float(1.0))
    EndIf
    PlayEffect(EFFECT_GATHER_ENERGY_PINK, 1, LVar0, LVar1, LVar2, LVar3, 40)
    Call(UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 20, EASING_LINEAR)
    Label(0)
    Call(UpdateLerp)
    Call(SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Wait(10)
    Call(GetPartnerAndLevel, LVar5, LVar6)
    Call(AdjustFormationPriority, LVar5)
    Switch(LVar5)
        CaseEq(PARTNER_GOOMBARIO)
            Call(SummonEnemy, Ref(GoombarioFormation), false)
        CaseEq(PARTNER_KOOPER)
            Call(SummonEnemy, Ref(KooperFormation), false)
        CaseEq(PARTNER_BOMBETTE)
            Call(SummonEnemy, Ref(BombetteFormation), false)
        CaseEq(PARTNER_PARAKARRY)
            Call(SummonEnemy, Ref(ParakarryFormation), false)
        CaseEq(PARTNER_BOW)
            Call(SummonEnemy, Ref(BowFormation), false)
        CaseEq(PARTNER_WATT)
            Call(SummonEnemy, Ref(WattFormation), false)
        CaseEq(PARTNER_SUSHIE)
            Call(SummonEnemy, Ref(SushieFormation), false)
        CaseEq(PARTNER_LAKILESTER)
            Call(SummonEnemy, Ref(LakilesterFormation), false)
    EndSwitch
    Set(LVarA, LVar0)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(SetBattleVar, BTL_VAR_LastCopiedPartner, LVar5)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SMOKE_BURST)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET, true)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_PRIMARY_TARGET, false)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW | ACTOR_FLAG_NO_DMG_APPLY, true)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVarA, LVar0)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetOwnerID, LVar0)
    Call(SetActorVar, LVarA, AVAR_Copy_ParentActorID, LVar0)
    Call(SetActorVar, LVarA, AVAR_Copy_PartnerLevel, LVar6)
    Wait(20)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(MakeLerp, 200, 0, 20, EASING_LINEAR)
        Label(1)
        Call(UpdateLerp)
        Call(SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(SetActorSounds, LVarA, ACTOR_SOUND_JUMP, SOUND_NONE, 0)
    Switch(LVar5)
        CaseEq(8)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.01))
            Call(SetGoalPos, LVarA, LVar0, 10, LVar2)
            Call(JumpToGoal, LVarA, 10, false, false, false)
            Wait(10)
        CaseOrEq(6)
        CaseOrEq(9)
        CaseOrEq(4)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.01))
            Call(SetGoalPos, LVarA, LVar0, 30, LVar2)
            Call(JumpToGoal, LVarA, 20, false, false, false)
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarA)
    Call(ResetActorSounds, LVarA, ACTOR_SOUND_JUMP)
    Wait(20)
    Call(SetActorPos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(ForceHomePos, ACTOR_SELF, NPC_DISPOSE_LOCATION)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, AVAR_State, AVAL_State_CopiedPartner)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static EvtScript EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, AVAR_State, LVar0)
    Switch(LVar0)
        CaseEq(AVAL_State_ReadyToCopy)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 600)
                Call(GetBattleVar, BTL_VAR_DuplighostCopyFlags, LVar0)
                IfNotFlag(LVar0, BTL_VAL_Duplighost_HasCopied)
                    // first time partner is copied, set battle flag and proceed
                    Call(GetBattleVar, BTL_VAR_DuplighostCopyFlags, LVar0)
                    BitwiseOrConst(LVar0, BTL_VAL_Duplighost_HasCopied)
                    Call(SetBattleVar, BTL_VAR_DuplighostCopyFlags, LVar0)
                    ExecWait(EVS_CopyPartner)
                Else
                    // partner has been copied before, try to avoid copying the same one
                    Call(GetBattleVar, BTL_VAR_LastCopiedPartner, LVar0)
                    Call(GetPartnerAndLevel, LVar1, LVar2)
                    IfEq(LVar0, LVar1)
                        ExecWait(EVS_CopyPartner)
                    Else
                        ExecWait(EVS_Attack_FlyingTackle)
                    EndIf
                EndIf
            Else
                ExecWait(EVS_Attack_FlyingTackle)
            EndIf
        CaseEq(AVAL_State_CopiedPartner)
            // do nothing, currently in disguise
        CaseEq(AVAL_State_ReadyToTackle)
            ExecWait(EVS_Attack_FlyingTackle)
        CaseEq(AVAL_State_WaitToTackle)
    EndSwitch
    Return
    End
};
