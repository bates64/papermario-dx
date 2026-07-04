#include "kkj_25.h"
#include "sprite/player.h"

EvtScript N(EVS_NpcIdle_Bowser_Npc1) = {
    Call(SetSelfVar, 0, 0)
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Thread
        Call(GetNpcPos, NPC_Bowser_01, LVar0, LVar1, LVar2)
        Add(LVar0, -75)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Call(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Call(SetCamDistance, CAM_DEFAULT, 1000)
        Call(SetCamPitch, CAM_DEFAULT, Float(17.0), Float(-7.0))
        Call(SetCamSpeed, CAM_DEFAULT, Float(4.0))
        Call(PanToTarget, CAM_DEFAULT, 0, true)
    EndThread
    Call(ModifyGlobalOverrideFlags, 1, GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE)
    Call(StopSound, SOUND_LRAW_KPA_ARENA_TURN_ON)
    Call(StartBossBattle, SONG_BOWSER_BATTLE)
    Return
    End
};

EvtScript N(EVS_NpcDefeat_Bowser_Npc1) = {    Call(PlaySound, SOUND_LRAW_KPA_ARENA_ACTIVE)
    Exec(N(EVS_Scene_PeachBreaksFree))
    Return
    End};

EvtScript N(EVS_NpcInit_Bowser_Npc1) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Bowser_Npc1)))
    Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_Bowser_Npc1)))
    Call(SetNpcPos, NPC_Bowser_01, 350, 0, 0)
    Return
    End
};

EvtScript N(EVS_NpcIdle_Kammy_Broom_Npc1) = {
    Call(SetSelfVar, 0, 0)
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfNe(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetPlayerImgFXFlags, IMGFX_FLAG_USE_LIGHTING)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Idle, IMGFX_SET_TINT, 0, 0, 0, 0)
    Call(HidePlayerShadow, true)
    Call(DisablePartnerAI, false)
    Wait(1)
    Call(GetNpcPos, NPC_Peach_01, LVar0, LVar1, LVar2)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Call(ModifyGlobalOverrideFlags, 1, GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE)
    Call(StopSound, SOUND_LRAW_KPA_ARENA_ACTIVE)
    Call(StartBossBattle, SONG_BOWSER_BATTLE)
    Call(EnablePartnerAI)
    Return
    End
};

API_CALLABLE(N(PostBattleHideWorld_Npc1)) {
    increment_status_bar_disabled();
    set_screen_overlay_params_back(OVERLAY_SCREEN_COLOR, 255.0f);

    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcDefeat_Kammy_Broom_Npc1) = {
    Call(GetBattleOutcome, LVar0)
    Call(N(PostBattleHideWorld_Npc1))
    Set(GF_KKJ25_Defeated_Kammy, true)
    // reload the map in the 'midpoint' configuration
    Call(GotoMap, Ref("kkj_25"), kkj_25_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_NpcAux_Kammy_Broom_Npc1) = {
    Set(LVar3, 1)
    Loop(0)
        Loop(5)
            Call(GetNpcPos, NPC_Kammy_01, LVar0, LVar1, LVar2)
            Add(LVar1, LVar3)
            Call(SetNpcPos, NPC_Kammy_01, LVar0, LVar1, LVar2)
            Wait(2)
        EndLoop
        Mul(LVar3, -1)
        Wait(3)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy_Broom_Npc1) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Kammy_Broom_Npc1)))
    Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_Kammy_Broom_Npc1)))
    Call(BindNpcAux, NPC_SELF, Ref(N(EVS_NpcAux_Kammy_Broom_Npc1)))
    Call(SetNpcPos, NPC_Kammy_01, 460, 10, 0)
    Call(SetNpcYaw, NPC_Kammy_01, 270)
    Call(SetNpcAnimation, NPC_Kammy_01, ANIM_BattleKammy_FlyStill)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy_Npc1) = {
    Call(SetNpcPos, NPC_Kammy_02, 300, -100, 0)
    Call(SetNpcAnimation, NPC_Kammy_02, ANIM_BattleKammy_Fall)
    Return
    End
};

EvtScript N(EVS_NpcInit_BattleKooper_01_Npc1) = {
    Call(SetNpcPos, NPC_Peach_01, 400, 0, -30)
    Call(SetNpcYaw, NPC_Peach_01, 270)
    Call(SetNpcAnimation, NPC_Peach_01, ANIM_Peach2_TiedIdle)
    Return
    End
};

EvtScript N(EVS_NpcInit_Twink_Npc1) = {
    Call(SetNpcAnimation, NPC_Twink_01, ANIM_Twink_Idle)
    Call(EnableNpcShadow, NPC_Twink_01, false)
    Call(SetNpcPos, NPC_Twink_01, 300, -100, 0)
    Return
    End
};

