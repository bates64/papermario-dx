#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/JrTroopa.h"
#include "sprite/npc/ParaJrTroopa.h"
#include "sprite/npc/MageJrTroopa.h"

#define NAMESPACE A(jr_troopa)

PlayerData* playerData = &gPlayerData;
extern EvtScript N(EVS_Init);
extern s32 N(MageAnims)[];
extern s32 N(FlyingAnims)[];
extern s32 N(BaseAnims)[];
extern s32 N(DefeatedAnims)[];
extern s32 N(BaseDefeatedAnims)[];
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_HandlePhase);
extern EvtScript N(EVS_OnDeath);
extern EvtScript N(EVS_GetFormAnims);
extern EvtScript N(EVS_Move_Charge);
extern EvtScript N(EVS_Attack_Slam);
extern EvtScript N(EVS_Spark_Fly_Away);
extern EvtScript N(EVS_Lose_Flying_Mode);
extern EvtScript N(EVS_DeathExplode);


enum N(ActorPartIDs) {
    PRT_MAGE            = 1,
    PRT_FLYING          = 2,
    PRT_BASE            = 3,
};

enum N(ActorVars) {
    AVAR_FORM                           = 0,
    AVAR_FIRST_TIME_TALKING             = 1,
    AVAR_TURNS_UNTIL_SECOND_PHASE       = 2,
    AVAR_TROOPA_DAMAGE                  = 3,
    AVAR_TURNS_UNTIL_SPARK_FLY_AWAY     = 4,
    AVAR_TROOPA_STATE                   = 5,
};

enum N(ActorValues) {
    AVAL_FORM_BASE          = 1,
    AVAL_FORM_FLYING        = 2,
    AVAL_FORM_MAGE          = 3,
};

enum N(ActorParams) {
    DMG_SCARE               = 3,
    DMG_FIREBALL            = 4,
    DMG_LIGHTNING           = 5,
    DMG_FAKEOUT_SCARE_A     = 4,
    DMG_FAKEOUT_SCARE_B     = 2,
    DMG_BOOSTED_LIGHTNING   = 8,
};

enum {
    FORM_ANIM_HURT      = 0,
    FORM_ANIM_BURN      = 1,
    FORM_ANIM_FLAIL     = 2,
    FORM_ANIM_TALK      = 3,
    FORM_ANIM_RETURN    = 4,
    FORM_ANIM_IMMUNE    = 5,
};

s32 N(BaseAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_JrTroopa_Idle,
    STATUS_KEY_SLEEP,     ANIM_JrTroopa_Sleep,
    STATUS_KEY_STONE,     ANIM_JrTroopa_Still,
    STATUS_KEY_STOP,      ANIM_JrTroopa_Still,
    STATUS_KEY_PARALYZE,  ANIM_JrTroopa_Still,
    STATUS_KEY_DIZZY,     ANIM_JrTroopa_Dizzy,
    STATUS_END,
};

s32 N(FlyingAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_ParaJrTroopa_Idle,
    STATUS_KEY_SLEEP,     ANIM_ParaJrTroopa_Sleep,
    STATUS_KEY_STONE,     ANIM_ParaJrTroopa_Still,
    STATUS_KEY_STOP,      ANIM_ParaJrTroopa_Still,
    STATUS_KEY_PARALYZE,  ANIM_ParaJrTroopa_Still,
    STATUS_KEY_DIZZY,     ANIM_ParaJrTroopa_Dizzy,
    STATUS_END,
};

s32 N(MageAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_MageJrTroopa_Idle,
    STATUS_KEY_SLEEP,     ANIM_MageJrTroopa_Sleep,
    STATUS_KEY_STONE,     ANIM_MageJrTroopa_Still,
    STATUS_KEY_STOP,      ANIM_MageJrTroopa_Still,
    STATUS_KEY_PARALYZE,  ANIM_MageJrTroopa_Still,
    STATUS_KEY_DIZZY,     ANIM_MageJrTroopa_Dizzy,
    STATUS_END,
};

s32 N(DefeatedAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_JrTroopa_Defeated,
    STATUS_END,
};

s32 N(BaseDefeatedAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_JrTroopa_Defeated,
    STATUS_END,
};

