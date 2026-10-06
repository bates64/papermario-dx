#include "isk_16.h"

EvtScript EVS_NpcIdle_Tutankoopa_01 = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, 0)
            Goto(0)
        EndIf
    Call(StartBossBattle, SONG_TUTANKOOPA_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Tutankoopa_01 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetEncounterStatusFlags, ENCOUNTER_FLAG_THUMBS_UP, true)
            Call(InterpPlayerYaw, 90, 0)
            ExecWait(EVS_Scene_TutankoopaDefeated)
            Exec(EVS_SpawnStarCard)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Tutankoopa_01 = {
    Call(InterpNpcYaw, NPC_Tutankoopa_01, 150, 1)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Tutankoopa_01))
            Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Tutankoopa_01))
        CaseGe(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(SetNpcPos, NPC_Tutankoopa_01, 0, -1500, 0)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_ChainChomp = {
    Return
    End
};

NpcSettings NpcSettings_Tutankoopa_01 = {
    .defaultAnim = ANIM_Tutankoopa_Idle,
    .height = 40,
    .radius = 36,
};

NpcSettings NpcSettings_ChainChomp = {
    .defaultAnim = ANIM_ChainChomp_QuickBite,
    .height = 32,
    .radius = 32,
};

NpcSettings NpcSettings_Tutankoopa_02 = {
    .defaultAnim = ANIM_Tutankoopa_Still,
    .height = 40,
    .radius = 36,
};

NpcData NpcData_Tutankoopa[] = {
    {
        .id = NPC_Tutankoopa_01,
        .pos = { 457.0f, -1300.0f, 316.0f },
        .yaw = 230,
        .init = &EVS_NpcInit_Tutankoopa_01,
        .initVarCount = 1,
        .initVar = { .value = 0 },
        .settings = &NpcSettings_Tutankoopa_01,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Tutankoopa_Idle,
            .walk   = ANIM_Tutankoopa_Idle,
            .run    = ANIM_Tutankoopa_Idle,
            .chase  = ANIM_Tutankoopa_Idle,
            .alert  = ANIM_Tutankoopa_Idle,
            .unused = ANIM_Tutankoopa_Idle,
            .death  = ANIM_Tutankoopa_Hurt,
            .hit    = ANIM_Tutankoopa_Hurt,
            .anim_8 = ANIM_Tutankoopa_Idle,
            .anim_9 = ANIM_Tutankoopa_Idle,
            .anim_A = ANIM_Tutankoopa_Idle,
            .anim_B = ANIM_Tutankoopa_Idle,
            .anim_C = ANIM_Tutankoopa_Idle,
            .anim_D = ANIM_Tutankoopa_Idle,
            .anim_E = ANIM_Tutankoopa_Idle,
            .anim_F = ANIM_Tutankoopa_Idle,
        },
    },
    {
        .id = NPC_Tutankoopa_02,
        .pos = { 500.0f, -1300.0f, 316.0f },
        .yaw = 230,
        .settings = &NpcSettings_Tutankoopa_02,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Tutankoopa_Idle,
            .walk   = ANIM_Tutankoopa_Idle,
            .run    = ANIM_Tutankoopa_Idle,
            .chase  = ANIM_Tutankoopa_Idle,
            .alert  = ANIM_Tutankoopa_Idle,
            .unused = ANIM_Tutankoopa_Idle,
            .death  = ANIM_Tutankoopa_Hurt,
            .hit    = ANIM_Tutankoopa_Hurt,
            .anim_8 = ANIM_Tutankoopa_Idle,
            .anim_9 = ANIM_Tutankoopa_Idle,
            .anim_A = ANIM_Tutankoopa_Idle,
            .anim_B = ANIM_Tutankoopa_Idle,
            .anim_C = ANIM_Tutankoopa_Idle,
            .anim_D = ANIM_Tutankoopa_Idle,
            .anim_E = ANIM_Tutankoopa_Idle,
            .anim_F = ANIM_Tutankoopa_Idle,
        },
    },
};

NpcData NpcData_ChainChomp = {
    .id = NPC_ChainChomp,
    .pos = { 457.0f, -1300.0f, 316.0f },
    .yaw = 230,
    .init = &EVS_NpcInit_ChainChomp,
    .settings = &NpcSettings_ChainChomp,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = {
        .idle   = ANIM_ChainChomp_Still,
        .walk   = ANIM_ChainChomp_Still,
        .run    = ANIM_ChainChomp_Still,
        .chase  = ANIM_ChainChomp_Still,
        .alert  = ANIM_ChainChomp_Still,
        .unused = ANIM_ChainChomp_Still,
        .death  = ANIM_ChainChomp_Still,
        .hit    = ANIM_ChainChomp_Still,
        .anim_8 = ANIM_ChainChomp_Still,
        .anim_9 = ANIM_ChainChomp_Still,
        .anim_A = ANIM_ChainChomp_Still,
        .anim_B = ANIM_ChainChomp_Still,
        .anim_C = ANIM_ChainChomp_Still,
        .anim_D = ANIM_ChainChomp_Still,
        .anim_E = ANIM_ChainChomp_Still,
        .anim_F = ANIM_ChainChomp_Still,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Tutankoopa, "isk_part_2:tutankoopa", "isk_01"),
    NPC_GROUP(NpcData_ChainChomp),
    {}
};