AnimID N(LimitAnims_Bowser_Npc1)[] = {
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_Shock,
    ANIM_WorldBowser_RearUpLaugh,
    ANIM_WorldBowser_Tantrum,
    ANIM_WorldBowser_Jump,
    ANIM_WorldBowser_Land,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Peach_Npc1)[] = {
    ANIM_Peach2_TiedStill,
    ANIM_Peach1_Idle,
    ANIM_Peach1_Walk,
    ANIM_Peach2_RaiseArms,
    ANIM_Peach2_GaspStill,
    ANIM_Peach2_TiedIdle,
    ANIM_Peach3_TiedTalk,
    ANIM_Peach3_TiedShout,
    ANIM_Peach3_TiedLaugh,
    ANIM_Peach2_TalkIdle,
    ANIM_Peach3_Pray,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy_Npc1)[] = {
    ANIM_BattleKammy_Idle,
    ANIM_BattleKammy_Talk,
    ANIM_BattleKammy_FlyStill,
    ANIM_BattleKammy_FlyTalk,
    ANIM_BattleKammy_FlyRodTalk,
    ANIM_BattleKammy_FlyRodCast,
    ANIM_BattleKammy_Fall,
    ANIM_BattleKammy_Broom,
    ANIM_BattleKammy_Slump,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Twink_Npc1)[] = {
    ANIM_Twink_Idle,
    ANIM_Twink_Sad,
    ANIM_Twink_Back,
    ANIM_Twink_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_Bowser_Npc1) = {
    .id = NPC_Bowser_01,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Bowser_Npc1),
    .settings = &N(NpcSettings_Bowser),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
    .limitAnimations = N(LimitAnims_Bowser_Npc1),
};

NpcData N(NpcData_Peach_Npc1) = {
    .id = NPC_Peach_01,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_BattleKooper_01_Npc1),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
    .limitAnimations = N(LimitAnims_Peach_Npc1),
};

NpcData N(NpcData_Kammy_Npc1)[] = {
    {
        .id = NPC_Kammy_01,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Kammy_Broom_Npc1),
        .settings = &N(NpcSettings_Kammy_Flying),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_BattleKammy_Idle,
            .walk   = ANIM_BattleKammy_Idle,
            .run    = ANIM_BattleKammy_Idle,
            .chase  = ANIM_BattleKammy_Idle,
            .alert  = ANIM_BattleKammy_Idle,
            .unused = ANIM_BattleKammy_Idle,
            .death  = ANIM_BattleKammy_Idle,
            .hit    = ANIM_BattleKammy_Idle,
            .anim_8 = ANIM_BattleKammy_Idle,
            .anim_9 = ANIM_BattleKammy_Idle,
            .anim_A = ANIM_BattleKammy_Idle,
            .anim_B = ANIM_BattleKammy_Idle,
            .anim_C = ANIM_BattleKammy_Idle,
            .anim_D = ANIM_BattleKammy_Idle,
            .anim_E = ANIM_BattleKammy_Idle,
            .anim_F = ANIM_BattleKammy_Idle,
        },
        .limitAnimations = N(LimitAnims_Kammy_Npc1),
    },
    {
        .id = NPC_Kammy_02,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Kammy_Npc1),
        .settings = &N(NpcSettings_Kammy_Flying),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_BattleKammy_Idle,
            .walk   = ANIM_BattleKammy_Idle,
            .run    = ANIM_BattleKammy_Idle,
            .chase  = ANIM_BattleKammy_Idle,
            .alert  = ANIM_BattleKammy_Idle,
            .unused = ANIM_BattleKammy_Idle,
            .death  = ANIM_BattleKammy_Idle,
            .hit    = ANIM_BattleKammy_Idle,
            .anim_8 = ANIM_BattleKammy_Idle,
            .anim_9 = ANIM_BattleKammy_Idle,
            .anim_A = ANIM_BattleKammy_Idle,
            .anim_B = ANIM_BattleKammy_Idle,
            .anim_C = ANIM_BattleKammy_Idle,
            .anim_D = ANIM_BattleKammy_Idle,
            .anim_E = ANIM_BattleKammy_Idle,
            .anim_F = ANIM_BattleKammy_Idle,
        },
        .limitAnimations = N(LimitAnims_Kammy_Npc1),
    },
};

NpcData N(NpcData_Twink_Npc1) = {
    .id = NPC_Twink_01,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Twink_Npc1),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = TWINK_ANIMS,
    .limitAnimations = N(LimitAnims_Twink_Npc1),
};

NpcGroupList N(InitialNpcs) = {
    NPC_GROUP(N(NpcData_Bowser_Npc1), BTL_KPA2_FORMATION_03),
    NPC_GROUP(N(NpcData_Peach_Npc1)),
    NPC_GROUP(N(NpcData_Kammy_Npc1), BTL_KKJ_FORMATION_00),
    NPC_GROUP(N(NpcData_Twink_Npc1)),
    {}
};