s32 N(DefenseTable)[] = {
    ELEMENT_NORMAL,     0,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               100,
    STATUS_KEY_POISON,              100,
    STATUS_KEY_FROZEN,              100,
    STATUS_KEY_DIZZY,               100,
    STATUS_KEY_FEAR,                100,
    STATUS_KEY_STATIC,              100,
    STATUS_KEY_PARALYZE,            100,
    STATUS_KEY_SHRINK,              100,
    STATUS_KEY_STOP,                100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_FEAR,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

ActorPartBlueprint N(ActorParts)[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAGE,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = N(MageAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_FLYING,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 32 },
        .opacity = 255,
        .idleAnimations = N(FlyingAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_BASE,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = N(BaseAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = 0,
    .type = ACTOR_TYPE_JR_TROOPA_1,
    .level = ACTOR_LEVEL_JR_TROOPA_1,
    .maxHP = 10,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init),
    .statusTable = N(StatusTable),
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 30 },
    .statusTextOffset = { 10, 20 },
};

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(BindHandlePhase, ACTOR_SELF, Ref(N(EVS_HandlePhase)))
    // Create Spark NPC
    // CreateNpc(0, NPC_ANIM_spark_normal_idle_nb)
    // Call(SetNpcYaw, 0, 90)
    // Call(SetNpcPos, 0, -129, 16, -11)
    // Call(EnableNpcShadow, 0, 1)
    // Start of ActorVars
    Call(SetActorVar, ACTOR_SELF, AVAR_FORM, AVAL_FORM_MAGE) // Form
    Call(SetActorVar, ACTOR_SELF, AVAR_FIRST_TIME_TALKING, 0) // First time talking
    Call(SetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SECOND_PHASE, 1) // Turns until second phase
    Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_DAMAGE, 1) // Jr Troopa's damage
    Call(SetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SPARK_FLY_AWAY, 1) // Turns until Spark flies away
    Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, 0) // Jr Troopa's state: 0 = Mage, 1 = Flying, 2 = Mage(weak)
    Return
    End
};

EvtScript N(EVS_Idle) = {
    Return
    End
};

EvtScript N(EVS_HandleEvent) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, FALSE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            Set(LVar1, FORM_ANIM_HURT)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            Set(LVar1, FORM_ANIM_BURN)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            Set(LVar1, FORM_ANIM_BURN)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_BurnHit)
            Wait(5)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            Set(LVar1, FORM_ANIM_HURT)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            Set(LVar1, FORM_ANIM_HURT)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_SpinSmashHit)
            Wait(5)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
        CaseOrEq(EVENT_AIR_LIFT_FAILED)
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            Set(LVar1, FORM_ANIM_HURT)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(EVS_Enemy_Hit)
            Wait(10)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseEq(EVENT_END_FIRST_STRIKE)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAGE, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, PRT_MAGE, ANIM_MageJrTroopa_Run)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAGE, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAGE)
            SetConst(LVar1, ANIM_MageJrTroopa_Idle)
            ExecWait(EVS_Enemy_Recover)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, TRUE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_GetFormAnims) = {
    Call(GetActorVar, ACTOR_SELF, AVAR_FORM, LVar0)
    Switch(LVar1)
        CaseEq(FORM_ANIM_HURT)
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_Hurt)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_Hurt)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_Hurt)
            EndSwitch
        CaseEq(FORM_ANIM_BURN)
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_BurnHurt)
                    Set(LVar2, ANIM_ParaJrTroopa_BurnStill)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_BurnHurt)
                    Set(LVar2, ANIM_MageJrTroopa_BurnStill)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_BurnHurt)
                    Set(LVar2, ANIM_JrTroopa_BurnStill)
            EndSwitch
        CaseEq(FORM_ANIM_FLAIL)
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_Flail)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_Flail)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_Flail)
            EndSwitch
        CaseEq(FORM_ANIM_TALK)
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_Talk)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_Talk)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_Talk)
            EndSwitch
        CaseEq(FORM_ANIM_RETURN)
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_FlyFast)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_Run)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_Run)
            EndSwitch
        CaseDefault
            Switch(LVar0)
                CaseEq(AVAL_FORM_FLYING)
                    Set(LVar1, ANIM_ParaJrTroopa_Idle)
                CaseEq(AVAL_FORM_MAGE)
                    Set(LVar1, ANIM_MageJrTroopa_Idle)
                CaseDefault
                    Set(LVar1, ANIM_JrTroopa_Idle)
            EndSwitch
    EndSwitch
    Return
    End
};

