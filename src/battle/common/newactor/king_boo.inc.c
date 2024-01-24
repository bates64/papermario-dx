#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/KingBoo.h"

#define NAMESPACE A(king_boo)

extern EvtScript N(EVS_Init);
extern s32 N(DefaultAnims)[];
extern s32 N(LaughAnims)[];
extern s32 N(FireBallAnims)[];
extern s32 N(BooAnims)[];
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_OnHit);
extern EvtScript N(EVS_OnDeath);
extern EvtScript N(EVS_RemoveClone);
extern EvtScript N(EVS_Scare_Phase1Attacks);
extern EvtScript N(EVS_CrownMagic_Phase1Attacks);
extern EvtScript N(EVS_Attack_Scare);
extern EvtScript N(EVS_Attack_FakeoutScare);
extern EvtScript N(EVS_Attack_Fireball);
extern EvtScript N(EVS_Attack_Lightning);
extern EvtScript N(EVS_IllusoryClones);
extern EvtScript N(EVS_BooFlood);
extern EvtScript N(EVS_ClonePosition);
extern EvtScript N(EVS_Attack_FakeoutScareA);
extern EvtScript N(EVS_Attack_FakeoutScareB);
extern EvtScript N(EVS_Attack_BoostedLightning);
extern EvtScript N(EVS_Move_Heal);
extern EvtScript N(EVS_Move_Buff);


enum N(ActorPartIDs) {
    PRT_MAIN        = 1,
    PRT_FIREBALL    = 2,
    PRT_BOO         = 3,
};

enum N(ActorVars) {
    AVAR_Flags                  = 0,
    AVAR_Phase                  = 1,
    AVAR_Clone1Exists           = 2,
    AVAR_Clone2Exists           = 3,
    AVAR_TurnsUntilClones       = 4,
    AVAR_Clone1_ID              = 5,
    AVAR_Clone2_ID              = 6,
};

enum N(ActorValues) {
    AVAL_CheckPhase             = 0,
    AVAL_FirstPhase             = 1,
    AVAL_SecondPhase            = 2,
    AVAL_ScareAttacks           = 3,
    AVAL_CrownMagicAttacks      = 4,
    AVAL_SkipDamage             = 5,
    AVAL_ReturnHome             = 6,
    AVAL_EndTurn                = 7,
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
    ELEMENT_JUMP,       0,
    ELEMENT_SMASH,      0,
    ELEMENT_THROW,     -2,
    ELEMENT_WATER,      3,
    ELEMENT_FIRE,       3,
    ELEMENT_ICE,        3,
    ELEMENT_BLAST,     -4,
    ELEMENT_MAGIC,    100,
    ELEMENT_COSMIC,  -100,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,             100,
    STATUS_KEY_POISON,            100,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,             100,
    STATUS_KEY_FEAR,              100,
    STATUS_KEY_STATIC,            100,
    STATUS_KEY_PARALYZE,          100,
    STATUS_KEY_SHRINK,            100,
    STATUS_KEY_STOP,              100,
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
        .targetOffset = { 0, 43 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_FIREBALL,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(FireBallAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_BOO,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(BooAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_FLYING,
    .type = ACTOR_TYPE_KING_BOO,
    .level = ACTOR_LEVEL_KING_BOO,
    .maxHP = 40,
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
    .size = { 48, 45 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KingBoo_Idle,
    STATUS_KEY_STONE,     ANIM_KingBoo_Still,
    STATUS_KEY_SLEEP,     ANIM_KingBoo_Still,
    STATUS_KEY_POISON,    ANIM_KingBoo_Idle,
    STATUS_KEY_STOP,      ANIM_KingBoo_Still,
    STATUS_KEY_STATIC,    ANIM_KingBoo_Idle,
    STATUS_KEY_PARALYZE,  ANIM_KingBoo_Still,
    STATUS_KEY_DIZZY,     ANIM_KingBoo_Idle,
    STATUS_KEY_FEAR,      ANIM_KingBoo_Idle,
    STATUS_END,
};

s32 N(LaughAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KingBoo_Laugh,
    STATUS_END,
};

s32 N(FireBallAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KingBoo_FireBall,
    STATUS_END,
};

s32 N(BooAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_KingBoo_Boo,
    STATUS_END,
};

EvtScript N(EVS_Init) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_TakeTurn)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Idle)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_HandleEvent)))
    Call(SetActorVar, ACTOR_SELF, AVAR_Flags, 0)
	Call(SetActorVar, ACTOR_SELF, AVAR_Phase, 0)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE )
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE )
	Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone1_ID, -1)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone2_ID, -1)
	// Boo
	Call(CreateNpc, 1, ANIM_KingBoo_Boo)
	Call(SetNpcYaw, 1, 0)
	Call(SetNpcPos, 1, 0, -1000, 0)
	Call(EnableNpcShadow, 1, TRUE)
    Return
    End
};

