#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/jr_troopa.h"
#include "sprite/npc/para_jr_troopa.h"
#include "sprite/npc/mage_jr_troopa.h"
#include "sprite/npc/spark.h"
#include "message_ids.h"
#include "wua.h"

// TEMP XXX why is para_jr_troopa.h broken
#define _NPC_PALETTE_para_jr_troopa_default 0x00

#define NAMESPACE jr_troopa

enum { //jr troopa parts
    TROOPA_PART_MAGE = 1,
    TROOPA_PART_FLYING,
    TROOPA_PART_NORMAL,
};

enum { //actor variables
    VAR_FIRST_TIME_TALKING,
    VAR_TURNS_UNTIL_SECOND_PHASE,
    VAR_TROOPA_DAMAGE,
    VAR_TURNS_UNTIL_SPARK_FLY_AWAY,
    VAR_TROOPA_STATE,
};

PlayerData* playerData = &gPlayerData;
/*ApiStatus CreateNpc(Evt* script, s32 isInitialCall);
ApiStatus func_802535B4(Evt* script, s32 isInitialCall);
ApiStatus func_8027D32C(Evt* script, s32 isInitialCall);
ApiStatus func_80269E80(Evt* script, s32 isInitialCall);*/
extern s32 N(anims)[];
extern s32 N(anims_para)[];
extern s32 N(anims_normal)[];
extern s32 N(idleAnimations_80222C6C)[];
//extern s32 N(defense_table)[];
extern s32 N(status_table)[];
extern s32 N(defense_table)[];
extern ActorPartBlueprint N(parts)[];
extern EvtScript N(init);
extern EvtScript N(turn);
extern EvtScript N(idle);
extern EvtScript N(dispatch);
extern EvtScript N(dispatch_para);
extern EvtScript N(next_turn);
extern EvtScript N(spell_attack);
extern EvtScript N(spell_attack_flying);
extern EvtScript N(transform);
extern EvtScript N(802260AC);
extern EvtScript N(8022646C);
extern EvtScript N(lose_flying_mode);
extern EvtScript N(regular_attack);
extern EvtScript N(spark_fly_away);
extern EvtScript N(spark_fly_back);
extern EvtScript N(jr_troopa_defense_jab);
extern EvtScript N(troopa_dead);
extern EvtScript N(80222C78);

s32 N(defense_table)[] = {
    ELEMENT_NORMAL, 0,

    ELEMENT_END,
};

s32 N(status_table)[] = {
    STATUS_NORMAL, 0,
    STATUS_DEFAULT, 0,
    STATUS_SLEEP, 100,
    STATUS_POISON, 100,
    STATUS_FROZEN, 100,
    STATUS_DIZZY, 100,
    STATUS_FEAR, 100,
    STATUS_STATIC, 100,
    STATUS_PARALYZE, 100,
    STATUS_SHRINK, 100,
    STATUS_STOP, 100,

    STATUS_DEFAULT_TURN_MOD, 0,
    STATUS_SLEEP_TURN_MOD, 0,
    STATUS_POISON_TURN_MOD, 0,
    STATUS_FROZEN_TURN_MOD, 0,
    STATUS_DIZZY_TURN_MOD, 0,
    STATUS_FEAR_TURN_MOD, 0,
    STATUS_STATIC_TURN_MOD, 0,
    STATUS_PARALYZE_TURN_MOD, 0,
    STATUS_SHRINK_TURN_MOD, 0,
    STATUS_STOP_TURN_MOD, 0,

    STATUS_END,
};

ActorPartBlueprint N(parts)[] = {
    {
        .flags = ACTOR_PART_FLAG_MULTI_TARGET,
        .index = TROOPA_PART_MAGE,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 0xFF,
        .idleAnimations = N(anims),
        .defenseTable = N(defense_table),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1D = 246,
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = TROOPA_PART_FLYING,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 32 },
        .opacity = 255,
        .idleAnimations = N(anims_para),
        .defenseTable = N(defense_table),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1D = 246,
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = TROOPA_PART_NORMAL,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 0xFF,
        .idleAnimations = N(anims_normal),
        .defenseTable = N(defense_table),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1D = 246,
    },
};

ActorBlueprint NAMESPACE = {
    .flags = 0,
    .type = 136,
    .level = 41,
    .maxHP = 10,
    .partCount = ARRAY_COUNT(N(parts)),
    .partsData = N(parts),
    .script = &N(init),
    .statusTable = N(status_table),
    .escapeChance = 0,
    .airLiftChance = 0,
    .spookChance = 0,
    .baseStatusChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 24, 32 },
    .hpBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 30 },
    .statusMessageOffset = { 10, 20 },
};

s32 N(anims)[] = {
    STATUS_NORMAL,    NPC_ANIM_mage_jr_troopa_default_idle_u,
    STATUS_SLEEP,     NPC_ANIM_mage_jr_troopa_default_sleep,
    STATUS_STONE,     NPC_ANIM_mage_jr_troopa_default_still,
    STATUS_POISON,    NPC_ANIM_mage_jr_troopa_default_still,
    STATUS_STOP,      NPC_ANIM_mage_jr_troopa_default_still,
    STATUS_STATIC,    NPC_ANIM_mage_jr_troopa_default_still,
    STATUS_DIZZY,     NPC_ANIM_mage_jr_troopa_default_dizzy,
    STATUS_PARALYZE,  NPC_ANIM_mage_jr_troopa_default_still,
    STATUS_END,
};

s32 N(anims_para)[] = {
    STATUS_NORMAL,    NPC_ANIM_para_jr_troopa_Palette_00_idle_u,
    STATUS_SLEEP,     NPC_ANIM_para_jr_troopa_Palette_00_sleep,
    STATUS_STONE,     NPC_ANIM_para_jr_troopa_Palette_00_still,
    STATUS_POISON,    NPC_ANIM_para_jr_troopa_Palette_00_still,
    STATUS_STOP,      NPC_ANIM_para_jr_troopa_Palette_00_still,
    STATUS_STATIC,    NPC_ANIM_para_jr_troopa_Palette_00_still,
    STATUS_DIZZY,     NPC_ANIM_para_jr_troopa_Palette_00_dizzy,
    STATUS_PARALYZE,  NPC_ANIM_para_jr_troopa_Palette_00_still,
    STATUS_END,
};

