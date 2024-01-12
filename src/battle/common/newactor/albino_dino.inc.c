#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "effects.h"
#include "sprite/npc/AlbinoDino.h"

#define NAMESPACE A(albino_dino)

enum N(ActorPartIDs) {
    PRT_MAIN     = 1,
};

enum N(ActorParams) {
    DMG_TACKLE              = 6,
    DMG_TACKLEPARTNER       = 3,
};

extern EvtScript N(EVS_Init);
extern s32 N(DefaultAnims)[];
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_AddWalkQuakeFX);
extern EvtScript N(EVS_Attack_TackleCharge);
extern EvtScript N(EVS_Attack_FireBreath);

s32 N(DefaultAnimations)[] = {
    STATUS_KEY_NORMAL, ANIM_AlbinoDino_Idle,
    STATUS_KEY_STONE, ANIM_AlbinoDino_Still,
    STATUS_KEY_SLEEP, ANIM_AlbinoDino_Idle,
    STATUS_KEY_POISON, ANIM_AlbinoDino_Idle,
    STATUS_KEY_STOP, ANIM_AlbinoDino_Still,
    STATUS_KEY_STATIC, ANIM_AlbinoDino_Idle,
    STATUS_KEY_PARALYZE, ANIM_AlbinoDino_Still,
    STATUS_KEY_DIZZY, ANIM_AlbinoDino_Still,
    STATUS_KEY_FEAR, ANIM_AlbinoDino_Still,
    STATUS_END,
};

s32 N(DefenseTable)[] = {
    ELEMENT_NORMAL, 0,
    ELEMENT_FIRE, 99,
    ELEMENT_WATER, 99,
    ELEMENT_ICE, 99,
    ELEMENT_BLAST, 99,
    ELEMENT_SHOCK, 99,
    ELEMENT_MAGIC, 99,
    ELEMENT_COSMIC, 99,
    ELEMENT_END,
};

s32 N(StatusTable)[] = {
    STATUS_KEY_NORMAL, 100,
    STATUS_KEY_DEFAULT, 0,
    STATUS_KEY_SLEEP, 0,
    STATUS_KEY_POISON, 0,
    STATUS_KEY_FROZEN, 0,
    STATUS_KEY_DIZZY, 0,
    STATUS_KEY_FEAR, 0,
    STATUS_KEY_STATIC, 0,
    STATUS_KEY_PARALYZE, 0,
    STATUS_KEY_SHRINK, 0,
    STATUS_KEY_STOP, 0,
    STATUS_TURN_MOD_DEFAULT, 0,
    STATUS_TURN_MOD_SLEEP, 0,
    STATUS_TURN_MOD_POISON, 0,
    STATUS_TURN_MOD_FROZEN, 0,
    STATUS_TURN_MOD_DIZZY, 0,
    STATUS_TURN_MOD_FEAR, 0,
    STATUS_TURN_MOD_STATIC, 0,
    STATUS_TURN_MOD_PARALYZE, 0,
    STATUS_TURN_MOD_SHRINK, 0,
    STATUS_TURN_MOD_STOP, 0,
    STATUS_END,
};

ActorPartBlueprint N(ActorParts)[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -9, 46 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnimations),
        .defenseTable = N(DefenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { -6, -17 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = 0,
    .type = ACTOR_TYPE_ALBINO_DINO,
    .level = 23,
    .maxHP = 15,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init),
    .statusTable = N(StatusTable),
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 64, 56 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 24 },
    .statusTextOffset = { 11, 40 },
};

