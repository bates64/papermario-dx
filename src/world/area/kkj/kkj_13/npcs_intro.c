#include "kkj_13.h"
#include "sprite/player.h"

EvtScript N(EVS_NpcIdle_BowserAwaitBattle_Intro) = {
    Call(SetSelfVar, 0, 1)
    Loop(0)
        Wait(1)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(ModifyGlobalOverrideFlags, 1, GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE)
    Call(StartBossBattle, SONG_BOWSER_THEME)
    Return
    End
};

EvtScript N(EVS_NpcDefeat_Bowser_Body_Intro) = {
    Call(SetSelfVar, 0, 1)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bowser_Body_Intro) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_BowserAwaitBattle_Intro)))
    Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_Bowser_Body_Intro)))
    Return
    End
};

AnimID N(LimitAnims_Bowser_Intro)[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_BrandishIdle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Run,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_TalkEyesClosed,
    ANIM_WorldBowser_BrandishTalk,
    ANIM_WorldBowser_RearUpTalk,
    ANIM_WorldBowser_RearUpLaugh,
    ANIM_WorldBowser_Brandish,
    ANIM_WorldBowser_RearUpMock,
    ANIM_WorldBowser_PostJump,
    ANIM_WorldBowser_ClownCarStill,
    ANIM_WorldBowser_ClownCarIdle,
    ANIM_WorldBowser_ClownCarPropeller,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy_Intro)[] = {
    ANIM_WorldKammy_Idle,
    ANIM_WorldKammy_Walk,
    ANIM_WorldKammy_Talk,
    ANIM_WorldKammy_FlyStill,
    ANIM_WorldKammy_FlyIdle,
    ANIM_WorldKammy_FlySlow,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Koopatrol_Intro)[] = {
    ANIM_WorldKoopatrol_Still,
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Walk,
    ANIM_WorldKoopatrol_Run,
    ANIM_LIST_END
};

NpcData N(NpcData_Bowser_Intro) = {
    .id = NPC_Bowser_Body,
    .pos = { 0.0f, -500.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Bowser_Body_Intro),
    .settings = &N(NpcSettings_Bowser),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
    .limitAnimations = N(LimitAnims_Bowser_Intro),
};

NpcData N(NpcData_Characters_Intro)[] = {
    {
        .id = NPC_Bowser_Prop,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = N(LimitAnims_Bowser_Intro),
    },
    {
        .id = NPC_Koopatrol_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Intro),
    },
    {
        .id = NPC_Koopatrol_02,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Intro),
    },
    {
        .id = NPC_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Kammy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = N(LimitAnims_Kammy_Intro),
    },
    {
        .id = NPC_Peach,
        .pos = { 670.0f, 0.0f, -12.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Peach),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
        .drops = NO_DROPS,
        .animations = PEACH_ANIMS,
    },
};

NpcGroupList N(IntroNPCs) = {
    NPC_GROUP(N(NpcData_Bowser_Intro), BTL_KPA2_FORMATION_01),
    NPC_GROUP(N(NpcData_Characters_Intro)),
    {}
};