s32 N(anims_normal)[] = {
    STATUS_NORMAL,    NPC_ANIM_jr_troopa_default_idle,
    STATUS_SLEEP,     NPC_ANIM_jr_troopa_default_sleep,
    STATUS_STONE,     NPC_ANIM_jr_troopa_default_still,
    STATUS_POISON,    NPC_ANIM_jr_troopa_default_still,
    STATUS_STOP,      NPC_ANIM_jr_troopa_default_still,
    STATUS_STATIC,    NPC_ANIM_jr_troopa_default_still,
    STATUS_DIZZY,     NPC_ANIM_jr_troopa_default_dizzy,
    STATUS_PARALYZE,  NPC_ANIM_jr_troopa_default_still,
    STATUS_END,
};

s32 N(idleAnimations_80222C6C)[] = {
    STATUS_NORMAL,    NPC_ANIM_jr_troopa_default_dead,
    STATUS_END,
};

EvtScript N(init) = SCRIPT({
    BindTakeTurn(ACTOR_SELF, N(turn));
    BindIdle(ACTOR_SELF, N(idle));
    BindHandleEvent(ACTOR_SELF, N(dispatch));
    BindNextTurn(ACTOR_SELF, N(next_turn));
    // Create spark
    CreateNpc(0, NPC_ANIM_spark_normal_idle_nb);
    SetNpcYaw(0, 90);
    SetNpcPos(0, -129, 16, -11);
    EnableNpcShadow(0, 1);
    //
    SetActorVar(ACTOR_SELF, VAR_FIRST_TIME_TALKING, 0); //first time talking
    SetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SECOND_PHASE, 1); //turns until second phase
    SetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE, 1); //jr troopa's damage
    SetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SPARK_FLY_AWAY, 1); //turns until spark flies away
    SetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, 0); //jr troopa's state: 0 = mage, 1 = flying, 2 = mage(weak)
});

EvtScript N(next_turn) = SCRIPT({
    GetActorVar(ACTOR_SELF, VAR_FIRST_TIME_TALKING, $b); //first time talking
    if($b == 0){
        UseIdleAnimation(ACTOR_SELF, 0);
        EnableIdleScript(ACTOR_SELF, 0);
        UseBattleCamPreset (13);
        SetBattleCamTarget (-114, 0, 0);
        SetBattleCamZoom (320);
        SetBattleCamOffsetZ (50);
        MoveBattleCamOver (20);
        SpeakToPlayer(
            0,
            NPC_ANIM_spark_normal_talk_neutral_nb,
            NPC_ANIM_spark_normal_idle_neutral_nb,
            0,
            MSG_prologue_jrtroopa_battle_1,
        );
        // ActorSpeak(
        //     MSG_prologue_jrtroopa_battle_2,
        //     ACTOR_SELF,
        //     1,
        //     NPC_ANIM(mage_jr_troopa, default, talk_point),
        //     NPC_ANIM(mage_jr_troopa, default, idle_point)
        // );
        //ActorSpeak(1900955, -127, EVT_VAR(0), -1, -1);

        SetActorVar(ACTOR_SELF, VAR_FIRST_TIME_TALKING, 1);
        UseIdleAnimation(ACTOR_SELF, 1);
        EnableIdleScript(ACTOR_SELF, 1);
        }
});

EvtScript N(idle) = SCRIPT({
    // GetActorVar(-127, 3, EVT_VAR(0));
    // 0;
    // match EVT_VAR(0) {
    //     == 2 {
    //         GetStatusFlags(-127, EVT_VAR(10));
    //         if (EVT_VAR(10) & 266240) {
    //             SetTargetOffset(-127, 2, -15, 28);
    //             func_8027D4C8(-127, 2, 4, -6);
    //             N(func_80218AD0_41FF10)(-25, 27, -1, 27);
    //         } else {
    //             SetTargetOffset(-127, 2, -8, 33);
    //             func_8027D4C8(-127, 2, 0, -6);
    //             N(func_80218AD0_41FF10)(-22, 30, 2, 28);
    //         }
    //     }
    //     else {
    //         N(func_80218AD0_41FF10)(-20, 35, 10, 25);
    //     }
    // }
    // sleep 1;
    // goto 0;
});


