#include "kkj_25.h"
#include "sprite/player.h"

EvtScript N(EVS_NpcIdle_Bowser_Npc2) = {
    Label(0)
        Call(SetSelfVar, 0, 0)
        Loop(0)
            Call(GetSelfVar, 0, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Thread
            Call(GetNpcPos, NPC_Bowser_02, LVar0, LVar1, LVar2)
            Add(LVar0, -75)
            Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
            Call(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
            Call(SetCamSpeed, CAM_DEFAULT, Float(4.0))
            Call(SetCamPitch, CAM_DEFAULT, Float(17.0), Float(-7.0))
            Call(SetCamDistance, CAM_DEFAULT, 1000)
            Call(PanToTarget, CAM_DEFAULT, 0, true)
        EndThread
        Call(StartBossBattle, SONG_FINAL_BOWSER_BATTLE)
        Goto(0)
    Return
    End
};

API_CALLABLE(N(PostBattleHideWorld_Npc2)) {
    increment_status_bar_disabled();
    set_screen_overlay_params_back(OVERLAY_SCREEN_COLOR, 255.0f);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcDefeat_Bowser_Npc2) = {
    Call(SetEncounterStatusFlags, ENCOUNTER_FLAG_CANT_SKIP_WIN_DELAY, true)
    Call(N(PostBattleHideWorld_Npc2))
    Set(GF_KKJ25_Defeated_Bowser, true)
    // reload the map in the 'final' configuration
    Call(GotoMap, Ref("kkj_25"), kkj_25_ENTRY_2)
    Wait(100)
    Return
    End
};

s32 N(FlyingKammyHoverOffsets_Npc2)[] = {
    1, 2, 3, 2, 1, -1, -2, -3, -2, -1,
};

EvtScript N(EVS_NpcAux_Kammy_Broom_Npc2) = {
    Label(0)
        UseBuf(Ref(N(FlyingKammyHoverOffsets_Npc2)))
        Loop(10)
            BufRead1(LVar1)
            Call(GetNpcPos, NPC_Kammy_03, LVar2, LVar3, LVar4)
            Add(LVar3, LVar1)
            Call(SetNpcPos, NPC_Kammy_03, LVar2, LVar3, LVar4)
            Wait(3)
        EndLoop
        Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Peach_Npc2) = {
    Call(SetNpcPos, NPC_Peach_01, 475, 0, 0)
    Call(SetNpcAnimation, NPC_Peach_01, ANIM_Peach1_Idle)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bowser_Npc2) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Bowser_Npc2)))
    Call(BindNpcDefeat, NPC_SELF, Ref(N(EVS_NpcDefeat_Bowser_Npc2)))
    Call(SetNpcScale, NPC_Bowser_02, Float(1.5), Float(1.5), Float(1.5))
    Call(SetNpcPos, NPC_Bowser_02, 200, 0, 0)
    Call(SetNpcAnimation, NPC_Bowser_02, ANIM_WorldBowser_Idle)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy_Broom_Npc2) = {
    Call(BindNpcAux, NPC_SELF, Ref(N(EVS_NpcAux_Kammy_Broom_Npc2)))
    Call(SetNpcPos, NPC_Kammy_03, 540, 10, -50)
    Call(SetNpcAnimation, NPC_Kammy_03, ANIM_BattleKammy_Broom)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy_Npc2) = {
    Call(SetNpcPos, NPC_Kammy_04, 550, 0, -40)
    Call(SetNpcAnimation, NPC_Kammy_04, ANIM_BattleKammy_Slump)
    Return
    End
};

EvtScript N(EVS_NpcInit_Twink_Npc2) = {
    Call(InterpNpcYaw, NPC_Peach_01, 270, 0)
    Call(SetNpcPos, NPC_Twink_01, 510, 30, 0)
    Call(InterpNpcYaw, NPC_Twink_01, 270, 0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Eldstar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Eldstar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Eldstar, false)
    Call(SetNpcPos, NPC_Eldstar, 100, 45, 0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Mamar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Mamar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Mamar, false)
    Call(SetNpcPos, NPC_Mamar, 46, 45, -27)
    Return
    End
};

EvtScript N(EVS_NpcInit_Skolar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Skolar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Skolar, false)
    Call(SetNpcPos, NPC_Skolar, 33, 45, -95)
    Return
    End
};

EvtScript N(EVS_NpcInit_Muskular_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Muskular, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Muskular, false)
    Call(SetNpcPos, NPC_Muskular, 71, 45, -132)
    Return
    End
};

EvtScript N(EVS_NpcInit_Misstar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Misstar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Misstar, false)
    Call(SetNpcPos, NPC_Misstar, 131, 45, -132)
    Return
    End
};

EvtScript N(EVS_NpcInit_Klevar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Klevar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Klevar, false)
    Call(SetNpcPos, NPC_Klevar, 169, 45, -95)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kalmar_Npc2) = {
    Call(SetNpcImgFXParams, NPC_Kalmar, IMGFX_SET_ALPHA, 0, 0, 0, 0)
    Call(EnableNpcShadow, NPC_Kalmar, false)
    Call(SetNpcPos, NPC_Kalmar, 156, 45, -27)
    Return
    End
};