EvtScript N(EVS_OnDeath) = {
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Flail)
    // Call(ActorSpeak, MSG_ID, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Flail, ANIM_JrTroopa_Flail)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, 0)
    Call(SetBattleCamZoom, 260)
    Call(SetBattleCamOffsetZ, 30)
    Call(MoveBattleCamOver, 20)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    // Call(ActorSpeak, MSG_ID, ACTOR_SELF, PRT_MAGE, ANIM_JrTroopa_, ANIM_JrTroopa_Dizzy)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    SetConst(LVar0, PRT_MAGE)
    SetConst(LVar1, ANIM_JrTroopa_Panic)
    Set(LVar2, EXEC_DEATH_NO_SPINNING)
    Return
    End
};

EvtScript N(EVS_JrTroopa_BaseDeath) = {
    Set(LVarA, LVar0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(SetAnimation, ACTOR_SELF, LVarA, LVar1)
    Wait(10)
    Call(GetDamageSource, LVar5)
    Switch(LVar5)
        CaseOrEq(DMG_SRC_NEXT_SLAP_LEFT)
        CaseOrEq(DMG_SRC_NEXT_FAN_SMACK_LEFT)
        CaseOrEq(DMG_SRC_LAST_SLAP_LEFT)
        CaseOrEq(DMG_SRC_LAST_FAN_SMACK_LEFT)
        CaseOrEq(DMG_SRC_NEXT_SLAP_RIGHT)
        CaseOrEq(DMG_SRC_NEXT_FAN_SMACK_RIGHT)
        CaseOrEq(DMG_SRC_LAST_SLAP_RIGHT)
        CaseOrEq(DMG_SRC_LAST_FAN_SMACK_RIGHT)
        CaseOrEq(DMG_SRC_SPIN_SMASH)
        EndCaseGroup
        CaseDefault
            Set(LVar2, 0)
            Loop(24)
                Call(SetActorYaw, ACTOR_SELF, LVar2)
                Add(LVar2, 30)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
    EndSwitch
    Label(0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Add(LVar2, 10)
    PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
    Call(PlaySound, SOUND_ACTOR_DEATH)
    Call(DropStarPoints, ACTOR_SELF)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_14)
    Call(SetBattleCamZoom, 260)
    Call(SetBattleCamOffsetZ, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_KNOCKOUT_CHIRPING)
    Call(SetAnimation, ACTOR_SELF, LVarA, ANIM_JrTroopa_Collapse)
    Wait(12)
    Call(SetAnimation, ACTOR_SELF, LVarA, ANIM_JrTroopa_Defeated)
    Call(SetIdleAnimations, ACTOR_SELF, LVarA, Ref(N(BaseDefeatedAnims)))
    Wait(60)
    Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_DMG_APPLY, TRUE)
    Return
    End
};