EvtScript N(dispatch) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    SetActorScale(ACTOR_SELF, 1.0, 1.0, 1.0);
    GetLastEvent(ACTOR_SELF, EVT_VAR(0));
    match EVT_VAR(0) {
        EVENT_HIT_COMBO, EVENT_HIT {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt_u;
            await DoNormalHit;
        }
        == EVENT_BURN_HIT {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_burn_hurt;
            EVT_VAR(2) = NPC_ANIM_mage_jr_troopa_default_burn_dead;
            await DoBurnHit;
        }
        == EVENT_BURN_DEATH {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_burn_hurt;
            EVT_VAR(2) = NPC_ANIM_mage_jr_troopa_default_burn_dead;
            await DoBurnHit;
            /*
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM(mage_jr_troopa, default, burn_dead);
            await DoDeath;
            */
            EVT_VAR(0) = 0x3;
            EVT_VAR(1) = 0x210013;
            await N(80222C78);
            return;
        }
        == EVENT_SPIN_SMASH_HIT {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt;
            await DoSpinSmashHit;
        }
        == EVENT_SPIN_SMASH_DEATH {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt;
            await DoSpinSmashHit;
            /*
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM(mage_jr_troopa, default, hurt);//dead
            await DoDeath;
            */
            EVT_VAR(0) = 0x3;
            EVT_VAR(1) = 0x210013;
            await N(80222C78);
            return;
        }
        == EVENT_SHOCK_HIT {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt; //There isn't a shock anim, will not be used anyways.
            await DoShockHit;
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt;
            await DoJumpBack;
            JumpToGoal(ACTOR_SELF, 5, 0, 1, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 2.0);
            SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_dizzy);
            SetGoalToHome(ACTOR_SELF);
            SetActorSpeed(ACTOR_SELF, 8.0);
            RunToGoal(ACTOR_SELF, 0, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 1.0);
            sleep 5;
            SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_idle_u);
            SetActorJumpGravity(ACTOR_SELF, 1.6);
            JumpToGoal(ACTOR_SELF, 5, 0, 1, 0);
        }
        == EVENT_SHOCK_DEATH {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt; //There isn't a shock anim, will not be used anyways.
            await DoShockHit;
            /*
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM(mage_jr_troopa, default, hurt);//dead
            await DoDeath;
            */
            EVT_VAR(0) = 0x3;
            EVT_VAR(1) = 0x210013;
            await N(80222C78);
            return;
        }
        == EVENT_STAR_BEAM, 23, EVENT_IMMUNE, EVENT_AIR_LIFT_FAILED {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_idle;
            await DoImmune;
        }
        == EVENT_DEATH {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt_u;
            await DoNormalHit;
            sleep 10;
            /*
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM(mage_jr_troopa, default, hurt_u);//dead
            await DoDeath;
            */
            await N(troopa_dead);
            EVT_VAR(0) = 0x1;
            EVT_VAR(1) = 0x210013;
            await N(80222C78);
            return;
        }
        == EVENT_END_FIRST_STRIKE {
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 2.0);
            SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_run);
            SetGoalToHome(ACTOR_SELF);
            SetActorSpeed(ACTOR_SELF, 4.0);
            RunToGoal(ACTOR_SELF, 0, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 1.0);
            HPBarToHome(ACTOR_SELF);
        }
        == EVENT_RECOVER_STATUS {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_idle;
            await DoRecover;
        }
        == EVENT_SCARE_AWAY {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_run;
            EVT_VAR(2) = NPC_ANIM_mage_jr_troopa_default_hurt;
            await DoScareAway;
            return;
        }
        == EVENT_BEGIN_AIR_LIFT {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_run;
            await DoAirLift;
        }
        == EVENT_BLOW_AWAY {
            EVT_VAR(0) = TROOPA_PART_MAGE;
            EVT_VAR(1) = NPC_ANIM_mage_jr_troopa_default_hurt;
            await DoBlowAway;
            return;
        } else {
        }
    }
    SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_idle);
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(dispatch_para) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    SetActorScale(ACTOR_SELF, 1.0, 1.0, 1.0);
    GetLastEvent(ACTOR_SELF, EVT_VAR(0));
    match EVT_VAR(0) {
        EVENT_HIT_COMBO, EVENT_HIT {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt_u;
            await DoNormalHit;
        }
        == EVENT_BURN_HIT {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_burn_hurt;
            EVT_VAR(2) = NPC_ANIM_para_jr_troopa_Palette_00_burn_dead;
            await DoBurnHit;
        }
        == EVENT_BURN_DEATH {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_burn_hurt;
            EVT_VAR(2) = NPC_ANIM_para_jr_troopa_Palette_00_burn_dead;
            await DoBurnHit;
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_burn_dead;
            await DoDeath;
            return;
        }
        == EVENT_SPIN_SMASH_HIT {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;
            await DoSpinSmashHit;
        }
        == EVENT_SPIN_SMASH_DEATH {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;
            await DoSpinSmashHit;
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;//dead
            await DoDeath;
            return;
        }
        == EVENT_SHOCK_HIT {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt; //There isn't a shock anim, will not be used anyways.
            await DoShockHit;
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;
            await DoJumpBack;
            JumpToGoal(ACTOR_SELF, 5, 0, 1, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 2.0);
            SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_para_jr_troopa_Palette_00_dizzy);
            SetGoalToHome(ACTOR_SELF);
            SetActorSpeed(ACTOR_SELF, 8.0);
            RunToGoal(ACTOR_SELF, 0, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_MAGE, 1.0);
            sleep 5;
            SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_para_jr_troopa_Palette_00_idle);
            SetActorJumpGravity(ACTOR_SELF, 1.6);
            JumpToGoal(ACTOR_SELF, 5, 0, 1, 0);
        }
        == EVENT_SHOCK_DEATH {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt; //There isn't a shock anim, will not be used anyways.
            await DoShockHit;
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;//dead
            await DoDeath;
            return;
        }
        == EVENT_STAR_BEAM, 23, EVENT_IMMUNE, EVENT_AIR_LIFT_FAILED {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_idle;
            await DoImmune;
        }
        == EVENT_DEATH {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt_u;
            await DoNormalHit;
            sleep 10;
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt_u;//dead
            await DoDeath;
            return;
        }
        == EVENT_END_FIRST_STRIKE {
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_FLYING, 2.0);
            SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM_para_jr_troopa_Palette_00_run);
            SetGoalToHome(ACTOR_SELF);
            SetActorSpeed(ACTOR_SELF, 4.0);
            RunToGoal(ACTOR_SELF, 0, 0);
            SetAnimationRate(ACTOR_SELF, TROOPA_PART_FLYING, 1.0);
            HPBarToHome(ACTOR_SELF);
        }
        == EVENT_RECOVER_STATUS {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_idle;
            await DoRecover;
        }
        == EVENT_SCARE_AWAY {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_run;
            EVT_VAR(2) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;
            await DoScareAway;
            return;
        }
        == EVENT_BEGIN_AIR_LIFT {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_run;
            await DoAirLift;
        }
        == EVENT_BLOW_AWAY {
            EVT_VAR(0) = TROOPA_PART_FLYING;
            EVT_VAR(1) = NPC_ANIM_para_jr_troopa_Palette_00_hurt;
            await DoBlowAway;
            return;
        } else {
        }
    }
    SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM_para_jr_troopa_Palette_00_idle_u);
    GetActorHP(ACTOR_SELF, $hp);
    if($hp <= 3){
        await N(lose_flying_mode);
    }
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(troopa_dead) = SCRIPT({
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_INVISIBLE, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_INVISIBLE, 1);
    EnableIdleScript(ACTOR_SELF, 0);
    UseIdleAnimation(ACTOR_SELF, 0);
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_hurt_crazy);
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_9,
        ACTOR_SELF,
        TROOPA_PART_NORMAL,
        NPC_ANIM_jr_troopa_default_hurt_crazy,
        NPC_ANIM_jr_troopa_default_hurt_crazy
    );
        UseBattleCamPreset (13);
        BattleCamTargetActor(ACTOR_SELF);
        GetActorPos(ACTOR_SELF, $x, $y, $z);
        SetBattleCamTarget ($x, $y, 0);
        SetBattleCamZoom (260);
        SetBattleCamOffsetZ (30);
        MoveBattleCamOver (20);
        SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_INVISIBLE, 0);
        SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_INVISIBLE, 1);
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_10,
        ACTOR_SELF,
        TROOPA_PART_MAGE,
        NPC_ANIM_mage_jr_troopa_default_hanging,
        NPC_ANIM_mage_jr_troopa_default_dizzy
    );
        SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_INVISIBLE, 0);
        SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_INVISIBLE, 1);
});

