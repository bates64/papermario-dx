#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/Tatanga.h"
#include "sprite/npc/StarZoneStar.h"

#define NAMESPACE A(tatanga)

extern EvtScript N(EVS_Init);
extern s32 N(DefaultAnims)[];
extern s32 N(BiffBulletAnims)[];
extern s32 N(ShotMoonAnims)[];
extern s32 N(ShotBallAnims)[];
extern s32 N(ShotFireworkAnims)[];
extern s32 N(ShotStarAnims)[];
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
    PRT_MAIN            = 1,
    PRT_BIFF_BULLET     = 2,
    PRT_SHOT_MOON_1     = 3,
    PRT_SHOT_MOON_2     = 4,
    PRT_SHOT_BALL       = 5,
    PRT_SHOT_FIREWORK   = 6,
    PRT_SHOT_STAR_1     = 7,
    PRT_SHOT_STAR_2     = 8,
    PRT_SHOT_STAR_3     = 9,
    PRT_SHOT_STAR_4     = 10,
    PRT_SHOT_STAR_5     = 11,
};

enum N(ActorVars) {
    AVAR_TurnCounter                  = 0,
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
        .targetOffset = { -10, 50 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_BIFF_BULLET,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(BiffBulletAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_MOON_1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotMoonAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_MOON_2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotMoonAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_BALL,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotBallAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_FIREWORK,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotFireworkAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_STAR_1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotStarAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_STAR_2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotStarAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_STAR_3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotStarAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_STAR_4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotStarAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
    {
        .flags = ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_INVISIBLE,
        .index = PRT_SHOT_STAR_5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = N(ShotStarAnims),
        .defenseTable = N(DefenseTable),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_FLYING,
    .type = ACTOR_TYPE_TATANGA,
    .level = ACTOR_LEVEL_TATANGA,
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
    .size = { 72, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_Idle,
    STATUS_KEY_STONE,     ANIM_Tatanga_Still,
    STATUS_KEY_SLEEP,     ANIM_Tatanga_Still,
    STATUS_KEY_POISON,    ANIM_Tatanga_Idle,
    STATUS_KEY_STOP,      ANIM_Tatanga_Still,
    STATUS_KEY_STATIC,    ANIM_Tatanga_Idle,
    STATUS_KEY_PARALYZE,  ANIM_Tatanga_Still,
    STATUS_KEY_DIZZY,     ANIM_Tatanga_Dizzy,
    STATUS_KEY_FEAR,      ANIM_Tatanga_Idle,
    STATUS_END,
};

s32 N(BiffBulletAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_ShotBiff,
    STATUS_END,
};

s32 N(ShotMoonAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_ShotMoon,
    STATUS_END,
};

s32 N(ShotBallAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_ShotBall,
    STATUS_END,
};

s32 N(ShotFireworkAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_ShotFireworks,
    STATUS_END,
};

s32 N(ShotStarAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_ShotBall,
    STATUS_END,
};
