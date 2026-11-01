#include "tik_04.h"

#include "world/common/enemy/SpikedGloomba/wander.inc.c"

EvtScript EVS_NpcIdle_SpikedGloomba = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SpringRoom.index)
            Call(SetNpcPos, NPC_SELF, 280, -10, 0)
        CaseEq($ElevatorAtticRoom.index)
            Call(BindNpcAI, NPC_SELF, EVS_NpcAI_SpikedGloomba_Wander)
            Return
        CaseEq($ShortElevatorRoom.index)
            Call(SetNpcPos, NPC_SELF, 280, -10, 0)
        CaseEq($MetalBlockRoom.index)
            Call(SetNpcPos, NPC_SELF, 360, -10, 0)
    EndSwitch
    Label(100)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    IfLt(LVar0, -30)
        Wait(1)
        Goto(100)
    EndIf
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Dark_Run)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_FLYING | NPC_FLAG_NO_SHADOW_RAYCAST, false)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, true)
    Call(SetNpcSpeed, NPC_SELF, 2)
    Call(GetSelfNpcID, LVar0)
    IfEq(LVar0, 0)
        Call(NpcMoveTo, NPC_SELF, 55, 0, 0)
    Else
        Wait(14)
        Call(NpcMoveTo, NPC_SELF, 60, 0, 0)
    EndIf
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Dark_Idle)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_SpikedGloomba_Wander)
    Return
    End
};

EvtScript EVS_NpcInit_SpikedGloomba = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_SpikedGloomba)
    Return
    End
};

NpcData NpcData_SpikedGloomba_01 = {
    .id = NPC_SpikedGoomba_01,
    .pos = $SpikedGoomba_01.pos,
    .yaw = $SpikedGoomba_01.yaw,
    .territory = $SpikedGoomba_01.territory,
    .init = &EVS_NpcInit_SpikedGloomba,
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcData NpcData_SpikedGloomba_02 = {
    .id = NPC_SpikedGoomba_02,
    .pos = $SpikedGoomba_02.pos,
    .yaw = $SpikedGoomba_02.yaw,
    .territory = $SpikedGoomba_02.territory,
    .init = &EVS_NpcInit_SpikedGloomba,
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpikedGloomba_01, "tik:spiked_gloomba_1_gloomba_2", "tik_02"),
    NPC_GROUP(NpcData_SpikedGloomba_02, "tik:spiked_gloomba_2", "tik_02"),
    {}
};
