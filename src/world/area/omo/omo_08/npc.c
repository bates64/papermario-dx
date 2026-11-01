#include "omo_08.h"

#include "world/common/npc/TrainToad/idle.inc.c"
#include "world/common/enemy/ShyGuy/wander.inc.c"

EvtScript EVS_NpcInteract_Conductor = {
    Call(DisablePlayerInput, true)
    ExecWait(EVS_Conductor_ChooseRoute)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_NpcInit_Conductor = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Conductor)
    Return
    End
};

EvtScript EVS_NpcInteract_TrainToad = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH4_SOLVED_COLOR_PUZZLE)
            Call(FindItem, ITEM_MYSTERY_NOTE, LVar0)
            IfEq(LVar0, -1)
                IfEq(GF_OMO09_SpawnedPeachChoice3, false)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002B)
                Else
                    IfEq(GF_OMO09_Chest_Dictionary, false)
                        Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002C)
                    Else
                        Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002F)
                    EndIf
                EndIf
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002D)
            EndIf
        CaseLt(STORY_CH4_WATT_JOINED_PARTY)
            Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002E)
        CaseLt(STORY_CH4_DEFEATED_GENERAL_GUY)
            Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_002F)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_TrainToad_Green_Talk, ANIM_TrainToad_Green_Idle, 0, MSG_CH4_0030)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_TrainToad = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_TrainToad)
    Return
    End
};

EvtScript EVS_NpcAI_BoxedShyGuy = {
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
                IfEq(LVar1, 0)
                    Call(SetSelfVar, 0, 1)
                    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_ShyGuy_Wander)
                EndIf
            CaseEq(2)
                Call(DisablePlayerInput, true)
                Wait(25)
                Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE, false)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
                Call(SetSelfVar, 0, 0)
                Call(DisablePlayerInput, false)
        EndSwitch
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_NpcDefeat_BoxedShyGuy = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, 0, 2)
            Call(BindNpcAI, NPC_SELF, EVS_NpcAI_BoxedShyGuy)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_BoxedShyGuy = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcAI_BoxedShyGuy)
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_BoxedShyGuy)
    Return
    End
};

NpcData NpcData_Toads[] = {
    {
        .id = NPC_Conductor,
        .pos = $Conductor.pos,
        .yaw = $Conductor.yaw,
        .init = &EVS_NpcInit_Conductor,
        .settings = &NpcSettings_TrainToad,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TRAIN_CONDUCTOR_ANIMS,
        .tattle = MSG_NpcTattle_OMO_TrainConductor,
    },
    {
        .id = NPC_TrainToad,
        .pos = $TrainToad.pos,
        .yaw = $TrainToad.yaw,
        .init = &EVS_NpcInit_TrainToad,
        .settings = &NpcSettings_TrainToad,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TRAIN_TOAD_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_OMO_TrainConductor,
    },
};

NpcData NpcData_ShyGuy_01 = {
    .id = NPC_ShyGuy_01,
    .pos = $ShyGuy_01.pos,
    .yaw = $ShyGuy_01.yaw,
    .territory = $ShyGuy_01.territory,
    .init = &EVS_NpcInit_BoxedShyGuy,
    .settings = &NpcSettings_ShyGuy_Wander,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
};

NpcData NpcData_ShyGuy_02 = {
    .id = NPC_ShyGuy_02,
    .pos = $ShyGuy_02.pos,
    .yaw = $ShyGuy_02.yaw,
    .territory = $ShyGuy_02.territory,
    .init = &EVS_NpcInit_BoxedShyGuy,
    .settings = &NpcSettings_ShyGuy_Wander,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
};

NpcData NpcData_ShyGuy_03 = {
    .id = NPC_ShyGuy_03,
    .pos = $ShyGuy_03.pos,
    .yaw = $ShyGuy_03.yaw,
    .territory = $ShyGuy_03.territory,
    .init = &EVS_NpcInit_BoxedShyGuy,
    .settings = &NpcSettings_ShyGuy_Wander,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
};

NpcData NpcData_ShyGuy_04 = {
    .id = NPC_ShyGuy_04,
    .pos = $ShyGuy_04.pos,
    .yaw = $ShyGuy_04.yaw,
    .territory = $ShyGuy_04.territory,
    .init = &EVS_NpcInit_BoxedShyGuy,
    .settings = &NpcSettings_ShyGuy_Wander,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Toads),
    NPC_GROUP(NpcData_ShyGuy_01, "omo3:shy_guy_1", "omo_05:b"),
    NPC_GROUP(NpcData_ShyGuy_02, "omo3:shy_guy_1", "omo_05:b"),
    NPC_GROUP(NpcData_ShyGuy_03, "omo3:shy_guy_1", "omo_05:b"),
    NPC_GROUP(NpcData_ShyGuy_04, "omo3:shy_guy_1", "omo_05:b"),
    {}
};