// *INDENT-OFF*
EvtScript N(80222C78) = {
    EVT_CMD(EVT_OP_SET, EVT_VAR(10), EVT_VAR(0)),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(func_8027D32C), -127),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(UseIdleAnimation), -127, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetAnimation), -127, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_hurt_crazy),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 10),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(func_80269E80), EVT_VAR(5)),
    EVT_CMD(EVT_OP_SWITCH, EVT_VAR(5)),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 10),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 14),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 12),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 16),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 11),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 15),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 13),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 17),
        EVT_CMD(EVT_OP_CASE_OR_EQ, 2),
        EVT_CMD(EVT_OP_END_CASE_GROUP),
        EVT_CMD(EVT_OP_CASE_DEFAULT),
            EVT_CMD(EVT_OP_SET, EVT_VAR(2), 0),
            EVT_CMD(EVT_OP_LOOP, 24),
                EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), -127, EVT_VAR(2)),
                EVT_CMD(EVT_OP_ADD, EVT_VAR(2), 30),
                EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
            EVT_CMD(EVT_OP_END_LOOP),
            EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), -127, 0),
    EVT_CMD(EVT_OP_END_SWITCH),
    EVT_CMD(EVT_OP_LABEL, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(GetActorPos), -127, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2)),
    EVT_CMD(EVT_OP_ADD, EVT_VAR(1), 10),
    EVT_CMD(EVT_OP_ADD, EVT_VAR(2), 10),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(PlayEffect), 1, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(PlaySound), 997),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(DropStarPoints), -127),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), -127, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(UseBattleCamPreset), 14),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetBattleCamZoom), 260),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetBattleCamOffsetZ), 15),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(BattleCamTargetActor), -127),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(MoveBattleCamOver), 30),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(PlaySoundAtActor), -127, 8421),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetAnimation), -127, TROOPA_PART_NORMAL, 2162727),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 12),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetAnimation), -127, TROOPA_PART_NORMAL, 2162708),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetIdleAnimations), -127, TROOPA_PART_NORMAL, EVT_PTR(N(idleAnimations_80222C6C))),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 30),
    //EVT_CMD(EVT_OP_CALL, UseIdleAnimation, 256, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(UseBattleCamPreset), 2),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 15),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(UseIdleAnimation), 0, 0),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetAnimation), 0, 0, 65538),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 30),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 60),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 90),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 120),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 150),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 180),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 5),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SpeakToPlayer), 0, NPC_ANIM_spark_normal_talk_nb, NPC_ANIM_spark_normal_idle_nb, 0, MSG_prologue_jrtroopa_battle_11),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 150),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 120),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 90),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 60),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 30),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 1),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorYaw), 0, 0),
    EVT_CMD(EVT_OP_WAIT_FRAMES, 5),
    EVT_CMD(EVT_OP_CALL, EVT_PTR(SetActorFlagBits), -127, 4194304, 1),
    EVT_CMD(EVT_OP_RETURN),
    EVT_CMD(EVT_OP_END)
};
// *INDENT-ON*

EvtScript N(turn) = SCRIPT({
    GetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SECOND_PHASE, $turns_until_transform);
    if($turns_until_transform == 0)
    {
        SetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SECOND_PHASE, -1);
        SetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE, 2);
        SetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, 1);
        await N(transform);
    }
    else
    {
        GetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, $regularAttack);
        if($regularAttack == 2)
        {
            await N(regular_attack);
        }
        else
        {
            $turns_until_transform -= 1;
            SetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SECOND_PHASE, $turns_until_transform);
            GetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, $state);
            if($state == 0){
                await N(spell_attack);
            } else {
                await N(spell_attack_flying);
            }
            GetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, $state);
            if($state == 1){
                GetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SPARK_FLY_AWAY, $turns_until_defend);
                $turns_until_defend -= 1;
                SetActorVar(ACTOR_SELF, VAR_TURNS_UNTIL_SPARK_FLY_AWAY, $turns_until_defend);
                if($turns_until_defend == 0){
                    sleep 16;
                    //await N(lose_flying_mode);
                }
                if($turns_until_defend == 0){
                    sleep 16;
                    await N(spark_fly_away);
                }
                if($turns_until_defend == -1){
                    sleep 16;
                    await N(jr_troopa_defense_jab);
                }
                if($turns_until_defend == -2){
                    sleep 16;
                    await N(spark_fly_back);
                }
            }
        }
    }
});

