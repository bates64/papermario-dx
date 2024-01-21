#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/Tatanga.h"

#define NAMESPACE A(chikako)

extern EvtScript N(EVS_Init);
extern s32 N(DefaultAnims)[];
extern s32 N(ChargedAnims)[];
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_OnDeath);
extern EvtScript N(EVS_Move_Charge);
extern EvtScript N(EVS_Attack_Slam);
extern EvtScript N(EVS_KnockDown);
extern EvtScript N(EVS_DeathExplode);


enum N(ActorPartIDs) {
    PRT_MAIN            = 1,
};

enum N(ActorVars) {
    AVAR_TurnCounter           = 0,
};

enum N(ActorValues) {
    AVAL_ReturnHome             = 1,
    AVAL_EndTurn                = 2,
    AVAL_Death                  = 3,
    AVAL_TurnZero               = 0,
    AVAL_TurnOne                = 1,
    AVAL_TurnTwo                = 2,
};

enum N(ActorParams) {
    DMG_SCARE               = 3,
    DMG_FIREBALL            = 4,
    DMG_LIGHTNING           = 5,
    DMG_FAKEOUT_SCARE_A     = 4,
    DMG_FAKEOUT_SCARE_B     = 2,
    DMG_BOOSTED_LIGHTNING   = 8,
};

s32 N(DefenseTable)[] = {
    ELEMENT_NORMAL,     0,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               0,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,               0,
    STATUS_KEY_FEAR,                0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,            0,
    STATUS_KEY_SHRINK,              0,
    STATUS_KEY_STOP,                0,
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
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 33 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_FLYING,
    .type = ACTOR_TYPE_CHIKAKO,
    .level = ACTOR_LEVEL_CHIKAKO,
    .maxHP = 1,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init),
    .statusTable = N(StatusTable),
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_Chikako_ChikakoIdle,
    STATUS_END,
};

s32 N(ChargedAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_Chikako_ChikakoIdleCharged,
    STATUS_END,
};

EvtScript N(EVS_Init) = {
 Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
 Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
 Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
 Call(SetActorVar, ACTOR_SELF, AVAR_TurnCounter, AVAL_TurnZero)
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
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            ExecWait(Ref(N(EVS_OnDeath)))
        CaseEq(EVENT_BURN_DEATH)
            ExecWait(Ref(N(EVS_OnDeath)))
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseEq(EVENT_SHOCK_HIT)
            Call(PlaySoundAtActor, ACTOR_SELF, 0x00000759)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_ShockHit)
            ExecWait(Ref(N(EVS_OnDeath)))
        CaseEq(EVENT_SHOCK_DEATH)
            Call(PlaySoundAtActor, ACTOR_SELF, 0x00000759)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_ShockHit)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
        CaseOrEq(EVENT_AIR_LIFT_FAILED)
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_Hit)
            ExecWait(Ref(N(EVS_OnDeath)))
            Return
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoIdle)
            ExecWait(EVS_Enemy_Recover)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, TRUE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_OnDeath) = {
 ExecWait(Ref(N(EVS_KnockDown)))
 ExecWait(Ref(N(EVS_DeathExplode)))
 SetConst(LVar0, PRT_MAIN)
 SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoDeath)
 Set(LVar2, EXEC_DEATH_NO_SPINNING)
 ExecWait(EVS_Enemy_Death)
 Return
 End
};

EvtScript N(EVS_TakeTurn) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_TurnCounter, LVar0)
    IfEq(LVar0, AVAL_TurnOne)
        Goto(AVAL_TurnTwo)
    Else
        Goto(AVAL_TurnOne)
    EndIf
    Label(AVAL_TurnOne)
        ExecWait(Ref(N(EVS_Move_Charge)))
        Goto(AVAL_EndTurn)
    Label(AVAL_TurnTwo)
        ExecWait(Ref(N(EVS_Attack_Slam)))
        Goto(AVAL_EndTurn)
    Label(AVAL_EndTurn)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Move_Charge) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_19)
    Call(SetBattleCamZoom, 320)
    Call(MoveBattleCamOver, 50)
    Wait(20)
    Thread
        Call(ShakeCam, CAM_BATTLE, 0, 40, Float(0.3))
    EndThread
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoCharging)
    Call(PlaySoundAtActor, ACTOR_SELF, 0x0000208F)
    Wait(40)
    Call(PlaySoundAtActor, ACTOR_SELF, 0x0000035C)
    Call(SetPartEventFlags, ACTOR_SELF, PRT_MAIN, 0x00400080)
    Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(N(ChargedAnims)))
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoIdleCharged)
    Wait(30)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 30)
    Call(SetActorVar, ACTOR_SELF, AVAR_TurnCounter, AVAL_TurnOne)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript N(EVS_Attack_Slam) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    // Animation here
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoAttack)
    Wait(10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(9.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
            ExecWait(Ref(N(EVS_DeathExplode)))
            Call(SetGoalToTarget, ACTOR_SELF)
            IfEq(LVar0, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Goto(AVAL_Death)
    EndSwitch
    // Damage Mario
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(9.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
    ExecWait(Ref(N(EVS_DeathExplode)))
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(5)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT | DAMAGE_TYPE_BLAST, 0x0000FFFF, 0, 6, BS_FLAGS1_TRIGGER_EVENTS) // 6 Damage
    // Return home
    Label(AVAL_Death)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};

EvtScript N(EVS_KnockDown) = {
 Call(PlaySoundAtActor, ACTOR_SELF, SOUND_FALL_QUICK)
 Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
 Set(LVar1, -15)
 Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
 Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoDeath)
 Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
 Call(JumpToGoal, ACTOR_SELF, 15, FALSE, TRUE, FALSE)
 Return
 End
};

EvtScript N(EVS_DeathExplode) = {
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 40)
    Add(LVar2, 2)
    PlayEffect(EFFECT_BLAST, 0, LVar0, LVar1, LVar2, Float(3.0), 30, 0)
    PlayEffect(EFFECT_SMOKE_RING, 0, LVar0, LVar1, LVar2, 0)
    Add(LVar1, 40)
    Add(LVar2, 2)
    //Call(PlayEffect, ~FX:FaintDustCloud, LVar0, LVar1, LVar2, Float(3.0), 30, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BULLET_BILL_EXPLODE_A)
    // Call  PlaySoundAtActor  ( .Actor:Self 00002078 )
    Call(StartRumble, BTL_RUMBLE_PLAYER_MAX)
    Thread
        Call(ShakeCam, CAM_BATTLE, 0x00000000, 5, Float(1.0))
    EndThread
    Return
    End
};
