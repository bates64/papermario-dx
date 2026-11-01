#include "nok_12.h"

#include "world/common/enemy/KoopaTroopa/wander.inc.c"
#include "world/common/enemy/KoopaTroopa/patrol.inc.c"
#include "world/common/enemy/Goomba/wander.inc.c"
#include "world/common/enemy/SpikedGoomba/wander.inc.c"
#include "world/common/enemy/SpikedGoomba/patrol.inc.c"

// 'sleep' on top of brick block until it's broken
EvtScript EVS_NpcIdle_SpikedGoomba = {
    Label(0)
    Call(GetSelfVar, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(1)
        Goto(0)
    EndIf
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Sleep)
    Thread
        Call(PlaySoundAtNpc, NPC_SELF, SOUND_AI_FOUND_PLAYER_JUMP, SOUND_SPACE_DEFAULT)
        Call(MakeLerp, -90, 0, 10, EASING_LINEAR)
        Label(1)
        Call(UpdateLerp)
        Call(SetNpcRotation, NPC_SELF, LVar0, 0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
        Call(GetNpcPos, NPC_SELF, LVarA, LVarB, LVarC)
        Call(MakeLerp, 0, 360, 15, EASING_LINEAR)
        Label(2)
        Call(UpdateLerp)
        Call(SetNpcRotation, NPC_SELF, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
        Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
    EndThread
    Call(SetNpcJumpscale, NPC_SELF, 0.7)
    Call(NpcJump0, NPC_SELF, -65, 0, -120, 25)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Hurt)
    Wait(20)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Idle)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_SpikedGoomba_Wander)
    Return
    End
};

EvtScript EVS_NpcInit_SpikedGoomba = {
    Call(SetNpcPos, NPC_SELF, -165, 86, -118)
    Call(SetNpcRotation, NPC_SELF, -85, 0, 0)
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_SpikedGoomba)
    Return
    End
};

EvtScript EVS_NpcIdle_KoopaTroopa_02 = {
    Return
    End
};

EvtScript EVS_KoopaTroopa_Demo_MissAttack = {
    Wait(45)
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_ShellEnter)
    Wait(8)
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_ShellSpin)
    Wait(6)
    Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 80)
    Add(LVar2, 100)
    Call(NpcMoveTo, NPC_SELF, LVar0, LVar2, 12)
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_ShellExit)
    Wait(8)
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_Idle)
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa_02 = {
    Call(GetEntryID, LVar0)
    IfGe(LVar0, $Entry2.index)
        Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_KoopaTroopa_02)
        Call(SetNpcPos, NPC_SELF, 310, 0, -165)
    EndIf
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa_02_Demo = {
    Call(GetEntryID, LVar0)
    IfGe(LVar0, $Entry2.index)
        Call(BindNpcIdle, NPC_SELF, EVS_KoopaTroopa_Demo_MissAttack)
    EndIf
    Return
    End
};

NpcData NpcData_KoopaTroopa_01 = {
    .id = NPC_KoopaTroopa_01,
    .pos = $KoopaTroopa_01.pos,
    .yaw = $KoopaTroopa_01.yaw,
    .territory = $KoopaTroopa_01.territory,
    .settings = &NpcSettings_KoopaTroopa_Patrol,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPA_TROOPA_NOK_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_KoopaTroopa_02 = {
    .id = NPC_KoopaTroopa_02,
    .pos = $KoopaTroopa_02.pos,
    .yaw = $KoopaTroopa_02.yaw,
    .territory = $KoopaTroopa_02.territory,
    .init = &EVS_NpcInit_KoopaTroopa_02,
    .settings = &NpcSettings_KoopaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPA_TROOPA_NOK_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_KoopaTroopa_02_Demo = {
    .id = NPC_KoopaTroopa_02,
    .pos = $KoopaTroopa_02_1.pos,
    .yaw = $KoopaTroopa_02_1.yaw,
    .territory = $KoopaTroopa_02_1.territory,
    .init = &EVS_NpcInit_KoopaTroopa_02_Demo,
    .settings = &NpcSettings_KoopaTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPA_TROOPA_NOK_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Goomba = {
    .id = NPC_Goomba,
    .pos = $Goomba.pos,
    .yaw = $Goomba.yaw,
    .territory = $Goomba.territory,
    .settings = &NpcSettings_Goomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = GOOMBA_DROPS,
    .animations = GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_SpikedGoomba = {
    .id = NPC_SpikedGoomba,
    .pos = $SpikedGoomba.pos,
    .yaw = $SpikedGoomba.yaw,
    .territory = $SpikedGoomba.territory,
    .init = &EVS_NpcInit_SpikedGoomba,
    .settings = &NpcSettings_SpikedGoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SPIKED_GOOMBA_DROPS,
    .animations = SPIKED_GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_KoopaTroopa_01, "nok:koopa_troopa_2", "nok_01"),
    NPC_GROUP(NpcData_KoopaTroopa_02, "nok:koopa_troopa_1_spiked_goomba_1_paragoomba_1", "nok_01"),
    NPC_GROUP(NpcData_Goomba, "nok:goomba_1_spiked_goomba_1", "nok_02"),
    NPC_GROUP(NpcData_SpikedGoomba, "nok:spiked_goomba_2", "nok_02"),
    {}
};

NpcGroupList DemoNPCs = {
    NPC_GROUP(NpcData_KoopaTroopa_01, "nok:koopa_troopa_2", "nok_01"),
    NPC_GROUP(NpcData_KoopaTroopa_02_Demo, "nok:koopa_troopa_1_spiked_goomba_1_paragoomba_1", "nok_01"),
    NPC_GROUP(NpcData_Goomba, "nok:goomba_1_spiked_goomba_1", "nok_02"),
    NPC_GROUP(NpcData_SpikedGoomba, "nok:spiked_goomba_2", "nok_02"),
    {}
};