EvtScript N(spark_fly_away) = SCRIPT({
    UseBattleCamPreset (13);
    BattleCamTargetActor(0);
    SetBattleCamTarget (-114, 0, 0);
    SetBattleCamZoom (320);
    SetBattleCamOffsetZ (50);
    MoveBattleCamOver (20);
    SpeakToPlayer(
        0,
        NPC_ANIM_spark_normal_talk_sad_nb,
        NPC_ANIM_spark_normal_idle_sad_nb,
        0,
        MSG_prologue_jrtroopa_battle_4,
    );
    SetNpcAnimation (0, NPC_ANIM_spark_normal_idle_sad_nb);
    GetNpcPos(0, $x, $y, $z);
    $x -= 90;
    $y += 30;
    NpcFlyTo(0, $x, $y, $z, 25, -6, EASING_COS_IN_OUT);
    SetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE, 1);
    //remove boots
    SetActorFlags(ACTOR_SELF, 0x00000800, TRUE); //TEMP way of making it so mario can't jump on troopa anymore
});

EvtScript N(spark_fly_back) = SCRIPT({
    SetNpcAnimation (0, NPC_ANIM_spark_normal_idle_nb);
    UseBattleCamPreset (13);
    BattleCamTargetActor(0);
    SetBattleCamTarget (-114, 0, 0);
    SetBattleCamZoom (320);
    SetBattleCamOffsetZ (50);
    MoveBattleCamOver (20);
    GetNpcPos(0, $x, $y, $z);
    $x += 90;
    $y -= 30;
    NpcFlyTo(0, $x, $y, $z, 25, -6, EASING_COS_IN_OUT);
    SpeakToPlayer(
        0,
        NPC_ANIM_spark_normal_talk_nb,
        NPC_ANIM_spark_normal_idle_nb,
        0,
        MSG_prologue_jrtroopa_battle_6,
    );
    SetNpcAnimation (0, NPC_ANIM_spark_normal_idle_nb);
    GetActorPos(ACTOR_PLAYER, $x, $y, $z);
    $x -= 10;
    $y += 10;
    $z += 1;
    NpcFlyTo(0, $x, $y, $z, 15, -2, EASING_COS_IN_OUT);
    sleep 4;
    NpcFlyTo(0, -130, 17, -11, 15, -2, EASING_COS_IN_OUT);
    NpcFlyTo(0, -129, 16, -11, 1, -2, EASING_COS_IN_OUT);
    ShowGotItem(ITEM_SHOOTING_STAR, TRUE, 0);
    AddItem(ITEM_SHOOTING_STAR, $out);
    if($out == -1){
        sleep 100;
    }
    SpeakToPlayer(
        0,
        NPC_ANIM_spark_normal_talk_nb,
        NPC_ANIM_spark_normal_idle_nb,
        0,
        MSG_prologue_jrtroopa_battle_7,
    );
    /*
    GetNpcPos(0, $x, $y, $z);
    $y += 10;
    $z += 1;
    MakeItemEntity(ITEM_SHOOTING_STAR, $x, $y, $z, 1, 0);
    sleep 50;
    $x += 10;
    SetItemPos(0, $x, $y, $z);*/
    //sleep 10;
});

EvtScript N(jr_troopa_defense_jab) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    //SetActorVar(-127, 0, 1);
    sleep 15;
    UseBattleCamPreset(14);
    BattleCamTargetActor(ACTOR_SELF);
    SetBattleCamOffsetZ(35);
    MoveBattleCamOver(30);
    sleep 30;
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_5,
        ACTOR_SELF,
        2,
        NPC_ANIM_para_jr_troopa_Palette_00_talk_u,
        NPC_ANIM_para_jr_troopa_Palette_00_idle_u
    );
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(regular_attack) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    SetTargetActor(ACTOR_SELF, 0);
    UseBattleCamPreset(63);
    BattleCamTargetActor(ACTOR_SELF);
    //0x8024ECF8(-1, 1, 0);
    SetAnimation(ACTOR_SELF, 1, NPC_ANIM_mage_jr_troopa_default_run_u);
    SetGoalToTarget(ACTOR_SELF);
    AddGoalPos(ACTOR_SELF, 15, 0, -1);
    SetActorSpeed(ACTOR_SELF, 8.0);
    RunToGoal(ACTOR_SELF, 0, 0);
    SetAnimation(ACTOR_SELF, 1, NPC_ANIM_mage_jr_troopa_default_idle);
    SetAnimation(ACTOR_SELF, 1, NPC_ANIM_mage_jr_troopa_default_attack_u);
    sleep 10; //timing for when mario gets damaged.
    SetAnimation(ACTOR_SELF, 1, NPC_ANIM_mage_jr_troopa_default_attack2_u);
    SetGoalToTarget(ACTOR_SELF);
    EnemyDamageTarget(ACTOR_SELF, EVT_VAR(0), 0, 0, 0, 1, 20);
    sleep 20;
    SetAnimation(ACTOR_SELF, 1, NPC_ANIM_mage_jr_troopa_default_run_u);
    SetGoalToHome(ACTOR_SELF);
    SetActorSpeed(ACTOR_SELF, 10.0);
    RunToGoal(ACTOR_SELF, 0, 0);
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(transform) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    //SetActorVar(-127, 0, 1);
    sleep 15;
    UseBattleCamPreset(14);
    BattleCamTargetActor(ACTOR_SELF);
    SetBattleCamOffsetZ(35);
    MoveBattleCamOver(30);
    sleep 30;
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_2,
        ACTOR_SELF,
        1,
        NPC_ANIM_mage_jr_troopa_default_talk_point_u,
        NPC_ANIM_mage_jr_troopa_default_idle_u
    );
    sleep 8;
    await N(802260AC);
    //SetIdleAnimations(ACTOR_SELF, 1, N(anims_para));
    //SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM(para_jr_troopa, default, idle));
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_FLYING, ACTOR_PART_FLAG_INVISIBLE, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_INVISIBLE, 1);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_FLYING, ACTOR_PART_FLAG_NO_TARGET, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_NO_TARGET, 1);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_FLYING, ACTOR_PART_FLAG_MULTI_TARGET, 1);
    // SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_MULTI_TARGET, 0);
    sleep 30;
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) += 20;
    SetGoalPos(ACTOR_SELF, EVT_VAR(0), 60, EVT_VAR(2));
    FlyToGoal(-127, 45, 0, 0);
    ForceHomePos(ACTOR_SELF, EVT_VAR(0), 60, EVT_VAR(2));
    HPBarToHome(ACTOR_SELF);
    sleep 8;
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_3,
        ACTOR_SELF,
        2,
        NPC_ANIM_para_jr_troopa_Palette_00_talk_u,
        NPC_ANIM_para_jr_troopa_Palette_00_idle_u
    );
    sleep 10;
    await N(8022646C);
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
    BindHandleEvent(ACTOR_SELF, N(dispatch_para));
    await N(spell_attack_flying);
    //await N(lose_flying_mode);
});