EvtScript N(EVS_Init) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(EVS_TakeTurn)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(EVS_Idle)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(EVS_HandleEvent)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Idle) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(returnHome) = {
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Run)
    EVT_CALL(SetGoalToHome, ACTOR_SELF)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(12.0))
    EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HandleEvent) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, FALSE)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(EVENT_HIT_COMBO)
        EVT_CASE_OR_EQ(EVENT_HIT)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_SPIN_SMASH_HIT)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_SpinSmashHit)
        EVT_CASE_EQ(EVENT_SPIN_SMASH_DEATH)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_SpinSmashHit)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_HurtStill)
            EVT_EXEC_WAIT(EVS_Enemy_Death)
            EVT_RETURN
        EVT_CASE_OR_EQ(EVENT_ZERO_DAMAGE)
        EVT_CASE_OR_EQ(EVENT_IMMUNE)
        EVT_CASE_OR_EQ(EVENT_AIR_LIFT_FAILED)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_NoDamageHit)
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_DEATH)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_HurtStill)
            EVT_EXEC_WAIT(EVS_Enemy_Death)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_RECOVER_STATUS)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_Recover)
        EVT_CASE_EQ(EVENT_SCARE_AWAY)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Run)
            EVT_SET_CONST(LVar2, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_ScareAway)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_BEGIN_AIR_LIFT)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Run)
            EVT_EXEC_WAIT(EVS_Enemy_AirLift)
        EVT_CASE_EQ(EVENT_BLOW_AWAY)
            EVT_SET_CONST(LVar0, PRT_MAIN)
            EVT_SET_CONST(LVar1, ANIM_AlbinoDino_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_BlowAway)
            EVT_RETURN
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_AddWalkQuakeFX) = {
    EVT_SET(LVarA, 0)
    EVT_LABEL(0)
        EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_CALL(GetActorYaw, ACTOR_SELF, LVar3)
        EVT_IF_EQ(LVar3, 0)
            EVT_ADD(LVar0, 20)
        EVT_ELSE
            EVT_ADD(LVar0, -20)
        EVT_END_IF
        EVT_PLAY_EFFECT(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 25, 8, 45, 20, 0)
        EVT_IF_GT(LVarA, 3)
            EVT_CALL(ShakeCam, CAM_BATTLE, 0, 2, EVT_FLOAT(0.2))
            EVT_SET(LVarA, 0)
        EVT_END_IF
        EVT_ADD(LVarA, 1)
        EVT_WAIT(2)
        EVT_GOTO(0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_TakeTurn) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, FALSE)
    EVT_CALL(RandInt, 100, LVar0)
    EVT_IF_LT(LVar0, 50)
        EVT_EXEC_WAIT(N(EVS_Attack_TackleCharge))
    EVT_ELSE
        EVT_EXEC_WAIT(N(EVS_Attack_FireBreath))
    EVT_END_IF
    EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Attack_TackleCharge) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, FALSE)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
    EVT_EXEC_GET_TID(N(EVS_AddWalkQuakeFX), LVar9)
    EVT_THREAD
        EVT_LOOP(3)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_ALBINO_DINO_STEP_A)
            EVT_WAIT(4)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_ALBINO_DINO_STEP_B)
            EVT_WAIT(4)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Run)
    EVT_WAIT(20)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    EVT_SWITCH(LVarF)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_THREAD
                EVT_CALL(SetGoalToTarget, ACTOR_SELF)
                //EVT_CALL(AddGoalPos, ACTOR_SELF, -100, 0, 0)
                EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(12.0))
//                EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
            EVT_END_THREAD
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_12)
            EVT_WAIT(15)
            EVT_IF_EQ(LVarF, HIT_RESULT_LUCKY)
                EVT_CALL(SetGoalToTarget, ACTOR_SELF)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
                EVT_CALL(SetGoalToTarget, ACTOR_SELF)
                EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                EVT_CALL(SetGoalPos, ACTOR_SELF, -240, 0, LVar2)
                EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
                EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_12)
                EVT_CALL(MoveBattleCamOver, 20)
                EVT_CALL(SetActorPos, ACTOR_SELF, 240, 0, LVar2)
                EVT_CALL(SetGoalToHome, ACTOR_SELF)
                EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
                EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Run)
                EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
                EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
                EVT_RETURN
                EVT_END_CASE_GROUP
            EVT_END_IF
            EVT_WAIT(40)
            EVT_CALL(YieldTurn)
            EVT_EXEC_WAIT(N(returnHome))
            EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
            EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
            EVT_RETURN
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetStatusFlags, ACTOR_SELF, LVarA)
    EVT_IF_FLAG(LVarA, STATUS_FLAG_SHRINK)
        EVT_CALL(AddGoalPos, ACTOR_SELF, 12, 0, 0)
    EVT_ELSE
        EVT_CALL(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    EVT_END_IF
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(12.0))
    EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
    EVT_THREAD
        EVT_CALL(ShakeCam, CAM_BATTLE, 0, 4, EVT_FLOAT(1.5))
    EVT_END_THREAD
    EVT_KILL_THREAD(LVar9)
    EVT_WAIT(2)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_ICE, SUPPRESS_EVENT_ALL, DMG_STATUS_IGNORE_RES(STATUS_FLAG_FROZEN, 3), DMG_TACKLE, BS_FLAGS1_TRIGGER_EVENTS)
    EVT_SET(LVarA, 0)
    EVT_CALL(GetBattleFlags, LVar0)
    EVT_IF_NOT_FLAG(LVar0, BS_FLAGS1_ATK_BLOCKED)
        EVT_CALL(GetStatusFlags, ACTOR_PLAYER, LVar0)
        EVT_IF_NOT_FLAG(LVar0, STATUS_FLAG_STONE)
            EVT_SET(LVarA, 1)
        EVT_END_IF
    EVT_END_IF
    EVT_IF_NE(LVarA, 0)
        EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PARTNER)
        EVT_CALL(SetGoalToTarget, ACTOR_SELF)
        EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_ADD(LVar0, 32)
        EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(12.0))
        EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
        EVT_CALL(SetGoalToTarget, ACTOR_SELF)
        EVT_CALL(SetDamageSource, DMG_SRC_CRUSH_PARTNER)
        EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_ICE, SUPPRESS_EVENT_ALL, 0, DMG_TACKLEPARTNER, BS_FLAGS1_TRIGGER_EVENTS)
        EVT_CALL(GetBattleFlags, LVar0)
        EVT_IF_NOT_FLAG(LVar0, BS_FLAGS1_ATK_BLOCKED)
            EVT_CALL(SetGoalToTarget, ACTOR_SELF)
            EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(SetGoalPos, ACTOR_SELF, -240, 0, LVar2)
            EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
            EVT_CALL(SetActorPos, ACTOR_SELF, 240, 0, LVar2)
            EVT_CALL(SetGoalToHome, ACTOR_SELF)
            EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Run)
            EVT_WAIT(8)
            EVT_CALL(YieldTurn)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Idle)
            EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
            EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
            EVT_RETURN
        EVT_ELSE
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
            EVT_CALL(SetBattleCamTarget, -45, 60, 0)
            EVT_CALL(SetBattleCamZoom, 460)
            EVT_CALL(SetBattleCamOffsetZ, 0)
            EVT_CALL(MoveBattleCamOver, 30)
        EVT_END_IF
    EVT_END_IF
    EVT_SWITCH(LVarF)
        EVT_CASE_OR_EQ(HIT_RESULT_HIT)
        EVT_CASE_OR_EQ(HIT_RESULT_NO_DAMAGE)
            EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_ADD(LVar0, 40)
            EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(1.0))
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 15, FALSE, TRUE, FALSE)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_ALBINO_DINO_STEP_B)
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_AlbinoDino_Idle)
            EVT_WAIT(10)
            EVT_CALL(YieldTurn)
            EVT_EXEC_WAIT(N(returnHome))
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, TRUE)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