EvtScript N(EVS_Idle) = {
    Return
    End
};

EvtScript N(EVS_HandleEvent) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
            Call(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(EVS_Enemy_Hit)
			ExecWait(N(EVS_OnHit))
        CaseOrEq(EVENT_HIT)
            Call(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(EVS_Enemy_Hit)
			ExecWait(N(EVS_OnHit))
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            Call(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_BurnHit)
					EndThread
				EndIf
			EndIf
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_BurnHit)
					EndThread
				EndIf
			EndIf
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(EVS_Enemy_BurnHit)
			ExecWait(N(EVS_OnHit))
        CaseEq(EVENT_BURN_DEATH)
            Call(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_BurnHit)
					EndThread
				EndIf
			EndIf
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						ExecWait(EVS_Enemy_BurnHit)
					EndThread
				EndIf
			EndIf
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            SetConst(LVar2, ANIM_KingBoo_Hurt)
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(N(EVS_OnDeath))
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
        CaseOrEq(EVENT_AIR_LIFT_FAILED)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Idle)
            ExecWait(EVS_Enemy_NoDamageHit)
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            Call(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_CloneReact) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
			Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			Call(ActorExists, LVar0, LVar1)
			IfEq(LVar1, TRUE)
				Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				IfEq(LVarB, TRUE)
					Thread
						Call(SetOwnerID, LVar0)
						SetConst(LVar0, PRT_MAIN)
						SetConst(LVar1, ANIM_KingBoo_CloneReact) // Clone Hurt
						ExecWait(EVS_Enemy_Hit)
					EndThread
				EndIf
			EndIf
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(EVS_Enemy_Hit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Hurt)
            ExecWait(N(EVS_OnDeath))
            Return
        /*
        CaseEq(EVENT_END_FIRST_STRIKE)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_MoveFast)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, FALSE)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        */
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Idle)
            ExecWait(EVS_Enemy_Recover)
        CaseEq(EVENT_SCARE_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Slink)
            SetConst(LVar2, ANIM_KingBoo_Laugh)
            ExecWait(EVS_Enemy_NoDamageHit)
            Return
        CaseEq(EVENT_BEGIN_AIR_LIFT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_KingBoo_Idle)
            ExecWait(EVS_Enemy_NoDamageHit)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_OnHit) = {
	// Clone 1
    Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
    Call(ActorExists, LVar9, LVarA)
    IfEq(LVarA, TRUE)
        Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
        IfEq(LVarB, TRUE)
            Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
            Exec(N(EVS_RemoveClone))
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
            ExecGetTID(N(EVS_RemoveClone), LVar0)
            Label(1)
            IsThreadRunning(LVar0, LVar1)
            IfEq(LVar1, TRUE)
                Wait(1)
                Goto(1)
            EndIf
    EndIf
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9 )
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf

	// Clone 2
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf

	Wait(30)
	Call(HideHealthBar, ACTOR_SELF)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_MoveFast)
	Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
	Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Wait(5)
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(HPBarToHome, ACTOR_SELF)
	Return
	End
};

EvtScript N(EVS_OnDeath) = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
    Call(ActorExists, LVar9, LVarA)
    IfEq(LVarA, TRUE)
        Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
        IfEq(LVarB, TRUE)
            Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
            Exec(N(EVS_RemoveClone))
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
            ExecGetTID(N(EVS_RemoveClone), LVar0)
            Label(1)
            IsThreadRunning(LVar0, LVar1)
            IfEq(LVar1, TRUE)
                Wait(1)
                Goto(1)
            EndIf
    EndIf
    // Clone 1
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf

	// Clone 2
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf

    // Boo Flood Disappears
    Call(PlaySoundAtNpc, SOUND_BOO_VANISH_A, SOUND_SPACE_DEFAULT)
    SetF(LVar0, 128) // ALPHA
    Call(SetNpcRenderMode, 1, RENDER_MODE_SURFACE_XLU_LAYER1)
	Loop(8)
		Sub(LVar0, 16)
		Call(SetNpcImgFXParams, 1, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
		Wait(1)
	EndLoop
	Call(SetNpcAnimation, 1, ANIM_KingBoo_BooWellMany)
    Call(SetNpcPos, 1, 0, -1000, -125)

	// King Boo's "Death"
	Wait(15)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)

	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Wait(30)
	Call(RemoveActor, ACTOR_SELF)
	Return
	End
};