EvtScript N(802260AC) = SCRIPT({
    PlaySoundAtActor(ACTOR_SELF, 0x20B9);
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    GetStatusFlags(-127, EVT_VAR(3));
    if (EVT_VAR(3) !& 524288) {
        EVT_VAR(1) += 16;
    } else {
        EVT_VAR(1) += 6;
    }
    PlayEffect(0x13, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 1, 30, 0, 0, 0, 0, 0, 0, 0);
    PlayEffect(0x13, 1, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 1, 30, 0, 0, 0, 0, 0, 0, 0);
    spawn {
        EVT_VAR(0) = 0;
        loop 32 {
            sleep 1;
            EVT_VAR(0) += 45;
            SetActorRotation(ACTOR_SELF, 0, EVT_VAR(0), 0);
        }
    }
    sleep 32;
    PlaySoundAtActor(ACTOR_SELF, 0x300);
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(1) += 15;
    PlayEffect(0x52, 4, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 1, 40, 0, 0, 0, 0, 0, 0, 0);
    PlayEffect(0x7, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), -4, 0, 0, 0, 0, 0, 0, 0, 0);
    PlayEffect(0x7, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), -4, 4, 0, 0, 0, 0, 0, 0, 0);
    PlayEffect(0x7, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 4, 0, 0, 0, 0, 0, 0, 0, 0);
    PlayEffect(0x7, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 4, 4, 0, 0, 0, 0, 0, 0, 0);
});

EvtScript N(8022646C) = SCRIPT({
    //func_802535B4(1);
    UseBattleCamPreset(2);
    MoveBattleCamOver(12);
});

