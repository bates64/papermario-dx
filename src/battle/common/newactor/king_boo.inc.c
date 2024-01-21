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
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(EVS_TakeTurn)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(EVS_Idle)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(EVS_HandleEvent)))
    EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Flags, 0)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Phase, 0)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE )
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE )
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1_ID, -1)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2_ID, -1)
	// Boo
	EVT_CALL(CreateNpc, 1, ANIM_KingBoo_Boo)
	EVT_CALL(SetNpcYaw, 1, 0)
	EVT_CALL(SetNpcPos, 1, 0, -1000, 0)
	EVT_CALL(EnableNpcShadow, 1, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Idle) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HandleEvent) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(EVENT_HIT_COMBO)
            EVT_CALL(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
			EVT_EXEC_WAIT(N(EVS_OnHit))
        EVT_CASE_OR_EQ(EVENT_HIT)
            EVT_CALL(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
			EVT_EXEC_WAIT(N(EVS_OnHit))
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_BURN_HIT)
            EVT_CALL(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
			EVT_EXEC_WAIT(N(EVS_OnHit))
        EVT_CASE_EQ(EVENT_BURN_DEATH)
            EVT_CALL(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_SET_CONST(LVar2, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(N(EVS_OnDeath))
            EVT_RETURN
        EVT_CASE_OR_EQ(EVENT_ZERO_DAMAGE)
        EVT_CASE_OR_EQ(EVENT_IMMUNE)
        EVT_CASE_OR_EQ(EVENT_AIR_LIFT_FAILED)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_NoDamageHit)
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_DEATH)
            EVT_CALL(SetActorVar, ACTOR_ENEMY0, AVAR_Flags, LVar0)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_CloneReact) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
			EVT_CALL(ActorExists, LVar0, LVar1)
			EVT_IF_EQ(LVar1, TRUE)
				EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
				EVT_IF_EQ(LVarB, TRUE)
					EVT_THREAD
						EVT_CALL(SetOwnerID, LVar0)
						EVT_SET_CONST(LVar0, PRT_MAIN)
						EVT_SET_CONST(LVar1, ANIM_KingBoo_CloneReact) // Clone Hurt
						EVT_EXEC_WAIT(EVS_Enemy_Hit)
					EVT_END_THREAD
				EVT_END_IF
			EVT_END_IF
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Hurt)
            EVT_EXEC_WAIT(N(EVS_OnDeath))
            EVT_RETURN
        /*
        EVT_CASE_EQ(EVENT_END_FIRST_STRIKE)
            EVT_CALL(SetAnimationRate, ACTOR_SELF, PRT_MAIN, EVT_FLOAT(2.0))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_MoveFast)
            EVT_CALL(SetGoalToHome, ACTOR_SELF)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(4.0))
            EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
            EVT_CALL(SetAnimationRate, ACTOR_SELF, PRT_MAIN, EVT_FLOAT(1.0))
            EVT_CALL(HPBarToHome, ACTOR_SELF)
        */
        EVT_CASE_EQ(EVENT_RECOVER_STATUS)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_Recover)
        EVT_CASE_EQ(EVENT_SCARE_AWAY)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Slink)
            EVT_SET_CONST(LVar2, ANIM_KingBoo_Laugh)
            EVT_EXEC_WAIT(EVS_Enemy_NoDamageHit)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_BEGIN_AIR_LIFT)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_KingBoo_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_NoDamageHit)
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_OnHit) = {
	// Clone 1
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9 )
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF
	// Clone 2
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF

	EVT_WAIT(30)
	EVT_CALL(HideHealthBar, ACTOR_SELF)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_MoveFast)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
	EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_WAIT(5)
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, ACTOR_SELF)
	EVT_RETURN
	EVT_END
};

EvtScript N(EVS_OnDeath) = {
	// Clone 1
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF
	// Clone 2
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF

    // Boo Flood Disappears
    EVT_CALL(PlaySoundAtNpc, SOUND_BOO_VANISH_A, SOUND_SPACE_DEFAULT)
    EVT_SETF(LVar0, 128) // ALPHA
    EVT_CALL(SetNpcRenderMode, 1, RENDER_MODE_SURFACE_XLU_LAYER1)
	EVT_LOOP(8)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetNpcImgFXParams, 1, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_CALL(SetNpcAnimation, 1, ANIM_KingBoo_BooWellMany)
    EVT_CALL(SetNpcPos, 1, 0, -1000, -125)

	// King Boo's "Death"
	EVT_WAIT(15)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)

	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(30)
	EVT_CALL(RemoveActor, ACTOR_SELF)
	EVT_RETURN
	EVT_END
};

