#include "kkj_25.h"
#include "sprite/player.h"

s32 N(FlyingKammyHoverOffsets_Npc3)[] = {
    1, 2, 3, 2, 1, -1, -2, -3, -2, -1,
};

EvtScript N(EVS_NpcAux_Kammy_Broom_Npc3) = {
    Label(0)
        UseBuf(Ref(N(FlyingKammyHoverOffsets_Npc3)))
        Loop(10)
            BufRead1(LVar1)
            Call(GetNpcPos, NPC_Kammy_05, LVar2, LVar3, LVar4)
            Add(LVar3, LVar1)
            Call(SetNpcPos, NPC_Kammy_05, LVar2, LVar3, LVar4)
            Wait(3)
        EndLoop
        Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInit_StarRod_Npc3) = {
    Call(SetNpcPos, NPC_StarRod, 270, 0, 0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bowser_03_Npc3) = {
    Call(SetNpcAnimation, NPC_Bowser_03, ANIM_WorldBowser_DefeatedIdle)
    Call(SetNpcPos, NPC_Bowser_03, 300, 0, 50)
    Return
    End
};

EvtScript N(EVS_NpcInit_Peach_Npc3) = {
    Call(SetNpcCollisionSize, NPC_Peach_02, 48, 24)
    Call(SetNpcPos, NPC_Peach_02, 400, 0, 0)
    Call(SetNpcAnimation, NPC_Peach_02, ANIM_Peach1_Idle)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kammy_Broom_Npc3) = {
    Call(BindNpcAux, NPC_SELF, Ref(N(EVS_NpcAux_Kammy_Broom_Npc3)))
    Call(SetNpcPos, NPC_Kammy_05, 525, 10, 0)
    Call(SetNpcAnimation, NPC_Kammy_05, ANIM_BattleKammy_FlyStill)
    Call(InterpNpcYaw, NPC_Kammy_05, 270, 0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Twink_02_Npc3) = {
    Call(SetNpcPos, NPC_Twink_02, 430, 30, 0)
    Return
    End
};

AnimID N(LimitAnims_Bowser_Npc3)[] = {
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_Shock,
    ANIM_WorldBowser_DefeatedIdle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Peach_Npc3)[] = {
    ANIM_Peach1_Idle,
    ANIM_Peach1_Walk,
    ANIM_Peach2_RaiseArms,
    ANIM_Peach2_GaspStill,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy_Npc3)[] = {
    ANIM_BattleKammy_FlyStill,
    ANIM_BattleKammy_FlyTalk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Twink_Npc3)[] = {
    ANIM_Twink_Idle,
    ANIM_Twink_Talk,
    ANIM_Twink_Cringe,
    ANIM_LIST_END
};

NpcData N(NpcData_Bowser_Npc3) = {
    .id = NPC_Bowser_03,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Bowser_03_Npc3),
    .settings = &N(NpcSettings_Bowser),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = BOWSER_ANIMS,
    .limitAnimations = N(LimitAnims_Bowser_Npc3),
};

NpcData N(NpcData_Peach_Npc3) = {
    .id = NPC_Peach_02,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Peach_Npc3),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
    .limitAnimations = N(LimitAnims_Peach_Npc3),
};

NpcData N(NpcData_Kammy_Npc3) = {
    .id = NPC_Kammy_05,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Kammy_Broom_Npc3),
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
    .limitAnimations = N(LimitAnims_Kammy_Npc3),
};

NpcData N(NpcData_Twink_Npc3) = {
    .id = NPC_Twink_02,
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_Twink_02_Npc3),
    .settings = &N(NpcSettings_Dummy),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = TWINK_ANIMS,
    .limitAnimations = N(LimitAnims_Twink_Npc3),
};

NpcData N(NpcData_StarRod_Npc3) = {
    .id = NPC_StarRod,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &N(EVS_NpcInit_StarRod_Npc3),
    .settings = &N(NpcSettings_StarRod),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = STAR_ROD_ANIMS,
};

NpcGroupList N(FinaleNpcs) = {
    NPC_GROUP(N(NpcData_Bowser_Npc3), BTL_KPA2_FORMATION_03),
    NPC_GROUP(N(NpcData_Peach_Npc3)),
    NPC_GROUP(N(NpcData_Kammy_Npc3), BTL_KKJ_FORMATION_00),
    NPC_GROUP(N(NpcData_Twink_Npc3)),
    NPC_GROUP(N(NpcData_StarRod_Npc3)),
    {}
};