EvtScript N(spell_attack) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    SetTargetActor(ACTOR_SELF, 0);
    SetGoalToTarget(ACTOR_SELF);
    UseBattleCamPreset(2);
    MoveBattleCamOver(20);
    SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_attack_u);
    sleep 8;
    PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST1);
    GetStatusFlags(-127, EVT_VAR(0));
    if (EVT_VAR(0) !& 524288) {
        EVT_VAR(3) = 0;
        EVT_VAR(4) = 36;
        EVT_VAR(5) = 1.0;
    } else {
        EVT_VAR(3) = 0;
        EVT_VAR(4) = 14;
        EVT_VAR(5) = EVT_MAP_FLAG(-1999590);
    }
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) += EVT_VAR(3);
    EVT_VAR(1) += EVT_VAR(4);
    PlayEffect(0x13, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(5), 30, 0, 0, 0, 0, 0, 0, 0);
    sleep 30;
    SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_attack2_u);
    EnemyTestTarget(ACTOR_SELF, EVT_VAR(10), 268435456, 0, 1, 16);
    match EVT_VAR(10) {
        == 6 {
            PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST2);
            GetActorPos(ACTOR_PLAYER, EVT_VAR(3), EVT_VAR(4), EVT_VAR(5));
            EVT_VAR(3) -= 120;
            EVT_VAR(4) += 20;
            GetStatusFlags(-127, EVT_VAR(0));
            if (EVT_VAR(0) !& 524288) {
                EVT_VAR(6) = -8;
                EVT_VAR(7) = 20;
                EVT_VAR(8) = 1.0;
            } else {
                EVT_VAR(6) = -3;
                EVT_VAR(7) = 8;
                EVT_VAR(8) = EVT_MAP_FLAG(-1999590);
            }
            GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
            EVT_VAR(0) += EVT_VAR(6);
            EVT_VAR(1) += EVT_VAR(7);
            PlayEffect(0x12, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(3), EVT_VAR(4), EVT_VAR(5), 30, 0, 0, 0, 0, 0);
            sleep 35;
            EnableIdleScript(ACTOR_SELF, 1);
            UseIdleAnimation(ACTOR_SELF, 1);
            return;
        }
        == 5 {
            spawn {
                GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
                EVT_VAR(1) += 12;
                PlayEffect(0x3E, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 3.0, 30, 0, 0, 0, 0, 0, 0, 0);
                SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_attack2_burn);
                GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
                sleep 40;
                EVT_VAR(0) -= 7;
                EVT_VAR(1) += 14;
                EVT_VAR(2) += 4;
                PlayEffect(0x7, 2, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 0, 0, 0, 0, 0, 0, 0, 0, 0);
                sleep 20;
                SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_idle_u);
            }
            sleep 20;
            EnemyTestTarget(ACTOR_SELF, EVT_VAR(0), 0x80000000, 0, 0, 0);
            sleep 40;
            EnableIdleScript(ACTOR_SELF, 1);
            UseIdleAnimation(ACTOR_SELF, 1);
            return;
        }
    }
    PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST2);
    GetActorPos(ACTOR_PLAYER, EVT_VAR(3), EVT_VAR(4), EVT_VAR(5));
    EVT_VAR(4) += 20;
    GetStatusFlags(-127, EVT_VAR(0));
    if (EVT_VAR(0) !& 524288) {
        EVT_VAR(6) = -8;
        EVT_VAR(7) = 20;
        EVT_VAR(8) = 1.0;
    } else {
        EVT_VAR(6) = -3;
        EVT_VAR(7) = 8;
        EVT_VAR(8) = EVT_MAP_FLAG(-1999590);
    }
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) += EVT_VAR(6);
    EVT_VAR(1) += EVT_VAR(7);
    PlayEffect(0x12, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(3), EVT_VAR(4), EVT_VAR(5), 15, 0, 0, 0, 0, 0);
    sleep 15;
    GetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE,EVT_VAR(1));
    EnemyDamageTarget(ACTOR_SELF, EVT_VAR(0), 268435472, 0, 0, EVT_VAR(1), 32);
    UseBattleCamPreset(2);
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(spell_attack_flying) = SCRIPT({
    UseIdleAnimation(ACTOR_SELF, 0);
    EnableIdleScript(ACTOR_SELF, 0);
    SetTargetActor(ACTOR_SELF, 0);
    SetGoalToTarget(ACTOR_SELF);
    UseBattleCamPreset(2);
    MoveBattleCamOver(20);
    SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM_para_jr_troopa_Palette_00_attack_u);
    sleep 8;
    PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST1);
    GetStatusFlags(-127, EVT_VAR(0));
    if (EVT_VAR(0) !& 524288) {
        EVT_VAR(3) = 0;
        EVT_VAR(4) = 36;
        EVT_VAR(5) = 1.0;
    } else {
        EVT_VAR(3) = 0;
        EVT_VAR(4) = 14;
        EVT_VAR(5) = EVT_MAP_FLAG(-1999590);
    }
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) += EVT_VAR(3);
    EVT_VAR(1) += EVT_VAR(4);
    EVT_VAR(0) -= 7; //X position offset for spell attack
    EVT_VAR(1) += 9; //Y position offset for spell attack
    PlayEffect(0x13, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(5), 30, 0, 0, 0, 0, 0, 0, 0);
    sleep 30;
    SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM_para_jr_troopa_Palette_00_attack2_u);
    EnemyTestTarget(ACTOR_SELF, EVT_VAR(10), 268435456, 0, 1, 16);
    match EVT_VAR(10) {
        == 6 {
            PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST2);
            GetActorPos(ACTOR_PLAYER, EVT_VAR(3), EVT_VAR(4), EVT_VAR(5));
            EVT_VAR(3) -= 120;
            EVT_VAR(4) += 20;
            GetStatusFlags(-127, EVT_VAR(0));
            if (EVT_VAR(0) !& 524288) {
                EVT_VAR(6) = -8;
                EVT_VAR(7) = 20;
                EVT_VAR(8) = 1.0;
            } else {
                EVT_VAR(6) = -3;
                EVT_VAR(7) = 8;
                EVT_VAR(8) = EVT_MAP_FLAG(-1999590);
            }
            GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
            EVT_VAR(0) += EVT_VAR(6);
            EVT_VAR(1) += EVT_VAR(7);
            PlayEffect(0x12, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(3), EVT_VAR(4), EVT_VAR(5), 30, 0, 0, 0, 0, 0);
            sleep 35;
            EnableIdleScript(ACTOR_SELF, 1);
            UseIdleAnimation(ACTOR_SELF, 1);
            return;
        }
        == 5 {
            spawn {
                GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
                EVT_VAR(1) += 12;
                PlayEffect(0x3E, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 3.0, 30, 0, 0, 0, 0, 0, 0, 0);
                //SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM(mage_jr_troopa, default, attack2_burn));
                GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
                sleep 40;
                EVT_VAR(0) -= 7;
                EVT_VAR(1) += 14;
                EVT_VAR(2) += 4;
                PlayEffect(0x7, 2, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 0, 0, 0, 0, 0, 0, 0, 0, 0);
                sleep 20;
                //SetAnimation(ACTOR_SELF, TROOPA_PART_FLYING, NPC_ANIM(mage_jr_troopa, default, idle_u));
            }
            sleep 20;
            EnemyTestTarget(ACTOR_SELF, EVT_VAR(0), 0x80000000, 0, 0, 0);
            sleep 40;
            EnableIdleScript(ACTOR_SELF, 1);
            UseIdleAnimation(ACTOR_SELF, 1);
            return;
        }
    }
    PlaySoundAtActor(ACTOR_SELF, SOUND_SPELL_CAST2);
    GetActorPos(ACTOR_PLAYER, EVT_VAR(3), EVT_VAR(4), EVT_VAR(5));
    EVT_VAR(4) += 20;
    EVT_VAR(3) -= 5;
    GetStatusFlags(-127, EVT_VAR(0));
    if (EVT_VAR(0) !& 524288) {
        EVT_VAR(6) = -8;
        EVT_VAR(7) = 20;
        EVT_VAR(8) = 1.0;
    } else {
        EVT_VAR(6) = -3;
        EVT_VAR(7) = 8;
        EVT_VAR(8) = EVT_MAP_FLAG(-1999590);
    }
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) += EVT_VAR(6);
    EVT_VAR(1) += EVT_VAR(7);
    PlayEffect(0x12, 0, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), EVT_VAR(3), EVT_VAR(4), EVT_VAR(5), 15, 0, 0, 0, 0, 0);
    sleep 15;
    GetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE,EVT_VAR(1));
    EnemyDamageTarget(ACTOR_SELF, EVT_VAR(0), 268435472, 0, 0, EVT_VAR(1), 32);
    UseBattleCamPreset(2);
    EnableIdleScript(ACTOR_SELF, 1);
    UseIdleAnimation(ACTOR_SELF, 1);
});