EvtScript (N(EVS_RemoveClone)) = {
	EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
	EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	EVT_CALL(UseIdleAnimation, LVar9, FALSE)
	EVT_CALL(SetAnimation, LVar9, PRT_MAIN, ANIM_KingBoo_CloneReact)
	EVT_WAIT(20)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_CALL(EnableActorBlur, LVar9, TRUE)
	EVT_CALL(SetActorFlagBits, LVar9, ACTOR_FLAG_NO_DMG_APPLY, TRUE)
	EVT_CALL(RemoveActor, LVar9)
	EVT_CALL(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, EVT_PTR(N(DefaultAnims)))
	EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
	EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
	EVT_RETURN
	EVT_END
};






EvtScript N(EVS_TakeTurn) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_LABEL(AVAL_CheckPhase)
    //EVT_GOTO(AVAL_FirstPhase)
    //EVT_GOTO(AVAL_SecondPhase)
    EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Phase, LVar6)
    EVT_SWITCH(LVar6)
        EVT_CASE_EQ(0)
            EVT_CALL(GetActorHP, ACTOR_SELF, LVar4)
            EVT_IF_LT(LVar4, 21)
                EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Phase, 1)
                EVT_GOTO(AVAL_SecondPhase)
            EVT_ELSE
                EVT_GOTO(AVAL_FirstPhase)
            EVT_END_IF
        EVT_CASE_EQ(1)
            EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Phase, 2)
            EVT_GOTO(AVAL_SecondPhase)
        EVT_CASE_EQ(2)
            EVT_GOTO(AVAL_SecondPhase)
    EVT_END_SWITCH
    EVT_LABEL(AVAL_FirstPhase)
    EVT_CALL(RandInt, 100, LVar1)
    EVT_SWITCH(LVar1)
        EVT_CASE_LT(70)
            EVT_SET(LVar0, 0)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 1)
    EVT_END_SWITCH
    //EVT_SET(LVar0, 1) // EVT_SET( Attack
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_Scare_Phase1Attacks))
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_CrownMagic_Phase1Attacks))
            EVT_GOTO(AVAL_EndTurn)
    EVT_END_SWITCH

    EVT_LABEL(AVAL_SecondPhase)
    EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, LVar3)
    EVT_SWITCH(LVar3)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_IllusoryClones))
            EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnOne)
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            EVT_CALL(ActorExists, LVarA, LVar4)
            EVT_IF_EQ(LVar4, FALSE)
                EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnTwo)
                EVT_GOTO(AVAL_ScareAttacks)
            EVT_ELSE
                EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                EVT_GOTO(AVAL_CrownMagicAttacks)
            EVT_END_IF
        EVT_CASE_EQ(2)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            EVT_CALL(ActorExists, LVarA, LVar4)
            EVT_IF_EQ(LVar4, FALSE)
                EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                EVT_GOTO(AVAL_ScareAttacks)
            EVT_ELSE
                EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_TurnsUntilClones, AVAL_TurnZero)
                EVT_GOTO(AVAL_CrownMagicAttacks)
            EVT_END_IF
    EVT_END_SWITCH

    EVT_LABEL(AVAL_CrownMagicAttacks)
    EVT_CALL(RandInt, 100, LVar1)
    EVT_SWITCH(LVar1)
        EVT_CASE_LT(80)
            EVT_SET(LVar0, 0)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 1)
    EVT_END_SWITCH
    //EVT_SET(LVar0, 0) // EVT_SET Attack
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_Attack_BoostedLightning))
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_Move_Heal))
            EVT_GOTO(AVAL_EndTurn)
    EVT_END_SWITCH

    EVT_LABEL(AVAL_ScareAttacks)
    EVT_CALL(RandInt, 100, LVar1)
    EVT_SWITCH(LVar1)
        EVT_CASE_LT(70)
            EVT_SET(LVar0, 0)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 1)
    EVT_END_SWITCH
    //EVT_SET(LVar0, 0) // EVT_SET Attack
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_Attack_FakeoutScareB))
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_Attack_FakeoutScareA))
            EVT_GOTO(AVAL_EndTurn)
    EVT_END_SWITCH


    EVT_LABEL(AVAL_EndTurn)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Scare_Phase1Attacks) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(RandInt, 100, LVar1)
    EVT_SWITCH(LVar1)
        EVT_CASE_LT(70)
            EVT_SET(LVar0, 0)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 1)
    EVT_END_SWITCH
    //EVT_SET(LVar0, 0) // EVT_SET Attack
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_Attack_Scare))
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_Attack_FakeoutScare))
            EVT_GOTO(AVAL_EndTurn)
    EVT_END_SWITCH
    EVT_LABEL(AVAL_EndTurn)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_CrownMagic_Phase1Attacks) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(RandInt, 100, LVar1)
    EVT_SWITCH(LVar1)
        EVT_CASE_LT(60)
            EVT_SET(LVar0, 0)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 1)
    EVT_END_SWITCH
    //EVT_SET(LVar0, 1) // EVT_SET Attack
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_Attack_Fireball))
            EVT_GOTO(AVAL_EndTurn)
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_Attack_Lightning))
            EVT_GOTO(AVAL_EndTurn)
    EVT_END_SWITCH
    EVT_LABEL(AVAL_EndTurn)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Attack_Scare) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
	EVT_WAIT(20)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
	EVT_CALL(SetGoalToTarget, ACTOR_SELF)
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_ADD(LVar0, 20)
	EVT_SET(LVar1, 0)
	EVT_CALL(SetBattleCamTarget, LVar0, LVar1, LVar2)
	EVT_CALL(SetBattleCamZoom, 350)
	EVT_CALL(SetBattleCamOffsetZ, 45)
	EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetGoalToTarget, ACTOR_SELF )
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_ADD(LVar0, 25)
	EVT_SET(LVar1, 10)
	EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Scare)
	EVT_WAIT(30)
	EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
	EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
			EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
				EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
			EVT_END_IF
			EVT_GOTO(AVAL_SkipDamage)
		EVT_END_CASE_GROUP
	EVT_END_SWITCH
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
	EVT_WAIT(5)
	EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_SCARE, BS_FLAGS1_TRIGGER_EVENTS) // 3 Damage
	EVT_LABEL(AVAL_SkipDamage)
	EVT_WAIT(30)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(10)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetGoalToHome, ACTOR_SELF)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Attack_FakeoutScare) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
        EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
	EVT_WAIT(20)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
	EVT_CALL(SetGoalToTarget, ACTOR_SELF)
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_ADD(LVar0, 20)
	EVT_SET(LVar1, 0)
	EVT_CALL(SetBattleCamTarget, LVar0, LVar1, LVar2)
	EVT_CALL(SetBattleCamZoom, 350)
	EVT_CALL(SetBattleCamOffsetZ, 45)
	EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetGoalToTarget, ACTOR_SELF )
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_ADD(LVar0, 25)
	EVT_SET(LVar1, 10)
	EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP

	EVT_THREAD
		EVT_WAIT(15)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 1)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 1)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 2)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 2)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 3)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 3)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
	EVT_END_THREAD

	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Fakeout)
	EVT_WAIT(40)

	// Wiggle a little bit
	EVT_THREAD
		EVT_WAIT(15)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 1)
		EVT_CALL(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 1)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB (LVarD, 2)
		EVT_CALL(SetActorPos, ACTOR_SELF,  LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 2)
		EVT_CALL(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 3)
		EVT_CALL(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_ADD(LVarD, 3)
		EVT_CALL(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_WAIT(2)
		EVT_CALL(GetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
		EVT_SUB(LVarD, 4)
		EVT_CALL(SetActorPos, ACTOR_SELF, LVarD, LVarE, LVarF)
	EVT_END_THREAD
	EVT_WAIT(30)
	EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
	EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
			EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
				EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
			EVT_END_IF
			EVT_GOTO(AVAL_SkipDamage)
		EVT_END_CASE_GROUP
	EVT_END_SWITCH
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
	EVT_WAIT(5)
	EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_SCARE, BS_FLAGS1_TRIGGER_EVENTS) // 3 Damage
	EVT_LABEL(AVAL_SkipDamage)
	EVT_WAIT(30)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(10)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetGoalToHome, ACTOR_SELF)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

#include "common/CalculateArcsinDeg.inc.c"

#include "common/UnkBackgroundFunc3.inc.c"

#include "common/SetBackgroundAlpha.inc.c"

EvtScript N(EVS_Attack_Fireball) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
	EVT_CALL(N(UnkBackgroundFunc3))
    EVT_CALL(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    EVT_LABEL(0)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(0)
        EVT_END_IF
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	EVT_WAIT(50)
    EVT_CALL( SetAnimation, ACTOR_SELF, PRT_FIREBALL, ANIM_KingBoo_FireBall)
    EVT_WAIT(15)
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar1, 30)
	EVT_ADD(LVar2, 2)
    EVT_CALL(SetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2)
    EVT_CALL(SetPartScale, ACTOR_SELF, PRT_FIREBALL, EVT_FLOAT(1.0), EVT_FLOAT(1.0), EVT_FLOAT(1.0))
	EVT_CALL(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, 0)
    EVT_CALL(SetPartJumpGravity, ACTOR_SELF, PRT_FIREBALL, EVT_FLOAT(3.0))
    EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, FALSE)
	EVT_CALL(MakeLerp, 200, 0, 60, EASING_LINEAR)
    EVT_LABEL(2)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(2)
        EVT_END_IF
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar3, DAMAGE_TYPE_NO_CONTACT, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    EVT_SWITCH(LVar3)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_ADD(LVar1, -32) // Target mario's feet
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PETIT_PIRANHA_DIVE)
			EVT_THREAD
				EVT_CALL(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar1, LVar2, LVar0)
			   EVT_SET(LVar0,  0)
				EVT_LOOP(16)
					EVT_CALL(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar4, LVar5, LVar6)
					EVT_CALL(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
					EVT_CALL(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, LVar0)
					EVT_SET(LVar1, LVar4)
					EVT_SET(LVar2, LVar5)
					EVT_SET(LVar3, LVar6)
					EVT_WAIT(1)
				EVT_END_LOOP
			EVT_END_THREAD
            EVT_CALL(JumpPartTo, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2, 15, TRUE)
            EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            EVT_WAIT(2)
        EVT_END_CASE_GROUP
        EVT_CASE_DEFAULT
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PETIT_PIRANHA_DIVE)
			EVT_THREAD
				EVT_CALL(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar1, LVar2, LVar0)
			    EVT_SET(LVar0,  0)
				EVT_LOOP(16)
					EVT_CALL(GetPartPos, ACTOR_SELF, PRT_FIREBALL, LVar4, LVar5, LVar6)
					EVT_CALL(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
					EVT_CALL(SetPartRotation, ACTOR_SELF, PRT_FIREBALL, 0, 0, LVar0)
					EVT_SET(LVar1, LVar4)
					EVT_SET(LVar2, LVar5)
					EVT_SET(LVar3, LVar6)
					EVT_WAIT(1)
				EVT_END_LOOP
			EVT_END_THREAD
            EVT_CALL(JumpPartTo, ACTOR_SELF, PRT_FIREBALL, LVar0, LVar1, LVar2, 15, TRUE)
            EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_FIREBALL, ACTOR_PART_FLAG_INVISIBLE, TRUE)
            EVT_WAIT(2)
            EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_FIRE | DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_FIREBALL, BS_FLAGS1_TRIGGER_EVENTS) // 4 Damage
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
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
	EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
	EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
	EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
	EVT_CALL(N(UnkBackgroundFunc3))
    EVT_CALL(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    EVT_LABEL(0)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(0)
        EVT_END_IF
	EVT_WAIT(10)
	// Animation here
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	EVT_WAIT(55)
	EVT_CALL(StartRumble, BTL_RUMBLE_HIT_EXTREME)
	EVT_CALL(ShakeCam, CAM_BATTLE, 0, 5, EVT_FLOAT(1.0))
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_LIGHTNING_STRIKE)
	EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
	EVT_SWITCH(LVar0)
		EVT_CASE_OR_EQ(HIT_RESULT_MISS)
		EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
			EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
				EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
				EVT_CALL(RandInt, 40, LVar1)
				EVT_SUB(LVar0, LVar1)
				EVT_SET(LVar1, 200)
				EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
				EVT_ADD(LVar3, 30)
				EVT_SET(LVar4, 0)
                EVT_PLAY_EFFECT(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, EVT_FLOAT(0.5), 12, 0)
				EVT_CALL(N(SetBoltColors), LVarF)
				EVT_WAIT(12)
				EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                EVT_ADD(LVar1, 20)
                //EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
                EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
                EVT_PLAY_EFFECT(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
                EVT_WAIT(10)
                EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_GetAngry)
                EVT_WAIT(35)
			EVT_END_IF
			EVT_GOTO(AVAL_ReturnHome)
	EVT_END_SWITCH
	// Damage Mario
	EVT_CALL(SetGoalToTarget, ACTOR_SELF)
	EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
	EVT_CALL(RandInt, 40, LVar1)
	EVT_ADD(LVar0, LVar1)
	EVT_ADD(LVar0, 50)
	EVT_SET(LVar1, 200)
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
	EVT_SET(LVar4, 0)
    EVT_PLAY_EFFECT(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, EVT_FLOAT(1.5), 12, 0)
	EVT_CALL(N(SetBoltColors), LVarF)
	EVT_WAIT(12)
	EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, (DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_SHOCK | DAMAGE_TYPE_NO_CONTACT), 0, SUPPRESS_EVENT_FLAG_10000, DMG_LIGHTNING, BS_FLAGS1_TRIGGER_EVENTS) // 5 Damage
	// Return home
	EVT_LABEL(AVAL_ReturnHome)
    EVT_CALL(MakeLerp, 200, 0, 60, EASING_LINEAR)
    EVT_LABEL(2)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(2)
        EVT_END_IF
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
	EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
	EVT_RETURN
	EVT_END
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
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Init_Clone) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(EVS_Clone_Dummy)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(EVS_Clone_Dummy)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(EVS_Clone_Dummy)))
    EVT_RETURN
    EVT_END
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
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Phase, LVar6)
	EVT_IF_EQ(LVar6, 1)
		// Boo 1
		EVT_CALL(SetNpcPos, 1, 0, 0, -125)
        EVT_CALL(PlaySoundAtNpc, SOUND_BOO_VANISH_A, SOUND_SPACE_DEFAULT)
        EVT_SETF(LVar0, 0) // ALPHA
        EVT_CALL(SetNpcRenderMode, 1, RENDER_MODE_SURFACE_XLU_LAYER1)
	    EVT_LOOP(8)
		    EVT_ADD(LVar0, 16)
		    EVT_CALL(SetNpcImgFXParams, 1, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
		    EVT_WAIT(1)
	    EVT_END_LOOP
		EVT_CALL(SetNpcAnimation, 1, ANIM_KingBoo_BooWellMany)

		/* Boo 2
		EVT_CALL(SetNpcPos, 2, 5, -200, -125)
		EVT_CALL(SetNpcAnimation, 2, ANIM_KingBoo_BooLaugh)
		EVT_CALL(NpcFlyTo, 2, 5, 300, -125, 20, 0, EASING_COS_IN_OUT)
		// Boo 3
		EVT_CALL(SetNpcPos, 3, -10, -200, -125)
		EVT_CALL(SetNpcAnimation, 3, ANIM_KingBoo_BooLaugh)
		EVT_CALL(NpcFlyTo, 3, -10, 300, -125, 20, 0, EASING_COS_IN_OUT)
	    // Boo 4
		EVT_CALL(SetNpcPos, 4, 10, -200, -125)
		EVT_CALL(SetNpcAnimation, 4, ANIM_KingBoo_BooLaugh)
		EVT_CALL(NpcFlyTo, 4, 10, 300, -125, 20, 0, EASING_COS_IN_OUT)
		// Boo 5
		EVT_CALL(SetNpcPos, 5, -5, -200, -125)
		EVT_CALL(SetNpcAnimation, 5, ANIM_KingBoo_BooLaugh)
		EVT_CALL(NpcFlyTo, 5, -5, 300, -125, 20, 0, EASING_COS_IN_OUT)
	    // Boo 6
		EVT_CALL(SetNpcPos, 6, 0, -200, -125)
		EVT_CALL(SetNpcAnimation, 6, ANIM_KingBoo_BooLaugh)
		EVT_CALL(NpcFlyTo, 6, 0, 300, -125, 20, 0, EASING_COS_IN_OUT)
		*/
	EVT_END_IF
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_BooAbsorb)
	EVT_WAIT(50)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_BooAbsorbEnd)
	EVT_WAIT(20)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar3, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar3, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar3)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(5)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)
	//EVT_CALL(SetNpcAnimation, 1, ANIM_KingBoo_BooWellSingle )
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_IllusoryClones) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	EVT_WAIT(70)
	EVT_EXEC_WAIT(N(EVS_BooFlood))
	EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, TRUE)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, TRUE)
	EVT_SET(LVar0, 0)
	EVT_CALL(GetActorHP, ACTOR_SELF, LVarA)
	EVT_CALL(SummonEnemy, EVT_PTR(N(CloneFormation)), FALSE)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	EVT_CALL(SetPartEventBits, LVar0, PRT_MAIN, ACTOR_EVENT_FLAG_ILLUSORY, TRUE)
	EVT_CALL(SetEnemyHP, LVar0, LVarA)
	EVT_CALL(SummonEnemy, EVT_PTR(N(CloneFormation)), FALSE)
	EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	EVT_CALL(SetPartEventBits, LVar0, PRT_MAIN, ACTOR_EVENT_FLAG_ILLUSORY, TRUE)
	EVT_CALL(SetEnemyHP, LVar0, LVarA)

	// King Boo
	EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 1 Vanish
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
	EVT_SETF(LVar3, 0)
	EVT_CALL(SetPartAlpha, LVarA, PRT_MAIN, LVar3)
	EVT_CALL(SetActorPos, LVarA, LVar0, LVar1, LVar2)
	EVT_CALL(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW, TRUE)

    // Clone 2 Vanish
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarA)
	EVT_SETF(LVar3, 0)
	EVT_CALL(SetPartAlpha, LVarA, PRT_MAIN, LVar3)
	EVT_CALL(SetActorPos, LVarA, LVar0, LVar1, LVar2)
	EVT_WAIT(1)
	EVT_CALL(SetActorFlagBits, LVarA, ACTOR_FLAG_NO_SHADOW, TRUE)

	EVT_EXEC_WAIT(N(EVS_ClonePosition))

	// King Boo
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, ACTOR_SELF)

	// Clone 1
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
	EVT_CALL(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, LVarA)

	// Clone 2
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarA)
	EVT_CALL(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, LVarA)

	// King Boo Appears
	EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
	EVT_CALL(MoveBattleCamOver, 20)
	//EVT_CALL(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, EVT_PRT(N(LaughAnims)))
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Laugh)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_JUMP_SCARE)
	EVT_SETF(LVar3, 256)
	EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar3)
	EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 1 Appears
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, FALSE)
	EVT_CALL(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_Laugh )
	EVT_CALL(PlaySoundAtActor, LVar0, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar3, 256)
	EVT_CALL(SetPartAlpha, LVar0, PRT_MAIN, LVar3)
	EVT_CALL(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_SHADOW, TRUE)

	// Clone 2 Appears
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, FALSE)
	EVT_CALL(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_Laugh)
	EVT_CALL(PlaySoundAtActor, LVar0, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar3, 256)
	EVT_CALL(SetPartAlpha, LVar0, PRT_MAIN, LVar3)
	EVT_CALL(SetActorFlagBits, LVar0, ACTOR_FLAG_NO_SHADOW, TRUE)

	EVT_WAIT(15)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, TRUE)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, TRUE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ClonePosition) = {
	EVT_CALL(RandInt, 1000, LVar0)
    EVT_MOD(LVar0, 3)
	//EVT_SET(LVar0, 0) // To see the Position
    EVT_SWITCH(LVar0)
		EVT_CASE_EQ(0)
            EVT_SET(LVarA, ACTOR_SELF)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarB)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarC)
        EVT_CASE_EQ(1)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            EVT_SET(LVarB, ACTOR_SELF)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarC)
		EVT_CASE_EQ(2)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVarA)
            EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVarB)
            EVT_SET(LVarC, ACTOR_SELF)
	EVT_END_SWITCH
    EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
    EVT_CALL(MoveBattleCamOver, 150)

	// LVarA
	EVT_CALL(GetActorPos, LVarA, LVar0, LVar1, LVar2)
	EVT_SET(LVar0, 20)
	EVT_SET(LVar2, 5)
	EVT_CALL(SetActorPos, LVarA, LVar0, LVar1, LVar2)

	// LVarB
	EVT_CALL(GetActorPos, LVarB, LVar0, LVar1, LVar2)
	EVT_SET(LVar0, 70)
	EVT_SET(LVar2, 5)
	EVT_CALL(SetActorPos, LVarB, LVar0, LVar1, LVar2)

	// LVarC
	EVT_CALL(GetActorPos, LVarC, LVar0, LVar1, LVar2)
	EVT_SET(LVar0, 120)
	EVT_SET(LVar2, 5)
	EVT_CALL(SetActorPos, LVarC, LVar0, LVar1, LVar2)

    EVT_WAIT(15)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Attack_FakeoutScareA) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    EVT_SETF(LVar0, 256)
    EVT_LOOP(16)
        EVT_SUB(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    EVT_WAIT(20)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 20)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetBattleCamTarget, LVar0, LVar1, LVar2)
	EVT_CALL(SetBattleCamZoom, 350)
	EVT_CALL(SetBattleCamOffsetZ, 45)
	EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	EVT_CALL(MoveBattleCamOver, 20)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 40)
    EVT_SET(LVar1, 10)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
    EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_SETF(LVar0, 0)
    EVT_LOOP(16)
        EVT_ADD(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    // randomized delay
    EVT_CALL(RandInt, 20, LVar0)
    EVT_WAIT(LVar0)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_DoubleScareFakeoutA)
    EVT_WAIT(55)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_WAIT(60)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EVT_END_IF
            EVT_GOTO(AVAL_SkipDamage)
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
    EVT_WAIT(5)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT, 0, 0, DMG_FAKEOUT_SCARE_A, BS_FLAGS1_TRIGGER_EVENTS) // 4 Damage
    // EVT_CALL(PlaySoundAtPart, ACTOR_SELF PRT_BOO SOUND_BOO_VANISH_A)
    EVT_LABEL(AVAL_SkipDamage)
    EVT_WAIT(45)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    EVT_SETF(LVar0, 256)
    EVT_LOOP(16)
        EVT_SUB(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_WAIT(10)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
    EVT_CALL(MoveBattleCamOver, 20)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
    EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
    EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(HPBarToHome, ACTOR_SELF)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_SETF(LVar0, 0)
    EVT_LOOP(16)
        EVT_ADD(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_RETURN
    EVT_END
};
EvtScript N(EVS_Attack_FakeoutScareB) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    EVT_SETF(LVar0, 256)
    EVT_LOOP(16)
        EVT_SUB(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    EVT_WAIT(20)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 20)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetBattleCamTarget, LVar0, LVar1, LVar2)
	EVT_CALL(SetBattleCamZoom, 350)
	EVT_CALL(SetBattleCamOffsetZ, 45)
	EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
	EVT_CALL(MoveBattleCamOver, 20)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 45)
    EVT_SET(LVar1, 10)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
    EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 0, EASING_COS_IN_OUT)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_SETF(LVar0, 0)
    EVT_LOOP(16)
        EVT_ADD(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    // randomized delay
    EVT_CALL(RandInt, 20, LVar0)
    EVT_WAIT(LVar0)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_DoubleScareFakeoutB)
    EVT_WAIT(50)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_WAIT(30)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EVT_END_IF
            EVT_GOTO(AVAL_SkipDamage)
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_SET(LVar0, -130)
    EVT_SET(LVar1, -2)
    EVT_CALL(SetPartPos, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(FlyPartTo, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2, 0, 0, EASING_COS_IN_OUT)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOOTLER_SPOOK)
    EVT_WAIT(5)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT | DAMAGE_TYPE_STATUS_ALWAYS_HITS, SUPPRESS_EVENT_ALL, DMG_STATUS_IGNORE_RES(STATUS_FLAG_SHRINK, 2), DMG_FAKEOUT_SCARE_B, BS_FLAGS1_TRIGGER_EVENTS) // 2 Damage
    // EVT_CALL(PlaySoundAtPart, ACTOR_SELF, PRT_BOO SOUND_BOO_VANISH_A)
    EVT_SET(LVar0, 0)
    EVT_SET(LVar1, 0)
    EVT_SET(LVar2, 0)
    EVT_CALL(SetPartPos, ACTOR_SELF, PRT_BOO, LVar0, LVar1, LVar2)
    EVT_LABEL(AVAL_SkipDamage)
    EVT_WAIT(45)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
    EVT_SETF(LVar0, 256)
    EVT_LOOP(16)
        EVT_SUB(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_WAIT(10)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
    EVT_CALL(MoveBattleCamOver, 20)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
    EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
    EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(HPBarToHome, ACTOR_SELF)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
    EVT_SETF(LVar0, 0)
    EVT_LOOP(16)
        EVT_ADD(LVar0, 16)
        EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Attack_BoostedLightning) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_EXEC_WAIT(N(EVS_Move_Buff))
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(10)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, ACTOR_SELF)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
	EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
	EVT_CALL(N(UnkBackgroundFunc3))
    EVT_CALL(MakeLerp, 0, 200, 60, EASING_COS_IN_OUT)
    EVT_LABEL(0)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(0)
        EVT_END_IF
	EVT_WAIT(10)
	// Animation here
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_SPELL_CAST4)
	EVT_WAIT(55)
	EVT_CALL(StartRumble, BTL_RUMBLE_PLAYER_MAX)
	EVT_CALL(ShakeCam, CAM_BATTLE, 0, 5, EVT_FLOAT(2.0))
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_LIGHTNING_STRIKE)
	EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
	EVT_SWITCH(LVar0)
		EVT_CASE_OR_EQ(HIT_RESULT_MISS)
		EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
			EVT_IF_EQ(LVar0, HIT_RESULT_LUCKY)
				EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
				EVT_CALL(RandInt, 40, LVar1)
				EVT_SUB(LVar0, LVar1)
				EVT_SET(LVar1, 200)
				EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
				EVT_ADD(LVar3, 30)
				EVT_SET(LVar4, 0)
                EVT_PLAY_EFFECT(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, EVT_FLOAT(1.0), 12, 0)
				EVT_CALL(N(SetBoltColors), LVarF)
				EVT_WAIT(12)
				EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                EVT_ADD(LVar1, 20)
                //EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
                EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_EMOTE_IDEA)
                EVT_PLAY_EFFECT(EFFECT_EMOTE, EMOTE_EXCLAMATION, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0)
                EVT_WAIT(10)
                EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_GetAngry)
                EVT_WAIT(35)
			EVT_END_IF
			EVT_GOTO(AVAL_ReturnHome)
	EVT_END_SWITCH
	// Damage Mario
	EVT_CALL(SetGoalToTarget, ACTOR_SELF)
	EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
	EVT_CALL(RandInt, 40, LVar1)
	EVT_ADD(LVar0, LVar1)
	EVT_ADD(LVar0, 50)
	EVT_SET(LVar1, 200)
	EVT_CALL(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
	EVT_SET(LVar4, 0)
    EVT_PLAY_EFFECT(EFFECT_LIGHTNING_BOLT, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, EVT_FLOAT(2.5), 12, 0)
	EVT_CALL(N(SetBoltColors), LVarF)
	EVT_WAIT(12)
	EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, (DAMAGE_TYPE_MAGIC | DAMAGE_TYPE_SHOCK | DAMAGE_TYPE_NO_CONTACT), 0, SUPPRESS_EVENT_FLAG_10000, DMG_BOOSTED_LIGHTNING, BS_FLAGS1_TRIGGER_EVENTS) // 5 Damage
	// Return home
	EVT_LABEL(AVAL_ReturnHome)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, ACTOR_SELF)
    EVT_CALL(MakeLerp, 200, 0, 60, EASING_LINEAR)
    EVT_LABEL(2)
        EVT_CALL(UpdateLerp)
        EVT_CALL(N(SetBackgroundAlpha), LVar0)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(2)
        EVT_END_IF
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Move_Heal) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_EXEC_WAIT(N(EVS_Move_Buff))
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_VANISH_A)
	EVT_SETF(LVar0, 256)
	EVT_LOOP(16)
		EVT_SUB(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_WAIT(10)
	EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
	EVT_CALL(MoveBattleCamOver, 20)
	EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(10.0))
	EVT_CALL(SetGoalPos, ACTOR_SELF, 70, 50, 5)
	EVT_CALL(FlyToGoal, ACTOR_SELF, 30, 0, EASING_COS_IN_OUT)
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_CALL(HPBarToHome, ACTOR_SELF)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_BOO_APPEAR_A)
	EVT_SETF(LVar0, 0)
	EVT_LOOP(16)
		EVT_ADD(LVar0, 16)
		EVT_CALL(SetPartAlpha, ACTOR_SELF, PRT_MAIN, LVar0)
		EVT_WAIT(1)
	EVT_END_LOOP
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Idle)
	EVT_THREAD
		EVT_WAIT(5)
		EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_RECOVER_HEART)
		EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_HEART_BOUNCE)
		EVT_WAIT(30)
		EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_STAR_BOUNCE_A)
	EVT_END_THREAD
	EVT_THREAD
		EVT_CALL(FreezeBattleState, TRUE)
		EVT_CALL(HealActor, ACTOR_SELF, 10, FALSE)
		EVT_CALL(FreezeBattleState, FALSE)
	EVT_END_THREAD
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Move_Buff) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, FALSE)
	EVT_CALL(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, LVar0, SOUND_SPELL_CAST4)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, FALSE)
	EVT_CALL(SetAnimation, LVar0, PRT_MAIN, ANIM_KingBoo_CrownAttack)
	EVT_CALL(PlaySoundAtActor, LVar0, SOUND_SPELL_CAST4)
	EVT_WAIT(80)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, TRUE)
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar0)
	EVT_CALL(UseIdleAnimation, LVar0, TRUE)
	EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_POWER_UP)
	EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
	EVT_ADD(LVar1, 20)
	EVT_PLAY_EFFECT(EFFECT_ENERGY_IN_OUT, 6, LVar0, LVar1, LVar2, EVT_FLOAT(1.0), 45, 0)
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Laugh)
	EVT_WAIT(30)
	// Clone 1
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone1Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone1_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF
	// Clone 2
	EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
	EVT_CALL(ActorExists, LVar9, LVarA)
	EVT_IF_EQ(LVarA, TRUE)
		EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2Exists, LVarB)
		EVT_IF_EQ(LVarB, TRUE)
			EVT_CALL(SetActorVar, ACTOR_SELF, AVAR_Clone2Exists, FALSE)
			EVT_CALL(GetActorVar, ACTOR_SELF, AVAR_Clone2_ID, LVar9)
			EVT_EXEC(N(EVS_RemoveClone))
		EVT_END_IF
	EVT_END_IF
	EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_KingBoo_Hide)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};