EvtScript (N(EVS_RemoveClone)) = {
	Call(UseIdleAnimation, ACTOR_SELF, FALSE)
	Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	Call(UseIdleAnimation, LVar9, FALSE)
	Call(SetAnimation, LVar9, PRT_MAIN, ANIM_KingBoo_CloneReact)
	Wait(20)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Call(EnableActorBlur, LVar9, TRUE)
	Call(SetActorFlagBits, LVar9, ACTOR_FLAG_NO_DMG_APPLY, TRUE)
	Call(RemoveActor, LVar9)
	Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(N(DefaultAnims)))
	Call(UseIdleAnimation, ACTOR_SELF, TRUE)
	Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
	Return
	End
};






EvtScript N(EVS_TakeTurn) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Label(AVAL_CheckPhase)
    //Goto(AVAL_FirstPhase)
    Goto(AVAL_SecondPhase)
    Call(GetActorVar, ACTOR_SELF, AVAR_Phase, LVar6)
    Switch(LVar6)
        CaseEq(0)
            Call(GetActorHP, ACTOR_SELF, LVar4)
            IfLt(LVar4, 21)
                Call(SetActorVar, ACTOR_SELF, AVAR_Phase, 1)
                Goto(AVAL_SecondPhase)
            Else
                Goto(AVAL_FirstPhase)
            EndIf
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, AVAR_Phase, 2)
            Goto(AVAL_SecondPhase)
        CaseEq(2)
            Goto(AVAL_SecondPhase)
    EndSwitch
    Label(AVAL_FirstPhase)
    Call(RandInt, 100, LVar1)
    Switch(LVar1)
        CaseLt(70)
            Set(LVar0, 0)
        CaseDefault
            Set(LVar0, 1)
    EndSwitch
    //Set(LVar0, 1) // Set( Attack
    Switch(LVar0)
        CaseEq(0)
            ExecWait(N(EVS_Scare_Phase1Attacks))
            Goto(AVAL_EndTurn)
        CaseEq(1)
            ExecWait(N(EVS_CrownMagic_Phase1Attacks))
            Goto(AVAL_EndTurn)
    EndSwitch

    Label(AVAL_SecondPhase)
    Call(GetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, LVar3)
    Switch(LVar3)
        CaseEq(0)
            ExecWait(N(EVS_IllusoryClones))
            Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnOne)
            Goto(AVAL_EndTurn)
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            Call(ActorExists, LVarA, LVar4)
            IfEq(LVar4, FALSE)
                Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnTwo)
                Goto(AVAL_ScareAttacks)
            Else
                Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                Goto(AVAL_CrownMagicAttacks)
            EndIf
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            Call(ActorExists, LVarA, LVar4)
            IfEq(LVar4, FALSE)
                Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                Goto(AVAL_ScareAttacks)
            Else
                Call(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                Goto(AVAL_CrownMagicAttacks)
            EndIf
    EndSwitch

    Label(AVAL_CrownMagicAttacks)
    Call(RandInt, 100, LVar1)
    Switch(LVar1)
        CaseLt(80)
            Set(LVar0, 0)
        CaseDefault
            Set(LVar0, 1)
    EndSwitch
    //Set(LVar0, 0) // Set Attack
    Switch(LVar0)
        CaseEq(0)
            ExecWait(N(EVS_Attack_BoostedLightning))
            Goto(AVAL_EndTurn)
        CaseEq(1)
            ExecWait(N(EVS_Move_Heal))
            Goto(AVAL_EndTurn)
    EndSwitch

    Label(AVAL_ScareAttacks)
    Call(RandInt, 100, LVar1)
    Switch(LVar1)
        CaseLt(70)
            Set(LVar0, 0)
        CaseDefault
            Set(LVar0, 1)
    EndSwitch
    //Set(LVar0, 0) // Set Attack
    Switch(LVar0)
        CaseEq(0)
            ExecWait(N(EVS_Attack_FakeoutScareB))
            Goto(AVAL_EndTurn)
        CaseEq(1)
            ExecWait(N(EVS_Attack_FakeoutScareA))
            Goto(AVAL_EndTurn)
    EndSwitch


    Label(AVAL_EndTurn)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Scare_Phase1Attacks) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(RandInt, 100, LVar1)
    Switch(LVar1)
        CaseLt(70)
            Set(LVar0, 0)
        CaseDefault
            Set(LVar0, 1)
    EndSwitch
    //Set(LVar0, 0) // Set Attack
    Switch(LVar0)
        CaseEq(0)
            ExecWait(N(EVS_Attack_Scare))
            Goto(AVAL_EndTurn)
        CaseEq(1)
            ExecWait(N(EVS_Attack_FakeoutScare))
            Goto(AVAL_EndTurn)
    EndSwitch
    Label(AVAL_EndTurn)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_CrownMagic_Phase1Attacks) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(RandInt, 100, LVar1)
    Switch(LVar1)
        CaseLt(60)
            Set(LVar0, 0)
        CaseDefault
            Set(LVar0, 1)
    EndSwitch
    //Set(LVar0, 1) // Set Attack
    Switch(LVar0)
        CaseEq(0)
            ExecWait(N(EVS_Attack_Fireball))
            Goto(AVAL_EndTurn)
        CaseEq(1)
            ExecWait(N(EVS_Attack_Lightning))
            Goto(AVAL_EndTurn)
    EndSwitch
    Label(AVAL_EndTurn)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Attack_Scare) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
	Wait(20)
	Call(UseBattleCamPreset, BTL_CAM_PRESET_19)
	Call(SetGoalToTarget, ACTOR_SELF)
	Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Add(LVar0, 20)
	Set(LVar1, 0)
	Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
	Call(SetBattleCamZoom, 350)
	Call(SetBattleCamOffsetZ, 45)
	Call(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	Call(MoveBattleCamOver, 20)
	Call(SetGoalToTarget, ACTOR_SELF )
	Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Add(LVar0, 25)
	Set(LVar1, 10)
	Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Scare)
	Wait(30)
	Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
	Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
			IfEq(LVar0, HIT_RESULT_LUCKY)
				Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
			EndIf
			Goto(AVAL_SkipDamage)
		EndCaseGroup
	EndSwitch
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
	Wait(5)
	Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_SCARE, BS_FLAGS1_TRIGGER_EVENTS) // 3 Damage
	Label(AVAL_SkipDamage)
	Wait(30)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Wait(10)
	Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
	Call(MoveBattleCamOver, 20)
	Call(SetGoalToHome, ACTOR_SELF)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Attack_FakeoutScare) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
	Wait(20)
	Call(UseBattleCamPreset, BTL_CAM_PRESET_19)
	Call(SetGoalToTarget, ACTOR_SELF)
	Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Add(LVar0, 20)
	Set(LVar1, 0)
	Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
	Call(SetBattleCamZoom, 350)
	Call(SetBattleCamOffsetZ, 45)
	Call(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	Call(MoveBattleCamOver, 20)
	Call(SetGoalToTarget, ACTOR_SELF )
	Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Add(LVar0, 25)
	Set(LVar1, 10)
	Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop

	Thread
		Wait(15)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 1)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 1)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 2)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 2)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 3)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 3)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
	EndThread

	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Fakeout)
	Wait(40)

	// Wiggle a little bit
	Thread
		Wait(15)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 1)
		Call(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 1)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub (LVarD, 2)
		Call(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 2)
		Call(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 3)
		Call(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Add(LVarD, 3)
		Call(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Wait(2)
		Call(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		Sub(LVarD, 4)
		Call(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
	EndThread
	Wait(30)
	Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
	Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
			IfEq(LVar0, HIT_RESULT_LUCKY)
				Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
			EndIf
			Goto(AVAL_SkipDamage)
		EndCaseGroup
	EndSwitch
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
	Wait(5)
	Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_SCARE, BS_FLAGS1_TRIGGER_EVENTS) // 3 Damage
	Label(AVAL_SkipDamage)
	Wait(30)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Wait(10)
	Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
	Call(MoveBattleCamOver, 20)
	Call(SetGoalToHome, ACTOR_SELF)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

#include "common/CalculateArcsinDeg.inc.c"

#include "common/UnkBackgroundFunc3.inc.c"

#include "common/SetBackgroundAlpha.inc.c"

EvtScript N(EVS_Attack_Fireball) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	Call(BattleCamTargetActor, ACTOR_SELF)
	Call(N(UnkBackgroundFunc3))
    Call(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    Label(0)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Wait(5)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	Wait(50)
    Call(SetAnimation, ACTOR_SELF, PRT_FIREBALL, ANIM_KingBoo_FireBall)
    Wait(15)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
	Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2)
    Call(SetPartScale, ACTOR_SELF, PRT_FIREBALL, Float(1.0), Float(1.0), Float(1.0))
	Call(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, 0)
    Call(SetPartJumpGravity, ACTOR_SELF, PRT_FIREBALL, Float(3.0))
    Call(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, FALSE)
	Call(MakeLerp, 200, 0, 60, EASING_LINEAR)
    Label(2)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(EnemyTestTarget, ACTOR_SELF, LVar3, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVar3)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Add(LVar1, -32) // Target mario's feet
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_PETIT_PIRANHA_DIVE)
			Thread
				Call(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar1, LVar2, LVar0)
			   Set(LVar0,  0)
				Loop(16)
					Call(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar4, LVar5, LVar6)
					Call(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
					Call(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, LVar0)
					Set(LVar1, LVar4)
					Set(LVar2, LVar5)
					Set(LVar3, LVar6)
					Wait(1)
				EndLoop
			EndThread
            Call(JumpPartTo, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2, 15, TRUE)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            Wait(2)
        EndCaseGroup
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_PETIT_PIRANHA_DIVE)
			Thread
				Call(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar1, LVar2, LVar0)
			    Set(LVar0,  0)
				Loop(16)
					Call(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar4, LVar5, LVar6)
					Call(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
					Call(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, LVar0)
					Set(LVar1, LVar4)
					Set(LVar2, LVar5)
					Set(LVar3, LVar6)
					Wait(1)
				EndLoop
			EndThread
            Call(JumpPartTo, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2, 15, TRUE)
            Call(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_FIRE | DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_FIREBALL, BS_FLAGS1_TRIGGER_EVENTS) // 4 Damage
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

API_CALLABLE(N(SetBoltColors)) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, *args++);

    effect->data.lightningBolt->outerColor.r = 128;
    effect->data.lightningBolt->outerColor.g = 0;
    effect->data.lightningBolt->outerColor.b = 128;
    effect->data.lightningBolt->innerColor.r = 255;
    effect->data.lightningBolt->innerColor.g = 255;
    effect->data.lightningBolt->innerColor.b = 255;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Attack_Lightning) = {
	// Go to player
	Call(UseIdleAnimation, ACTOR_SELF, FALSE)
	Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	Call(BattleCamTargetActor, ACTOR_SELF)
	Call(N(UnkBackgroundFunc3))
    Call(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    Label(0)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
	Wait(10)
	// Animation here
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	Wait(55)
	Call(StartRumble, BTL_RUMBLE_HIT_EXTREME)
	Call(ShakeCam, CAM_BATTLE, 0, 5, Float(1.0))
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LIGHTNING_STRIKE)
	Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
	Switch(LVar0)
		CaseOrEq(HIT_RESULT_MISS)
		CaseOrEq(HIT_RESULT_LUCKY)
			IfEq(LVar0, HIT_RESULT_LUCKY)
				Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
				Call(RandInt, 40, LVar1)
				Sub(LVar0, LVar1)
				Set(LVar1, 200)
				Call(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
				Add(LVar3, 30)
				Set(LVar4, 0)
                PlayEffect(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(0.5), 12, 0)
				Call(N(SetBoltColors), LVarF)
				Wait(12)
				Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 20)
                //Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
                PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_GetAngry)
                Wait(35)
			EndIf
			Goto(AVAL_ReturnHome)
	EndSwitch
	// Damage Mario
	Call(SetGoalToTarget, ACTOR_SELF)
	Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
	Call(RandInt, 40, LVar1)
	Add(LVar0, LVar1)
	Add(LVar0, 50)
	Set(LVar1, 200)
	Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
	Set(LVar4, 0)
    PlayEffect(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.5), 12, 0)
	Call(N(SetBoltColors), LVarF)
	Wait(12)
	Call(EnemyDamageTarget, ACTOR_SELF, LVar0, (DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_SHOCK | DAMAGE_TYPE_NO_CONTACT), 0, SUPPRESS_EVENT_FLAG_10000, DMG_LIGHTNING, BS_FLAGS1_TRIGGER_EVENTS) // 5 Damage
	// Return home
	Label(AVAL_ReturnHome)
    Call(MakeLerp, 200, 0, 60, EASING_LINEAR)
    Label(2)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Call(UseIdleAnimation, ACTOR_SELF, TRUE)
	Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
	Return
	End
};