EvtScript N(EVS_JrTroopa_Death) = {
    Call(GetActorVar, ACTOR_SELF, AVAR_FORM, LVar0)
    Switch(LVar0)
        CaseEq(AVAL_FORM_FLYING)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            IfEq(LVar1, 0)
                Goto(0)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_FALL_QUICK)
            Call(HideHealthBar, ACTOR_SELF)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2))
            Call(FallToGoal, ACTOR_SELF, 10)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.8))
            Call(JumpToGoal, ACTOR_SELF, 8, FALSE, TRUE, FALSE)
            Call(HPBarToCurrent, ACTOR_SELF)
            Call(ShowHealthBar, ACTOR_SELF)
            Label(0)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Add(LVar2, 10)
                Loop(3)
                    PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                    Wait(3)
                EndLoop
            EndThread
            Call(SetPartFlagBits, ACTOR_SELF, PRT_FLYING, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
            Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_DefeatedBegin)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(15)
            Call(PlaySound, SOUND_ACTOR_DEATH)
            Call(DropStarPoints, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, BTL_CAM_PRESET_14)
            Call(SetBattleCamZoom, 260)
            Call(SetBattleCamOffsetZ, 15)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 30)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_KNOCKOUT_CHIRPING)
            Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Defeated)
            Wait(60)
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_DMG_APPLY, TRUE)
            Return
        CaseEq(AVAL_FORM_MAGE)
            Call(HideHealthBar, ACTOR_SELF)
            Call(UseIdleAnimation, ACTOR_SELF, FALSE)
            Call(GetDamageSource, LVar5)
            Switch(LVar5)
                CaseOrEq(DMG_SRC_NEXT_SLAP_LEFT)
                CaseOrEq(DMG_SRC_NEXT_FAN_SMACK_LEFT)
                CaseOrEq(DMG_SRC_LAST_SLAP_LEFT)
                CaseOrEq(DMG_SRC_LAST_FAN_SMACK_LEFT)
                CaseOrEq(DMG_SRC_NEXT_SLAP_RIGHT)
                CaseOrEq(DMG_SRC_NEXT_FAN_SMACK_RIGHT)
                CaseOrEq(DMG_SRC_LAST_SLAP_RIGHT)
                CaseOrEq(DMG_SRC_LAST_FAN_SMACK_RIGHT)
                CaseOrEq(DMG_SRC_SPIN_SMASH)
                EndCaseGroup
                CaseDefault
                    Set(LVar2, 0)
                    Loop(24)
                        Call(SetActorYaw, ACTOR_SELF, LVar2)
                        Add(LVar2, 30)
                        Wait(1)
                    EndLoop
                    Call(SetActorYaw, ACTOR_SELF, 0)
            EndSwitch
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Add(LVar2, 10)
                Loop(3)
                    PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                    Wait(3)
                EndLoop
            EndThread
            Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
            Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_DefeatedBegin)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(15)
            Call(PlaySound, SOUND_ACTOR_DEATH)
            Call(DropStarPoints, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, BTL_CAM_PRESET_14)
            Call(SetBattleCamZoom, 260)
            Call(SetBattleCamOffsetZ, 15)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 30)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_KNOCKOUT_CHIRPING)
            Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Defeated)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_BASE, Ref(N(DefeatedAnims)))
            Wait(60)
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_DMG_APPLY, TRUE)
            Return
        CaseDefault
            Set(LVar1, FORM_ANIM_HURT)
            ExecWait(N(EVS_GetFormAnims))
            ExecWait(N(EVS_JrTroopa_BaseDeath))
            Return
    EndSwitch
    Return
    End
};


EvtScript N(EVS_TakeTurn) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SECOND_PHASE, LVar4)
    IfEq(LVar4, 0)
        Call(SetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SECOND_PHASE, -1)
        Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_DAMAGE, 2)
        Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, 1)
        // ExecWait(N(EVS_Transform))
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, LVar5)
        IfEq(LVar5, 2)
            // ExecWait(N(EVS_Regular_Attack))
        Else
            Sub(LVar6, 1)
            Call(SetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SECOND_PHASE, LVar6)
            Call(GetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, LVar7)
            IfEq(LVar7, 0)
                // ExecWait(N(EVS_Attack_Shape_Spell))
            Else
                // ExecWait(N(EVS_Flying_Attack_Shape_Spell))
            EndIf
            Call(GetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, LVar7)
            IfEq(LVar7, 1)
                Call(GetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SPARK_FLY_AWAY, LVar8)
                Sub(LVar8, 1)
                Call(SetActorVar, ACTOR_SELF, AVAR_TURNS_UNTIL_SPARK_FLY_AWAY, LVar8)
                IfEq(LVar8, 0)
                    Wait(16)
                    ExecWait(N(EVS_Spark_Fly_Away))
                EndIf
                IfEq(LVar8, -1)
                    Wait(16)
                    // ExecWait(N(EVS_Defense_Jab))
                EndIf
                IfEq(LVar8, -2)
                    Wait(16)
                    // ExecWait(N(EVS_Spark_Fly_Back))
                EndIf
            Else
                // ExecWait(N(EVS_Flying_Attack_Shape_Spell))
            EndIf
        EndIf
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Move_Charge) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)

    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Attack_Slam) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)

    Return
    End
};

EvtScript N(EVS_Spark_Fly_Away) = {
    Call(UseBattleCamPreset, BTL_CAM_PRESET_13)
    Call(BattleCamTargetActor, 0)
    Call(SetBattleCamTarget, -114, 0, 0)
    Call(SetBattleCamZoom, 320)
    Call(SetBattleCamOffsetZ, 50)
    Call(MoveBattleCamOver, 20)
    //Call(SpeakToPlayer, ACTOR_SELF, NPC_ANIM_spark_normal_idle_nb, NPC_ANIM_spark_normal_idle_nb, 0, MESSAGE_ID(0x1D, 0x00C0))
    //Call(SetNpcAnimation, 0, NPC_ANIM_spark_normal_idle_nb)
    Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
    Sub(LVar0, 90)
    Add(LVar1, 30)
    Call(NpcFlyTo, 0, LVar0, LVar1, LVar2, 25, -6, EASING_COS_IN_OUT)
    Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_DAMAGE, 1)
    // Remove Boots
    Call(SetActorFlags, ACTOR_SELF, ACTOR_FLAG_UPSIDE_DOWN, TRUE)
    Return
    End
};