AnimID N(LimitAnims_Bowser_Npc2)[] = {
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_Shock,
    ANIM_WorldBowser_RearUpLaugh,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Peach_Npc2)[] = {
    ANIM_Peach1_Idle,
    ANIM_Peach1_Walk,
    ANIM_Peach2_RaiseArms,
    ANIM_Peach2_GaspStill,
    ANIM_Peach2_TiedIdle,
    ANIM_Peach3_TiedTalk,
    ANIM_Peach2_TalkIdle,
    ANIM_Peach3_Pray,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy_Npc2)[] = {
    ANIM_BattleKammy_FlyStill,
    ANIM_BattleKammy_FlyTalk,
    ANIM_BattleKammy_Broom,
    ANIM_BattleKammy_Slump,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Twink_Npc2)[] = {
    ANIM_Twink_Idle,
    ANIM_Twink_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Eldstar_Npc2)[] = {
    ANIM_WorldEldstar_Idle,
    ANIM_WorldEldstar_Wave,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Mamar_Npc2)[] = {
    ANIM_WorldMamar_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Skolar_Npc2)[] = {
    ANIM_WorldSkolar_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Muskular_Npc2)[] = {
    ANIM_WorldMuskular_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Misstar_Npc2)[] = {
    ANIM_WorldMisstar_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Klevar_Npc2)[] = {
    ANIM_WorldKlevar_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kalmar_Npc2)[] = {
    ANIM_WorldKalmar_Idle,
    ANIM_LIST_END
};

NpcData N(NpcData_Bowser_Npc2) = {
    .id = NPC_Bowser_02,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Bowser_Npc2),
    .settings = &N(NpcSettings_Bowser),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
    .limitAnimations = N(LimitAnims_Bowser_Npc2),
};

NpcData N(NpcData_Peach_Npc2) = {
    .id = NPC_Peach_01,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Peach_Npc2),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
    .limitAnimations = N(LimitAnims_Peach_Npc2),
};

NpcData N(NpcData_Kammy_Npc2)[] = {
    {
        .id = NPC_Kammy_03,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Kammy_Broom_Npc2),
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
        .limitAnimations = N(LimitAnims_Kammy_Npc2),
    },
    {
        .id = NPC_Kammy_04,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Kammy_Npc2),
        .settings = &N(NpcSettings_Kammy_Flying),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
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
        .limitAnimations = N(LimitAnims_Kammy_Npc2),
    },
};

NpcData N(NpcData_Twink_Npc2) = {
    .id = NPC_Twink_01,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Twink_Npc2),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = TWINK_ANIMS,
    .limitAnimations = N(LimitAnims_Twink_Npc2),
};

NpcData N(NpcData_Eldstar_Npc2) = {
    .id = NPC_Eldstar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Eldstar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = ELDSTAR_ANIMS,
    .limitAnimations = N(LimitAnims_Eldstar_Npc2),
};

NpcData N(NpcData_Mamar_Npc2) = {
    .id = NPC_Mamar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Mamar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = MAMAR_ANIMS,
    .limitAnimations = N(LimitAnims_Mamar_Npc2),
};

NpcData N(NpcData_Skolar_Npc2) = {
    .id = NPC_Skolar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Skolar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = SKOLAR_ANIMS,
    .limitAnimations = N(LimitAnims_Skolar_Npc2),
};

NpcData N(NpcData_Muskular_Npc2) = {
    .id = NPC_Muskular,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Muskular_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = MUSKULAR_ANIMS,
    .limitAnimations = N(LimitAnims_Muskular_Npc2),
};

NpcData N(NpcData_Misstar_Npc2) = {
    .id = NPC_Misstar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Misstar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = MISSTAR_ANIMS,
    .limitAnimations = N(LimitAnims_Misstar_Npc2),
};

NpcData N(NpcData_Klevar_Npc2) = {
    .id = NPC_Klevar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Klevar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = KLEVAR_ANIMS,
    .limitAnimations = N(LimitAnims_Klevar_Npc2),
};

NpcData N(NpcData_Kalmar_Npc2) = {
    .id = NPC_Kalmar,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Kalmar_Npc2),
    .settings = &N(NpcSettings_StarSpirit),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = KALMAR_ANIMS,
    .limitAnimations = N(LimitAnims_Kalmar_Npc2),
};

NpcGroupList N(MidpointNpcs) = {
    NPC_GROUP(N(NpcData_Bowser_Npc2), BTL_KPA2_FORMATION_04),
    NPC_GROUP(N(NpcData_Peach_Npc2)),
    NPC_GROUP(N(NpcData_Kammy_Npc2), BTL_KKJ_FORMATION_00),
    NPC_GROUP(N(NpcData_Twink_Npc2)),
    NPC_GROUP(N(NpcData_Eldstar_Npc2)),
    NPC_GROUP(N(NpcData_Mamar_Npc2)),
    NPC_GROUP(N(NpcData_Skolar_Npc2)),
    NPC_GROUP(N(NpcData_Muskular_Npc2)),
    NPC_GROUP(N(NpcData_Misstar_Npc2)),
    NPC_GROUP(N(NpcData_Klevar_Npc2)),
    NPC_GROUP(N(NpcData_Kalmar_Npc2)),
    {}
};