s32 N(CloneStatusTable)[] = {
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

EvtScript N(EVS_Clone_Dummy) = {
    Return
    End
};

EvtScript N(EVS_Init_Clone) = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(N(EVS_Clone_Dummy)))
    Call(BindIdle, ACTOR_SELF, Ref(N(EVS_Clone_Dummy)))
    Call(BindHandleEvent, ACTOR_SELF, Ref(N(EVS_Clone_Dummy)))
    Return
    End
};

ActorBlueprint N(clone) = {
    .flags = ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_FLYING | ACTOR_FLAG_NO_SHADOW,
    .type = ACTOR_TYPE_KING_BOO,
    .level = ACTOR_LEVEL_KING_BOO,
    .maxHP = 40,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init_Clone),
    .statusTable = N(CloneStatusTable),
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 0,
    .coinReward = 0,
    .size = { 48, 45 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Vec3i N(CloneSummonPos) = { NPC_DISPOSE_LOCATION };

Formation N(CloneFormation) = {
    ACTOR_BY_POS(N(clone), N(CloneSummonPos), 0),
};

EvtScript N(EVS_BooFlood) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_Phase, LVar6)
	IfEq(LVar6, 1)
		// Boo 1
		Call(SetNpcPos, 1, 0, 0, -125)
        Call(PlaySoundAtNpc, SOUND_BOO_VANISH_A, SOUND_SPACE_DEFAULT)
        SetF(LVar0, 0) // ALPHA
        Call(SetNpcRenderMode, 1, RENDER_MODE_SURFACE_XLU_LAYER1)
	    Loop(8)
		    Add(LVar0, 16)
		    Call(SetNpcImgFXParams, 1, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
		    Wait(1)
	    EndLoop
		Call(SetNpcAnimation, 1, ANIM_KingBoo_BooWellMany)

		/* Boo 2
		Call(SetNpcPos, 2, 5, -200, -125)
		Call(SetNpcAnimation, 2, ANIM_KingBoo_BooLaugh)
		Call(NpcFlyTo, 2, 5, 300, -125, 20, 0, EASING_COS_IN_OUT)
		// Boo 3
		Call(SetNpcPos, 3, -10, -200, -125)
		Call(SetNpcAnimation, 3, ANIM_KingBoo_BooLaugh)
		Call(NpcFlyTo, 3, -10, 300, -125, 20, 0, EASING_COS_IN_OUT)
	    // Boo 4
		Call(SetNpcPos, 4, 10, -200, -125)
		Call(SetNpcAnimation, 4, ANIM_KingBoo_BooLaugh)
		Call(NpcFlyTo, 4, 10, 300, -125, 20, 0, EASING_COS_IN_OUT)
		// Boo 5
		Call(SetNpcPos, 5, -5, -200, -125)
		Call(SetNpcAnimation, 5, ANIM_KingBoo_BooLaugh)
		Call(NpcFlyTo, 5, -5, 300, -125, 20, 0, EASING_COS_IN_OUT)
	    // Boo 6
		Call(SetNpcPos, 6, 0, -200, -125)
		Call(SetNpcAnimation, 6, ANIM_KingBoo_BooLaugh)
		Call(NpcFlyTo, 6, 0, 300, -125, 20, 0, EASING_COS_IN_OUT)
		*/
	EndIf
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_BooAbsorb)
	Wait(50)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_BooAbsorbEnd)
	Wait(20)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar3, 256)
	Loop(16)
		Sub(LVar3, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar3)
		Wait(1)
	EndLoop
	Wait(5)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)
	//Call(SetNpcAnimation, 1, ANIM_KingBoo_BooWellSingle )
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_IllusoryClones) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	Wait(70)
	ExecWait(N(EVS_BooFlood))
	Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, TRUE)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, TRUE)
	Set(LVar0, 0)
	Call(GetActorHP, ACTOR_SELF, LVarA)
	Call(SummonEnemy, Ref(N(CloneFormation)), FALSE)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	Call(SetPartEventBits, LVar0, PRT_MAIN, ACTOR_EVENT_FLAG_ILLUSORY, TRUE)
	Call(SetEnemyHP, LVar0, LVarA)
	Call(SummonEnemy, Ref(N(CloneFormation)), FALSE)
	Call(SetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	Call(SetPartEventBits, LVar0, PRT_MAIN, ACTOR_EVENT_FLAG_ILLUSORY, TRUE)
	Call(SetEnemyHP, LVar0, LVarA)

	// King Boo
	Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 1 Vanish
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
	SetF(LVar3, 0)
	Call(SetPartAlpha, LVarA, PRT_MAIN, LVar3)
	Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
	Call(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW, TRUE)

    // Clone 2 Vanish
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarA)
	SetF(LVar3, 0)
	Call(SetPartAlpha, LVarA, PRT_MAIN, LVar3)
	Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
	Wait(1)
	Call(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW, TRUE)

	ExecWait(N(EVS_ClonePosition))

	// King Boo
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(HPBarToHome, ACTOR_SELF)

	// Clone 1
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
	Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	Call(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
	Call(HPBarToHome, LVarA)

	// Clone 2
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarA)
	Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	Call(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
	Call(HPBarToHome, LVarA)

	// King Boo Appears
	Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
	Call(MoveBattleCamOver, 20)
	//Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, EVT_PRT(N(LaughAnims)))
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Laugh)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_JUMP_SCARE)
	SetF(LVar3, 256)
	Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar3)
	Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 1 Appears
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	Call(UseIdleAnimation, LVar0, FALSE)
	Call(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_Laugh )
	Call(PlaySoundAtActor, LVar0, SOUND_BOO_APPEAR_A)
	SetF(LVar3, 256)
	Call(SetPartAlpha, LVar0, PRT_MAIN, LVar3)
	Call(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 2 Appears
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	Call(UseIdleAnimation, LVar0, FALSE)
	Call(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_Laugh)
	Call(PlaySoundAtActor, LVar0, SOUND_BOO_APPEAR_A)
	SetF(LVar3, 256)
	Call(SetPartAlpha, LVar0, PRT_MAIN, LVar3)
	Call(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_SHADOW, TRUE)

	Wait(15)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	Call(UseIdleAnimation, LVar0, TRUE)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	Call(UseIdleAnimation, LVar0, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_ClonePosition) = {
	Call(RandInt, 1000, LVar0)
    Mod(LVar0, 3)
	Set(LVar0, 1) // To see the Position
    Switch(LVar0)
		CaseEq(0)
            Set(LVarA, ACTOR_SELF)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarB)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarC)
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            Set(LVarB, ACTOR_SELF)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarC)
		CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarB)
            Set(LVarC, ACTOR_SELF)
	EndSwitch
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 150)

	// LVarA
	Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	Set(LVar0, 20)
	Set(LVar2, 5)
	Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)

	// LVarB
	Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
	Set(LVar0, 70)
	Set(LVar2, 5)
	Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)

	// LVarC
	Call(GetActorPos, LVarC, LVar0, LVar1, LVar2)
	Set(LVar0, 120)
	Set(LVar2, 5)
	Call(SetActorPos, LVarC, LVar0, LVar1, LVar2)

    Wait(15)
    Return
    End
};