#include "common/SetBowserFireBreathScales.inc.c"

EvtScript N(EVS_Attack_FireBreath) = {
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetStatusFlags, ACTOR_SELF, LVar0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_19)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Walk)
//    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 100)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
    EVT_CALL(RunToGoal, ACTOR_SELF, 15, FALSE)
//    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//    EVT_SUB(LVar0, 30)
//    EVT_ADD(LVar1, 65)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_FireBreathStart)
    EVT_WAIT(27)
    EVT_CALL(SetBattleCamTarget, LVar0, LVar1, LVar2)
    EVT_CALL(SetBattleCamZoom, 400)
    EVT_CALL(MoveBattleCamOver, 40)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_FireBreath)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_12)
    EVT_CALL(MoveBattleCamOver, 55)
    EVT_ADD(LVar2, 20)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar3, LVar4, -100)
    EVT_WAIT(5)
//    EVT_SUB(LVar0, 50)
    EVT_SUB(LVar1, 15)
//    EVT_SUB(LVar2, 25)
    EVT_SUB(LVar3, 40)
    EVT_SUB(LVar4, 0)
    EVT_SUB(LVar5, 5)
    EVT_PLAY_EFFECT(EFFECT_FIRE_BREATH, 2, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 25, 1, 8, 0)
    EVT_CALL(N(SetBowserFireBreathScales), LVarF)
    EVT_THREAD
//        EVT_CALL(N(StartRumbleWithParams), 50, 148)
        EVT_CALL(PlaySound, SOUND_BOWSER_FIRE_BREATH_LOOP)
        EVT_WAIT(35)
        EVT_CALL(PlaySound, SOUND_BOWSER_FIRE_BREATH_LOOP | SOUND_ID_TRIGGER_CHANGE_SOUND)
    EVT_END_THREAD
    EVT_WAIT(10)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    EVT_SWITCH(LVarA)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_FireBreathEnd)
            EVT_WAIT(40)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Idle)
            EVT_WAIT(15)
            //EVT_EXEC_WAIT(N(onAttackMissed))
            EVT_IF_EQ(LVarA, HIT_RESULT_LUCKY)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EVT_END_IF
            EVT_WAIT(30)
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_WAIT(2)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVarF, DAMAGE_TYPE_FIRE, SUPPRESS_EVENT_ALL, 0, 6, BS_FLAGS1_TRIGGER_EVENTS)
    EVT_WAIT(15)
    EVT_SWITCH(LVarF)
        EVT_CASE_OR_EQ(HIT_RESULT_HIT)
        EVT_CASE_OR_EQ(HIT_RESULT_NO_DAMAGE)
            EVT_CALL(ClearStatusEffects, ACTOR_PLAYER)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_FireBreathEnd)
            EVT_WAIT(40)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_AlbinoDino_Idle)
            EVT_WAIT(15)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_12)
            EVT_CALL(YieldTurn)
            EVT_EXEC_WAIT(N(returnHome))
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};