EvtScript N(lose_flying_mode) = SCRIPT({
    spawn {
        sleep 10;
        ActorSpeak(
        MSG_prologue_jrtroopa_battle_8A,
        ACTOR_SELF,
        TROOPA_PART_FLYING,
        NPC_ANIM_para_jr_troopa_Palette_00_hanging,
        NPC_ANIM_para_jr_troopa_Palette_00_hanging
    );
    }
    UseBattleCamPreset(2);
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    if (EVT_VAR(1) == 0) {
        goto 0;
    }
    PlaySoundAtActor(ACTOR_SELF, 0x301);
    SetActorSounds(-127, 2, 0, 0);
    //func_8027D32C(-127);
    SetGoalPos(ACTOR_SELF, EVT_VAR(0), 0, EVT_VAR(2));
    SetActorJumpGravity(ACTOR_SELF, 1.2001953125);
    FallToGoal(-127, 10);
    SetActorJumpGravity(ACTOR_SELF, 0.80078125);
    JumpToGoal(ACTOR_SELF, 8, 0, 1, 0);
    HPBarToCurrent(-127);
    BindHandleEvent(ACTOR_SELF, N(dispatch));
    //func_8027D2D8(-127);
0:
    spawn {
        GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
        EVT_VAR(1) += 10;
        EVT_VAR(2) += 10;
        loop 3 {
            PlayEffect(0x1, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            sleep 3;
        }
    }
    //SetPartFlagBits(-127, 1, 1, 1);
    //SetPartFlagBits(-127, 2, 1, 0);
    //SetAnimation(ACTOR_SELF, 2, NPC_ANIM(jr_troopa, default, dead_still));
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_FLYING, ACTOR_PART_FLAG_INVISIBLE, 1);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_INVISIBLE, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_FLYING, ACTOR_PART_FLAG_NO_TARGET, 1);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_NO_TARGET, 0);
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_dead);
    GetActorPos(ACTOR_SELF, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    EVT_VAR(0) -= 5;
    SetActorPos(-127, EVT_VAR(0), EVT_VAR(1), EVT_VAR(2));
    PlaySoundAtActor(ACTOR_SELF, 0x20E5);
    //sleep 15;
    //PlaySoundAtActor(ACTOR_SELF, SOUND_DEATH);
    //DropStarPoints(-127);
    SetActorYaw(ACTOR_SELF, 0);
    UseBattleCamPreset(14);
    SetBattleCamZoom(260);
    SetBattleCamOffsetZ(15);
    BattleCamTargetActor(ACTOR_SELF);
    MoveBattleCamOver(30);
    //SetAnimation(ACTOR_SELF, 2, NPC_ANIM(jr_troopa, default, dead));
    //SetIdleAnimations(-127, 2, N(idleAnimations_80225E48));
    sleep 35;
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_jump);
    sleep 2;
    JumpPartTo(ACTOR_SELF, TROOPA_PART_NORMAL, $x, $y, $z, 2, 1);
    sleep 4;
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_jump_land);
    sleep 4;
    //sleep 80;
    //SetPartMoveSpeed(ACTOR_SELF, TROOPA_PART_NORMAL, 1);
    //SetPartJumpGravity(ACTOR_SELF, TROOPA_PART_NORMAL, 10);
    //SetActorJumpGravity(ACTOR_SELF, 10);
    //GetPartPos(ACTOR_SELF, TROOPA_PART_NORMAL, $x, $y, $z);
    //JumpPartTo(ACTOR_SELF, TROOPA_PART_MAGE, $x, $y, $z, 10, 1);
    //JumpToGoal(ACTOR_SELF, 5, 0, 1, 1);
    //sleep 50;
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_idle_angry);
    sleep 6;
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_8B,
        ACTOR_SELF,
        TROOPA_PART_NORMAL,
        NPC_ANIM_jr_troopa_default_talk2,
        NPC_ANIM_jr_troopa_default_idle_angry
    );
    SetAnimation(ACTOR_SELF, TROOPA_PART_NORMAL, NPC_ANIM_jr_troopa_default_stand_weird_land);
    EVT_VAR(3) = 0;
    loop 12 {
        EVT_VAR(3) += 15;
        SetActorYaw(ACTOR_SELF, EVT_VAR(3));
        sleep 1;
    }
    sleep 20;
    loop 12 {
        EVT_VAR(3) -= 15;
        SetActorYaw(ACTOR_SELF, EVT_VAR(3));
        sleep 1;
    }
    sleep 20;
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_8C,
        ACTOR_SELF,
        TROOPA_PART_NORMAL,
        NPC_ANIM_jr_troopa_default_hanging,
        NPC_ANIM_jr_troopa_default_idle_angry
    );
    ActorSpeak(
        MSG_prologue_jrtroopa_battle_8D,
        ACTOR_SELF,
        TROOPA_PART_NORMAL,
        NPC_ANIM_jr_troopa_default_talk_point,
        NPC_ANIM_jr_troopa_default_point_tap
    );
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_INVISIBLE, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_INVISIBLE, 1);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_MAGE, ACTOR_PART_FLAG_NO_TARGET, 0);
    SetPartFlagBits(ACTOR_SELF, TROOPA_PART_NORMAL, ACTOR_PART_FLAG_NO_TARGET, 1);
    SetAnimation(ACTOR_SELF, TROOPA_PART_MAGE, NPC_ANIM_mage_jr_troopa_default_idle_u);
    SetActorVar(ACTOR_SELF, VAR_TROOPA_DAMAGE, 1);
    SetActorVar(ACTOR_SELF, VAR_TROOPA_STATE, 2);
    //SetActorFlagBits(-127, 4194304, 1);
    //add boots
    SetActorFlags(ACTOR_SELF, 0x0, TRUE); //TEMP way of making it so mario can jump on troopa again
});

#undef NAMESPACE