EvtScript N(EVS_Attack_FakeoutScareA) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    SetF(LVar0, 256)
    Loop(16)
        Sub(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    Wait(20)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_19)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
	Call(SetBattleCamZoom, 350)
	Call(SetBattleCamOffsetZ, 45)
	Call(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	Call(MoveBattleCamOver, 20)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Set(LVar1, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    SetF(LVar0, 0)
    Loop(16)
        Add(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    // randomized delay
    Call(RandInt, 20, LVar0)
    Wait(LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_DoubleScareFakeoutA)
    Wait(55)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    Wait(60)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            IfEq(LVar0, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Goto(AVAL_SkipDamage)
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
    Wait(5)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_FAKEOUT_SCARE_A, BS_FLAGS1_TRIGGER_EVENTS) // 4 Damage
    // Call(PlaySoundAtPart, ACTOR_SELF PRT_BOO SOUND_BOO_VANISH_A)
    Label(AVAL_SkipDamage)
    Wait(45)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    SetF(LVar0, 256)
    Loop(16)
        Sub(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 20)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    SetF(LVar0, 0)
    Loop(16)
        Add(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};
EvtScript N(EVS_Attack_FakeoutScareB) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    SetF(LVar0, 256)
    Loop(16)
        Sub(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    Wait(20)
    Call(UseBattleCamPreset, BTL_CAM_PRESET_19)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
	Call(SetBattleCamZoom, 350)
	Call(SetBattleCamOffsetZ, 45)
	Call(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	Call(MoveBattleCamOver, 20)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 45)
    Set(LVar1, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    SetF(LVar0, 0)
    Loop(16)
        Add(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    // randomized delay
    Call(RandInt, 20, LVar0)
    Wait(LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_DoubleScareFakeoutB)
    Wait(50)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            IfEq(LVar0, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Goto(AVAL_SkipDamage)
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar0, -130)
    Set(LVar1, -2)
    Call(SetPartPos, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyPartTo, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2, 0, 0, EASING_COS_IN_OUT)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
    Wait(5)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT | DAMAGE_TYPE_STATUS_ALWAYS_HITS, SUPPRESS_EVENT_ALL, DMG_STATUS_IGNORE_RES(STATUS_FLAG_SHRINK, 2), DMG_FAKEOUT_SCARE_B, BS_FLAGS1_TRIGGER_EVENTS) // 2 Damage
    // Call(PlaySoundAtPart, ACTOR_SELF, PRT_BOO SOUND_BOO_VANISH_A)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Set(LVar2, 0)
    Call(SetPartPos, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2)
    Label(AVAL_SkipDamage)
    Wait(45)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    SetF(LVar0, 256)
    Loop(16)
        Sub(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Wait(10)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 20)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    SetF(LVar0, 0)
    Loop(16)
        Add(LVar0, 16)
        Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        Wait(1)
    EndLoop
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Attack_BoostedLightning) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    ExecWait(N(EVS_Move_Buff))
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Wait(10)
	Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
	Call(MoveBattleCamOver, 20)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(HPBarToHome, ACTOR_SELF)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	Call(BattleCamTargetActor, ACTOR_SELF)
	Call(N(UnkBackgroundFunc3))
    Call(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    Label(0)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
	Wait(10)
	// Animation here
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	Wait(55)
	Call(StartRumble, BTL_RUMBLE_PLAYER_MAX)
	Call(ShakeCam, CAM_BATTLE, 0, 5, Float(2.0))
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LIGHTNING_STRIKE)
	Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
	Switch(LVar0)
		CaseOrEq(HIT_RESULT_MISS)
		CaseOrEq(HIT_RESULT_LUCKY)
			IfEq(LVar0, HIT_RESULT_LUCKY)
				Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
				Call(RandInt, 40, LVar1)
				Sub(LVar0, LVar1)
				Set(LVar1, 200)
				Call(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
				Add(LVar3, 30)
				Set(LVar4, 0)
                PlayEffect(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 12, 0)
				Call(N(SetBoltColors), LVarF)
				Wait(12)
				Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 20)
                //Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
                Call(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
                PlayEffect(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_GetAngry)
                Wait(35)
			EndIf
			Goto(AVAL_ReturnHome)
	EndSwitch
	// Damage Mario
	Call(SetGoalToTarget, ACTOR_SELF)
	Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
	Call(RandInt, 40, LVar1)
	Add(LVar0, LVar1)
	Add(LVar0, 50)
	Set(LVar1, 200)
	Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
	Set(LVar4, 0)
    PlayEffect(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(2.5), 12, 0)
	Call(N(SetBoltColors), LVarF)
	Wait(12)
	Call(EnemyDamageTarget, ACTOR_SELF, LVar0, (DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_SHOCK | DAMAGE_TYPE_NO_CONTACT), 0, SUPPRESS_EVENT_FLAG_10000, DMG_BOOSTED_LIGHTNING, BS_FLAGS1_TRIGGER_EVENTS) // 5 Damage
	// Return home
	Label(AVAL_ReturnHome)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(HPBarToHome, ACTOR_SELF)
    Call(MakeLerp, 200, 0, 60, EASING_LINEAR)
    Label(2)
        Call(UpdateLerp)
        Call(N(SetBackgroundAlpha), LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Move_Heal) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    ExecWait(N(EVS_Move_Buff))
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	SetF(LVar0, 256)
	Loop(16)
		Sub(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Wait(10)
	Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
	Call(MoveBattleCamOver, 20)
	Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
	Call(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	Call(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Call(HPBarToHome, ACTOR_SELF)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	SetF(LVar0, 0)
	Loop(16)
		Add(LVar0, 16)
		Call(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		Wait(1)
	EndLoop
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	Thread
		Wait(5)
		Call(PlaySoundAtActor, ACTOR_SELF, SOUND_RECOVER_HEART)
		Call(PlaySoundAtActor, ACTOR_SELF, SOUND_HEART_BOUNCE)
		Wait(30)
		Call(PlaySoundAtActor, ACTOR_SELF, SOUND_STAR_BOUNCE_A)
	EndThread
	Thread
		Call(FreezeBattleState, TRUE)
		Call(HealActor, ACTOR_SELF, 10, FALSE)
		Call(FreezeBattleState, FALSE)
	EndThread
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};

EvtScript N(EVS_Move_Buff) = {
    Call(UseIdleAnimation, ACTOR_SELF, FALSE)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	Call(UseIdleAnimation, LVar0, FALSE)
	Call(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, LVar0, SOUND_SPELL_CAST4)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	Call(UseIdleAnimation, LVar0, FALSE)
	Call(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	Call(PlaySoundAtActor, LVar0, SOUND_SPELL_CAST4)
	Wait(80)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	Call(UseIdleAnimation, LVar0, TRUE)
	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	Call(UseIdleAnimation, LVar0, TRUE)
	Call(PlaySoundAtActor, ACTOR_SELF, SOUND_POWER_UP)
	Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	Add(LVar1, 20)
	PlayEffect(EFFECT_ENERGY_IN_OUT, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0)
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Laugh)
	Wait(30)
    Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
    Call(ActorExists, LVar9, LVarA)
    IfEq(LVarA, TRUE)
        Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
        IfEq(LVarB, TRUE)
            Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
            Exec(N(EVS_RemoveClone))
            Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
            ExecGetTID(N(EVS_RemoveClone), LVar0)
            Label(1)
            IsThreadRunning(LVar0, LVar1)
            IfEq(LVar1, TRUE)
                Wait(1)
                Goto(1)
            EndIf
    EndIf

	// Clone 1
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf

	// Clone 2
	// Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// Call(ActorExists, LVar9, LVarA)
	// IfEq(LVarA, TRUE)
	// 	Call(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
	// 	IfEq(LVarB, TRUE)
	// 		Call(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
	// 		Call(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	// 		Exec(N(EVS_RemoveClone))
	// 	EndIf
	// EndIf
	Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, TRUE)
    Return
    End
};