EvtScript N(EVS_Lose_Flying_Mode) = {
    Thread
        Wait(10)
        //Call(ActorSpeak, MSG_ID, ACTOR_SELF, PRT_FLYING, ANIM_ParaJrTroopa_Talk, ANIM_ParaJrTroopa_Talk)
    EndThread
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfEq(LVar1, 0)
        Goto(0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 0x301)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2))
    Call(FallToGoal, ACTOR_SELF, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.8))
    Call(JumpToGoal, ACTOR_SELF, 8, FALSE, TRUE, FALSE)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(HPBarToCurrent, ACTOR_SELF)
    Label(0)
        Thread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 10)
            Add(LVar2, 10)
            Loop(3)
                PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0)
                Wait(3)
            EndLoop
        EndThread
    Call(SetPartFlagBits, ACTOR_SELF, PRT_FLYING, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_FLYING, ACTOR_PART_FLAG_NO_TARGET, TRUE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_NO_TARGET, FALSE)
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Defeated)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 0x20E5)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_14)
    Call(SetBattleCamZoom, 260)
    Call(SetBattleCamOffsetZ, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Jump)
    Wait(2)
    Call(JumpPartTo, ACTOR_SELF, PRT_BASE, LVar0, LVar1, LVar2, 2, TRUE)
    Wait(4)
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Midair)
    Wait(4)
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Idle) // Angry Idle
    Wait(6)
    // Call(ActorSpeak, MSG_ID, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Talk) // Angry Idle
    Call(SetAnimation, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_LandAlt)
    Set(LVar3, 0)
    Loop(12)
        Add(LVar3, 15)
        Call(SetActorYaw, ACTOR_SELF, LVar3)
        Wait(1)
    EndLoop
    Wait(20)
    Loop(12)
        Sub(LVar3, 15)
        Call(SetActorYaw, ACTOR_SELF, LVar3)
        Wait(1)
    EndLoop
    Wait(20)
    Call(ActorSpeak, MSG_NONE, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Talk) // Angry Idle
    Call(ActorSpeak, MSG_NONE, ACTOR_SELF, PRT_BASE, ANIM_JrTroopa_Talk, ANIM_JrTroopa_Talk) // Point Anims
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_INVISIBLE, FALSE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_MAGE, ACTOR_PART_FLAG_NO_TARGET, FALSE)
    Call(SetPartFlagBits, ACTOR_SELF, PRT_BASE, ACTOR_PART_FLAG_NO_TARGET, TRUE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAGE, ANIM_MageJrTroopa_Idle)
    Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_DAMAGE, 1)
    Call(SetActorVar, ACTOR_SELF, AVAR_TROOPA_STATE, 2)
    // Add Boots
    Call(SetActorFlags, ACTOR_SELF, ACTOR_FLAG_UPSIDE_DOWN, TRUE)
    Return
    End
};

EvtScript N(EVS_HandlePhase) = {
    Call(GetActorVar, ACTOR_SELF, AVAR_FIRST_TIME_TALKING, LVarB)
    IfEq(LVarB, 0)
        Call(UseIdleAnimation, ACTOR_SELF, FALSE)
        Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
        Call(UseBattleCamPreset, BTL_CAM_PRESET_13)
        Call(SetBattleCamTarget, -114, 0, 0)
        Call(SetBattleCamZoom, 320)
        Call(SetBattleCamOffsetZ, 50)
        Call(MoveBattleCamOver, 20)
        // Call(SpeakToPlayer, 0, ANIM_Spark_Talk_Neutral_NB, ANIM_Spark_Idle_Neutral_NB, 0, MESSAGE_ID(0x1A, 0x00C0))
        Call(SetActorVar, ACTOR_SELF, AVAR_FIRST_TIME_TALKING, 1)
        Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
        Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    EndIf
    Return
    End
};
