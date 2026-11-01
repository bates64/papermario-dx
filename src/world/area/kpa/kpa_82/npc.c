#include "kpa_82.h"

#include "world/common/enemy/Goomba/base.h"
#include "world/common/enemy/KoopaTroopa/base.h"
#include "world/common/enemy/DarkTroopa/base.h"
#include "world/common/enemy/ShyGuy/base.h"
#include "world/common/npc/Bobomb/base.h"

enum {
    ANSWER_CORRECT  = 0,
    ANSWER_WRONG  = 1,
};

#include "world/common/enemy/ShyGuy/idle.inc.c"

MobileAISettings AISettings_Short = {
    .moveSpeed = 5.0f,
    .moveTime = 1,
    .alertRadius = 1.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 6.0f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 1.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Short = {
    Call(BasicAI_Main, AISettings_Short)
    Return
    End
};

NpcSettings NpcSettings_Short = {
    .height = 22,
    .radius = 24,
    .level = ACTOR_LEVEL_GOOMBA,
    .doAI = &EVS_NpcAI_Short,
};

MobileAISettings AISettings_Koopa = {
    .moveSpeed = 5.0f,
    .moveTime = 1,
    .alertRadius = 1.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 6.0f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 1.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_KoopaTroopa_Wander = {
    Call(BasicAI_Main, AISettings_Koopa)
    Return
    End
};

NpcSettings NpcSettings_KoopaTroopa_Wander = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_DARK_KOOPA,
    .doAI = &EVS_NpcAI_KoopaTroopa_Wander,
};

MobileAISettings AISettings_ShyGuy_Wander = {
    .moveSpeed = 5.0f,
    .moveTime = 1,
    .alertRadius = 1.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 6.0f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 1.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ShyGuy_Wander = {
    Call(BasicAI_Main, AISettings_ShyGuy_Wander)
    Return
    End
};

NpcSettings NpcSettings_ShyGuy_Wander = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .doAI = &EVS_NpcAI_ShyGuy_Wander,
};

EvtScript EVS_SetCam_MeetingDoor = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, 3.0 / DT)
    Call(SetCamPitch, CAM_DEFAULT, 11.0, -10.0)
    Call(SetCamDistance, CAM_DEFAULT, 450.0)
    Call(SetCamPosA, CAM_DEFAULT, 88.0, 256.6)
    Call(SetCamPosB, CAM_DEFAULT, 195.0, 142.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetCam_AfterBattle = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, 3.0 / DT)
    Call(SetCamPitch, CAM_DEFAULT, 5.0, -14.0)
    Call(SetCamDistance, CAM_DEFAULT, 375.0)
    Call(SetCamPosA, CAM_DEFAULT, 88.0, 256.6)
    Call(SetCamPosB, CAM_DEFAULT, 195.0, 142.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetCam_AfterResult = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(SetCamPitch, CAM_DEFAULT, 11.0, -14.0)
    Call(SetCamDistance, CAM_DEFAULT, 450.0)
    Call(SetCamPosA, CAM_DEFAULT, 88.0, 256.6)
    Call(SetCamPosB, CAM_DEFAULT, 195.0, 142.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetCam_AskQuestion = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(SetCamPitch, CAM_DEFAULT, 11.0, -10.5)
    Call(SetCamPosA, CAM_DEFAULT, 88.0, 256.6)
    Call(SetCamPosB, CAM_DEFAULT, 195.0, 142.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetCam_ViewRoom = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, LVar6)
    Call(SetCamDistance, CAM_DEFAULT, 470.0)
    Call(SetCamPitch, CAM_DEFAULT, 16.0, -9.0)
    Call(SetCamPosA, CAM_DEFAULT, -2.5, 300.0)
    Call(SetCamPosB, CAM_DEFAULT, -2.5, 200.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetCam_BeforeBattle = {
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamSpeed, CAM_DEFAULT, LVar6)
    Call(SetCamDistance, CAM_DEFAULT, 470.0)
    Call(SetCamPitch, CAM_DEFAULT, 16.0, -9.0)
    Call(SetCamPosA, CAM_DEFAULT, 50.0, 300.0)
    Call(SetCamPosB, CAM_DEFAULT, 50.0, 200.0)
    Call(SetCamPosC, CAM_DEFAULT, 0.0, 0.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Return
    End
};

EvtScript EVS_SetDoorRots = {
    Call(MakeLerp, 0, 60, 30 * DT, EASING_LINEAR)
    Call(PlaySound, SOUND_KPA_QUIZ_DOORS_OPEN)
    Label(0)
        Call(UpdateLerp)
        Call(TranslateModel, MODEL_o100, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o101, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o145, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o146, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o102, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o103, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Call(StopSound, SOUND_NONE)
    Return
    End
};

EvtScript EVS_CloseDoors = {
    Call(MakeLerp, 60, 0, 30 * DT, EASING_LINEAR)
    Call(PlaySound, SOUND_KPA_QUIZ_DOORS_CLOSE)
    Label(0)
        Call(UpdateLerp)
        Call(TranslateModel, MODEL_o100, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o101, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o145, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o146, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o102, 0, LVar0, 0)
        Call(TranslateModel, MODEL_o103, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Call(StopSound, SOUND_NONE)
    Return
    End
};

EvtScript EVS_ReleaseFrom_Door_0 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(SetNpcPos, NPC_SELF, -100, 0, 0)
    Call(RandInt, 40, LVar1)
    Add(LVar1, -120)
    Call(NpcMoveTo, NPC_SELF, LVar1, 150, 30 * DT)
    Call(SetNpcAnimation, NPC_SELF, LVar4)
    Call(BindNpcAI, NPC_SELF, LVar5)
    Return
    End
};

EvtScript EVS_ReleaseFrom_Door_1 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(SetNpcPos, NPC_SELF, 0, 0, 0)
    Call(RandInt, 40, LVar1)
    Add(LVar1, -20)
    Call(NpcMoveTo, NPC_SELF, LVar1, 150, 30 * DT)
    Call(SetNpcAnimation, NPC_SELF, LVar4)
    Call(BindNpcAI, NPC_SELF, LVar5)
    Return
    End
};

EvtScript EVS_ReleaseFrom_Door_2 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(SetNpcPos, NPC_SELF, 100, 0, 0)
    Call(RandInt, 40, LVar1)
    Add(LVar1, 80)
    Call(NpcMoveTo, NPC_SELF, LVar1, 150, 30 * DT)
    Call(SetNpcAnimation, NPC_SELF, LVar4)
    Call(BindNpcAI, NPC_SELF, LVar5)
    Return
    End
};

EvtScript EVS_WithdrawTo_Door_0 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(RandInt, 20 * DT, LVar1)
    Add(LVar1, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, -100, 0, LVar1)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Return
    End
};

EvtScript EVS_WithdrawTo_Door_1 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(RandInt, 20 * DT, LVar1)
    Add(LVar1, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, 0, 0, LVar1)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Return
    End
};

EvtScript EVS_WithdrawTo_Door_2 = {
    Call(SetNpcAnimation, NPC_SELF, LVar3)
    Call(RandInt, 20 * DT, LVar1)
    Add(LVar1, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, 100, 0, LVar1)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Return
    End
};

EvtScript EVS_ReleaseFrom_RandomDoor = {
    Call(RandInt, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(EVS_ReleaseFrom_Door_0)
        CaseEq(1)
            ExecWait(EVS_ReleaseFrom_Door_1)
        CaseEq(2)
            ExecWait(EVS_ReleaseFrom_Door_2)
    EndSwitch
    Return
    End
};

EvtScript EVS_WithdrawTo_RandomDoor = {
    Call(RandInt, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(EVS_WithdrawTo_Door_0)
        CaseEq(1)
            ExecWait(EVS_WithdrawTo_Door_1)
        CaseEq(2)
            ExecWait(EVS_WithdrawTo_Door_2)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcIdle_Goomba = {
    Return
    End
};

EvtScript EVS_Release_Goomba = {
    Set(LVar3, ANIM_Goomba_Run)
    Set(LVar4, ANIM_Goomba_Idle)
    Set(LVar5, EVS_NpcAI_Short)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_Goomba = {
    Set(LVar3, ANIM_Goomba_Run)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_NpcIdle_ShyGuy = {
    Return
    End
};

EvtScript EVS_Release_RedShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Red_Dash)
    Set(LVar4, ANIM_ShyGuy_Red_Idle)
    Set(LVar5, EVS_NpcAI_ShyGuy_Wander)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_RedShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Red_Dash)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_Release_RedShyGuy_Door_1 = {
    Set(LVar3, ANIM_ShyGuy_Red_Dash)
    Set(LVar4, ANIM_ShyGuy_Red_Idle)
    Set(LVar5, EVS_NpcAI_ShyGuy_Wander)
    ExecWait(EVS_ReleaseFrom_Door_1)
    Return
    End
};

EvtScript EVS_Withdraw_RedShyGuy_Door_1 = {
    Set(LVar3, ANIM_ShyGuy_Red_Dash)
    ExecWait(EVS_WithdrawTo_Door_1)
    Return
    End
};

EvtScript EVS_Release_BlueShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Blue_Dash)
    Set(LVar4, ANIM_ShyGuy_Blue_Idle)
    Set(LVar5, EVS_NpcAI_ShyGuy_Wander)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_BlueShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Blue_Dash)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_Release_BlueShyGuy_Door_2 = {
    Set(LVar3, ANIM_ShyGuy_Blue_Dash)
    Set(LVar4, ANIM_ShyGuy_Blue_Idle)
    Set(LVar5, EVS_NpcAI_ShyGuy_Wander)
    ExecWait(EVS_ReleaseFrom_Door_2)
    Return
    End
};

EvtScript EVS_Withdraw_BlueShyGuy_Door_2 = {
    Set(LVar3, ANIM_ShyGuy_Blue_Dash)
    ExecWait(EVS_WithdrawTo_Door_2)
    Return
    End
};

EvtScript EVS_Release_GreenShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Green_Dash)
    Set(LVar4, ANIM_ShyGuy_Green_Idle)
    Set(LVar5, EVS_NpcAI_ShyGuy_Wander)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_GreenShyGuy = {
    Set(LVar3, ANIM_ShyGuy_Green_Dash)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_NpcIdle_KoopaTroopa = {
    Return
    End
};

EvtScript EVS_Release_DarkTroopa = {
    Set(LVar3, ANIM_KoopaTroopa_Dark_Run)
    Set(LVar4, ANIM_KoopaTroopa_Dark_Idle)
    Set(LVar5, EVS_NpcAI_KoopaTroopa_Wander)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_DarkTroopa = {
    Set(LVar3, ANIM_KoopaTroopa_Dark_Run)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_Release_KoopaTroopa = {
    Set(LVar3, ANIM_KoopaTroopa_Run)
    Set(LVar4, ANIM_KoopaTroopa_Idle)
    Set(LVar5, EVS_NpcAI_KoopaTroopa_Wander)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_KoopaTroopa = {
    Set(LVar3, ANIM_KoopaTroopa_Run)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_NpcIdle_Bobomb = {
    Return
    End
};

EvtScript EVS_Release_Bobomb = {
    Set(LVar3, ANIM_WorldBobomb_Green_Run)
    Set(LVar4, ANIM_WorldBobomb_Green_Idle)
    Set(LVar5, EVS_NpcAI_Short)
    ExecWait(EVS_ReleaseFrom_RandomDoor)
    Return
    End
};

EvtScript EVS_Withdraw_Bobomb = {
    Set(LVar3, ANIM_WorldBobomb_Green_Run)
    ExecWait(EVS_WithdrawTo_RandomDoor)
    Return
    End
};

EvtScript EVS_Release_Bobomb_Door_0 = {
    Set(LVar3, ANIM_WorldBobomb_Green_Run)
    Set(LVar4, ANIM_WorldBobomb_Green_Idle)
    Set(LVar5, EVS_NpcAI_Short)
    ExecWait(EVS_ReleaseFrom_Door_0)
    Return
    End
};

EvtScript EVS_Withdraw_Bobomb_Door_0 = {
    Set(LVar3, ANIM_WorldBobomb_Green_Run)
    ExecWait(EVS_WithdrawTo_Door_0)
    Return
    End
};

// special 'script' used only to organize the quiz waves
#define QS_NEXT(npcID, script)  npcID, (s32) script,
#define QS_WAIT(n)  -2, n,
#define QS_END      -1,

s32 QS_Release_Wave_0[] = {
    QS_NEXT(NPC_DarkTroopa_01,  EVS_Release_DarkTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Goomba_01,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_DarkTroopa_02,  EVS_Release_DarkTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Goomba_02,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Goomba_03,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_DarkTroopa_03,  EVS_Release_DarkTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Goomba_04,      EVS_Release_Goomba)
    QS_END
};

s32 QS_Release_Wave_1[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Release_RedShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Release_RedShyGuy)
    QS_WAIT(10 * DT)
    QS_NEXT(NPC_RedShyGuy_03,   EVS_Release_RedShyGuy)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Release_BlueShyGuy)
    QS_WAIT(3 * DT)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Release_BlueShyGuy)
    QS_WAIT(6 * DT)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Release_BlueShyGuy)
    QS_WAIT(7 * DT)
    QS_NEXT(NPC_BlueShyGuy_04,  EVS_Release_BlueShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Release_GreenShyGuy)
    QS_WAIT(4 * DT)
    QS_NEXT(NPC_GreenShyGuy_02, EVS_Release_GreenShyGuy)
    QS_WAIT(6 * DT)
    QS_NEXT(NPC_GreenShyGuy_03, EVS_Release_GreenShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_GreenShyGuy_04, EVS_Release_GreenShyGuy)
    QS_END
};

s32 QS_Release_Wave_2[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Release_RedShyGuy_Door_1)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Release_BlueShyGuy_Door_2)
    QS_NEXT(NPC_Bobomb_01,      EVS_Release_Bobomb_Door_0)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Release_RedShyGuy_Door_1)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Release_BlueShyGuy_Door_2)
    QS_NEXT(NPC_Bobomb_02,      EVS_Release_Bobomb_Door_0)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Release_BlueShyGuy_Door_2)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_BlueShyGuy_04,  EVS_Release_BlueShyGuy_Door_2)
    QS_END
};

s32 QS_Release_Wave_3[] = {
    QS_NEXT(NPC_Goomba_01,      EVS_Release_Goomba)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Release_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_02, EVS_Release_KoopaTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Release_BlueShyGuy)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Release_GreenShyGuy)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Release_BlueShyGuy)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_Goomba_02,      EVS_Release_Goomba)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Release_BlueShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_KoopaTroopa_03, EVS_Release_KoopaTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_KoopaTroopa_04, EVS_Release_KoopaTroopa)
    QS_END
};

s32 QS_Release_Wave_4[] = {
    QS_NEXT(NPC_Goomba_01,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Release_KoopaTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_DarkTroopa_01,  EVS_Release_DarkTroopa)
    QS_END
};

s32 QS_Release_Wave_5[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Release_RedShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Release_RedShyGuy)
    QS_WAIT(4 * DT)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Release_GreenShyGuy)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_Bobomb_01,      EVS_Release_Bobomb)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Bobomb_02,      EVS_Release_Bobomb)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_Bobomb_03,      EVS_Release_Bobomb)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Release_KoopaTroopa)
    QS_WAIT(10 * DT)
    QS_NEXT(NPC_KoopaTroopa_02, EVS_Release_KoopaTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_KoopaTroopa_03, EVS_Release_KoopaTroopa)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_KoopaTroopa_04, EVS_Release_KoopaTroopa)
    QS_END
};

s32 QS_Release_Wave_6[] = {
    QS_NEXT(NPC_DarkTroopa_01,  EVS_Release_DarkTroopa)
    QS_WAIT(10 * DT)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Release_BlueShyGuy)
    QS_NEXT(NPC_Goomba_01,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Release_BlueShyGuy)
    QS_NEXT(NPC_Goomba_02,      EVS_Release_Goomba)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_Goomba_03,      EVS_Release_Goomba)
    QS_NEXT(NPC_DarkTroopa_02,  EVS_Release_DarkTroopa)
    QS_WAIT(8 * DT)
    QS_NEXT(NPC_DarkTroopa_03,  EVS_Release_DarkTroopa)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Release_RedShyGuy)
    QS_WAIT(5 * DT)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Release_RedShyGuy)
    QS_END
};

s32 QS_Withdraw_Wave_0[] = {
    QS_NEXT(NPC_DarkTroopa_01,  EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_DarkTroopa_02,  EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_DarkTroopa_03,  EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_Goomba_01,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_02,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_03,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_04,      EVS_Withdraw_Goomba)
    QS_END
};

s32 QS_Withdraw_Wave_1[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_RedShyGuy_03,   EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_04,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Withdraw_GreenShyGuy)
    QS_NEXT(NPC_GreenShyGuy_02, EVS_Withdraw_GreenShyGuy)
    QS_NEXT(NPC_GreenShyGuy_03, EVS_Withdraw_GreenShyGuy)
    QS_NEXT(NPC_GreenShyGuy_04, EVS_Withdraw_GreenShyGuy)
    QS_END
};

s32 QS_Withdraw_Wave_2[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Withdraw_RedShyGuy_Door_1)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Withdraw_RedShyGuy_Door_1)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Withdraw_BlueShyGuy_Door_2)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Withdraw_BlueShyGuy_Door_2)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Withdraw_BlueShyGuy_Door_2)
    QS_NEXT(NPC_BlueShyGuy_04,  EVS_Withdraw_BlueShyGuy_Door_2)
    QS_NEXT(NPC_Bobomb_01,      EVS_Withdraw_Bobomb_Door_0)
    QS_NEXT(NPC_Bobomb_02,      EVS_Withdraw_Bobomb_Door_0)
    QS_END
};

s32 QS_Withdraw_Wave_3[] = {
    QS_NEXT(NPC_Goomba_01,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_02,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_02, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_03, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_04, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Withdraw_GreenShyGuy)
    QS_NEXT(NPC_BlueShyGuy_01,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_02,  EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_03,  EVS_Withdraw_BlueShyGuy)
    QS_END
};

s32 QS_Withdraw_Wave_4[] = {
    QS_NEXT(NPC_Goomba_01,      EVS_Withdraw_Goomba)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_DarkTroopa_01,  EVS_Withdraw_DarkTroopa)
    QS_END
};

s32 QS_Withdraw_Wave_5[] = {
    QS_NEXT(NPC_RedShyGuy_01,   EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_RedShyGuy_02,   EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_GreenShyGuy_01, EVS_Withdraw_GreenShyGuy)
    QS_NEXT(NPC_Bobomb_01,      EVS_Withdraw_Bobomb)
    QS_NEXT(NPC_Bobomb_02,      EVS_Withdraw_Bobomb)
    QS_NEXT(NPC_Bobomb_03,      EVS_Withdraw_Bobomb)
    QS_NEXT(NPC_KoopaTroopa_01, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_02, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_03, EVS_Withdraw_KoopaTroopa)
    QS_NEXT(NPC_KoopaTroopa_04, EVS_Withdraw_KoopaTroopa)
    QS_END
};

s32 QS_Withdraw_Wave_6[] = {
    QS_NEXT(NPC_DarkTroopa_01, EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_DarkTroopa_02, EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_DarkTroopa_03, EVS_Withdraw_DarkTroopa)
    QS_NEXT(NPC_BlueShyGuy_01, EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_BlueShyGuy_02, EVS_Withdraw_BlueShyGuy)
    QS_NEXT(NPC_Goomba_01,     EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_02,     EVS_Withdraw_Goomba)
    QS_NEXT(NPC_Goomba_03,     EVS_Withdraw_Goomba)
    QS_NEXT(NPC_RedShyGuy_01,  EVS_Withdraw_RedShyGuy)
    QS_NEXT(NPC_RedShyGuy_02,  EVS_Withdraw_RedShyGuy)
    QS_END
};

EvtScript EVS_Release_Wave = {
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            UseBuf(QS_Release_Wave_0)
        CaseEq(1)
            UseBuf(QS_Release_Wave_1)
        CaseEq(2)
            UseBuf(QS_Release_Wave_2)
        CaseEq(3)
            UseBuf(QS_Release_Wave_3)
        CaseEq(4)
            UseBuf(QS_Release_Wave_4)
        CaseEq(5)
            UseBuf(QS_Release_Wave_5)
        CaseEq(6)
            UseBuf(QS_Release_Wave_6)
    EndSwitch
    Loop(0)
        BufRead2(LVarA, LVarB)
        IfEq(LVarA, -1)
            BreakLoop
        EndIf
        IfEq(LVarA, -2)
            Wait(LVarB)
        Else
            Call(BindNpcAI, LVarA, LVarB)
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_Withdraw_Wave = {
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            UseBuf(QS_Withdraw_Wave_0)
        CaseEq(1)
            UseBuf(QS_Withdraw_Wave_1)
        CaseEq(2)
            UseBuf(QS_Withdraw_Wave_2)
        CaseEq(3)
            UseBuf(QS_Withdraw_Wave_3)
        CaseEq(4)
            UseBuf(QS_Withdraw_Wave_4)
        CaseEq(5)
            UseBuf(QS_Withdraw_Wave_5)
        CaseEq(6)
            UseBuf(QS_Withdraw_Wave_6)
    EndSwitch
    Loop(0)
        BufRead2(LVarA, LVarB)
        IfEq(LVarA, -1)
            BreakLoop
        EndIf
        IfEq(LVarA, -2)
            Wait(LVarB)
        Else
            Call(BindNpcAI, LVarA, LVarB)
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_AskQuestion = {
    ExecWait(EVS_SetCam_AskQuestion)
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0035)
            Call(ShowChoice, MSG_Choice_0046)
            IfEq(LVar0, 0)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(1)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0036)
            Call(ShowChoice, MSG_Choice_0047)
            IfEq(LVar0, 0)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(2)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0037)
            Call(ShowChoice, MSG_Choice_0048)
            IfEq(LVar0, 1)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(3)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0038)
            Call(ShowChoice, MSG_Choice_0049)
            IfEq(LVar0, 0)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(4)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0039)
            Call(ShowChoice, MSG_Choice_004A)
            IfEq(LVar0, 0)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(5)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003A)
            Call(ShowChoice, MSG_Choice_004B)
            IfEq(LVar0, 2)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
        CaseEq(6)
            Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003B)
            Call(ShowChoice, MSG_Choice_004C)
            IfEq(LVar0, 1)
                Set(LVar0, ANSWER_CORRECT)
            Else
                Set(LVar0, ANSWER_WRONG)
            EndIf
    EndSwitch
    Set(MV_LastAnswerResult, LVar0)
    Call(CloseMessage)
    Return
    End
};

EvtScript EVS_ShowUnknownCard = {
    Call(EnableModel, MODEL_m_, true)
    Call(MakeLerp, 180, LVar0, 60 * DT, EASING_QUADRATIC_IN)
    Loop(0)
        Call(UpdateLerp)
        IfGe(LVar0, 360)
            Call(RotateGroup, MODEL_g47, LVar0, 0, 1, 0)
            Call(EnableGroup, MODEL_g47, true)
            Call(EnableModel, MODEL_m_, false)
        Else
            Call(RotateModel, MODEL_m_, LVar0, 0, 1, 0)
        EndIf
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_TetherResultCardToDummyPos = {
    Loop(0)
        Call(GetNpcPos, NPC_Dummy, LVar0, LVar1, LVar2)
        Sub(LVar0, 0)
        Sub(LVar1, 130)
        Sub(LVar2, 50)
        Call(TranslateModel, LVarA, LVar0, LVar1, LVar2)
        IfEq(LVarA, 85)
            Call(RotateModel, MODEL_b_kai, 180, 0, 1, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_ScaleResultCard = {
    Call(EnableModel, LVarA, true)
    Call(MakeLerp, 100, 50, 30 * DT, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        SetF(LVar6, LVar0)
        MulF(LVar6, 0.01)
        Call(ScaleModel, LVarA, LVar6, LVar6, 1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_MoveCardToScoreboard = {
    Call(EnableModel, LVarA, true)
    Call(SetNpcPos, NPC_Dummy, 0, 130, 50)
    ExecGetTID(EVS_TetherResultCardToDummyPos, LVarB)
    Exec(EVS_ScaleResultCard)
    Wait(1)
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            Set(LVar0, 118)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(1)
            Set(LVar0, 78)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(2)
            Set(LVar0, 38)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(3)
            Set(LVar0, -1)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(4)
            Set(LVar0, -41)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(5)
            Set(LVar0, -81)
            Set(LVar1, 148)
            Set(LVar2, 3)
        CaseEq(6)
            Set(LVar0, -121)
            Set(LVar1, 148)
            Set(LVar2, 3)
    EndSwitch
    Call(SetNpcJumpscale, NPC_Dummy, 0.0)
    Call(NpcJump1, NPC_Dummy, LVar0, LVar1, LVar2, 30 * DT)
    Call(SetNpcPos, NPC_Dummy, 184, 20, 150)
    KillThread(LVarB)
    Return
    End
};

EvtScript EVS_GetCorrectScoreboardModel = {
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            Set(LVar0, MODEL_m1)
        CaseEq(1)
            Set(LVar0, MODEL_m2)
        CaseEq(2)
            Set(LVar0, MODEL_m3)
        CaseEq(3)
            Set(LVar0, MODEL_m4)
        CaseEq(4)
            Set(LVar0, MODEL_m5)
        CaseEq(5)
            Set(LVar0, MODEL_m6)
        CaseEq(6)
            Set(LVar0, MODEL_m7)
    EndSwitch
    Return
    End
};

EvtScript EVS_GetWrongScoreboardModel = {
    Switch(AB_KPA82_QuizRound)
        CaseEq(0)
            Set(LVar0, MODEL_b1)
        CaseEq(1)
            Set(LVar0, MODEL_b2)
        CaseEq(2)
            Set(LVar0, MODEL_b3)
        CaseEq(3)
            Set(LVar0, MODEL_b4)
        CaseEq(4)
            Set(LVar0, MODEL_b5)
        CaseEq(5)
            Set(LVar0, MODEL_b6)
        CaseEq(6)
            Set(LVar0, MODEL_b7)
    EndSwitch
    Return
    End
};

EvtScript EVS_ShowResultCard = {
    Set(LVar6, 2.0 / DT)
    ExecWait(EVS_SetCam_ViewRoom)
    Wait(5)
    IfEq(MV_LastAnswerResult, ANSWER_CORRECT)
        Set(LVar0, 2160)
        ExecWait(EVS_ShowUnknownCard)
        Call(PlaySound, SOUND_APPROVE)
        Wait(10 * DT)
        Call(EnableGroup, MODEL_g47, false)
        Set(LVarA, MODEL_m_kai)
        ExecWait(EVS_MoveCardToScoreboard)
        ExecWait(EVS_GetCorrectScoreboardModel)
        Call(EnableModel, MODEL_m_kai, false)
        Call(EnableModel, LVar0, true)
        Wait(30 * DT)
    Else
        Set(LVar0, 2340)
        ExecWait(EVS_ShowUnknownCard)
        Call(PlaySound, SOUND_MENU_ERROR)
        Wait(10 * DT)
        Call(EnableGroup, MODEL_g47, false)
        Set(LVarA, MODEL_b_kai)
        ExecWait(EVS_MoveCardToScoreboard)
        ExecWait(EVS_GetWrongScoreboardModel)
        Call(EnableModel, MODEL_b_kai, false)
        Call(EnableModel, LVar0, true)
        Wait(30 * DT)
    EndIf
    ExecWait(EVS_SetCam_AfterResult)
    Return
    End
};

EvtScript EVS_NpcIdle_Door = {
    Label(1)
        Wait(1)
        IfEq(GF_KPA82_PassedThroughDoor, false)
            Goto(1)
        EndIf
    Set(GF_KPA82_PassedThroughDoor, false)
    Call(DisablePlayerInput, true)
    ExecWait(EVS_SetCam_MeetingDoor)
    Set(MF_Sync_MusicChange, false)
    Thread
        Call(SetMusic, 0, SONG_FINAL_BOWSER_BATTLE, BGM_VARIATION_1, VOL_LEVEL_FULL)
        Wait(150 * DT)
        IfNe(MF_Sync_MusicChange, false)
            Goto(5)
        EndIf
        Call(FadeOutMusic, 0, 250)
        Wait(15 * DT)
        IfNe(MF_Sync_MusicChange, false)
            Goto(5)
        EndIf
        Exec(EVS_SetupMusic)
        Label(5)
    EndThread
    IfEq(GF_KPA82_SpokeToDoor, false)
        Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_002E)
        Set(GF_KPA82_SpokeToDoor, true)
    Else
        Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_002F)
    EndIf
    Call(ShowChoice, MSG_Choice_0013)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0031)
    Else
        Call(ContinueSpeech, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0030)
        Call(ResetCam, CAM_DEFAULT, 4.0)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
        Set(GF_KPA82_PassedThroughDoor, false)
        Call(DisablePlayerInput, false)
        Goto(1)
    EndIf
    Call(ShowChoice, MSG_Choice_0013)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0032)
    Else
        Call(ContinueSpeech, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0033)
    EndIf
    Call(DisablePartnerAI, false)
    Thread
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o166, COLLIDER_FLAGS_UPPER_MASK)
        Call(DisablePlayerPhysics, true)
        Call(SetPlayerSpeed, 2.0)
        Call(PlayerMoveTo, 175, 236, 20)
        Call(InterpPlayerYaw, 270, 0)
        Call(DisablePlayerPhysics, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o166, COLLIDER_FLAGS_UPPER_MASK)
    EndThread
    Thread
        Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_WALK)
        Call(SetNpcSpeed, NPC_PARTNER, 2.5)
        Call(InterpNpcYaw, NPC_PARTNER, 270, 0)
        Call(NpcMoveTo, NPC_PARTNER, 205, 236, 20)
        Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
        Call(NpcFaceNpc, NPC_PARTNER, NPC_SELF, 0)
    EndThread
    Set(AB_KPA82_QuizRound, 0)
    Set(AB_KPA82_RightAnswers, 0)
    Set(AB_KPA82_WrongAnswers, 0)
    Label(10)
        Set(LVar6, 2.0 / DT)
        ExecWait(EVS_SetCam_ViewRoom)
        Set(MF_Sync_MusicChange, true)
        Wait(2)
        Call(SetMusic, 0, SONG_NORMAL_BATTLE, 0, VOL_LEVEL_FULL)
        ExecWait(EVS_SetDoorRots)
        ExecWait(EVS_Release_Wave)
        Wait(200 * DT)
        Thread
            Call(ShowMessageAtScreenPos, MSG_CH8_0034, 300, 200)
            Set(MV_Sync_TimesUp, true)
        EndThread
        Wait(60 * DT)
        ExecWait(EVS_Withdraw_Wave)
        Wait(35 * DT)
        ExecWait(EVS_CloseDoors)
        Exec(EVS_SetupMusic)
        Wait(30 * DT)
        Label(12)
            Wait(1)
            IfEq(MV_Sync_TimesUp, false)
                Goto(12)
            EndIf
        Set(MV_Sync_TimesUp, false)
        ExecWait(EVS_AskQuestion)
        ExecWait(EVS_ShowResultCard)
        IfEq(MV_LastAnswerResult, ANSWER_CORRECT)
            Add(AB_KPA82_RightAnswers, 1)
            IfEq(AB_KPA82_RightAnswers, 5)
                Goto(30)
            EndIf
            IfEq(AB_KPA82_RightAnswers, 4)
                Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003D)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003C)
            EndIf
        Else
            Add(AB_KPA82_WrongAnswers, 1)
            IfEq(AB_KPA82_WrongAnswers, 3)
                Goto(20)
            EndIf
            IfEq(AB_KPA82_WrongAnswers, 1)
                Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003E)
            EndIf
            IfEq(AB_KPA82_WrongAnswers, 2)
                Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0040)
            EndIf
        EndIf
        Add(AB_KPA82_QuizRound, 1)
        Goto(10)
    Label(20)
    Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0041)
    Set(LVar6, 2.0 / DT)
    ExecWait(EVS_SetCam_ViewRoom)
    Call(SetNpcPos, NPC_AntiGuy_01, -100, 0, 0)
    Call(SetNpcPos, NPC_AntiGuy_02, 0, 0, 0)
    Call(SetNpcPos, NPC_AntiGuy_03, 100, 0, 0)
    Call(InterpPlayerYaw, 315, 0)
    Call(InterpNpcYaw, NPC_PARTNER, 315, 0)
    ExecWait(EVS_SetDoorRots)
    Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0042)
    Call(PlayerFaceNpc, NPC_AntiGuy_02, 5)
    Call(GetPlayerPos, LVar3, LVar4, LVar5)
    Set(LVar6, 3.0 / DT)
    ExecWait(EVS_SetCam_BeforeBattle)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Call(SetNpcAnimation, NPC_AntiGuy_01, ANIM_ShyGuy_Black_Dash)
        Call(NpcMoveTo, NPC_AntiGuy_01, LVar0, LVar2, 30 * DT)
    EndThread
    Thread
        Call(SetNpcAnimation, NPC_AntiGuy_02, ANIM_ShyGuy_Black_Dash)
        Call(NpcMoveTo, NPC_AntiGuy_02, LVar0, LVar2, 30 * DT)
    EndThread
    Thread
        Call(SetNpcAnimation, NPC_AntiGuy_03, ANIM_ShyGuy_Black_Dash)
        Call(NpcMoveTo, NPC_AntiGuy_03, LVar0, LVar2, 30 * DT)
    EndThread
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    ExecWait(EVS_SetCam_AfterBattle)
    Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_0043)
    Goto(40)
    Label(30)
    Thread
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o166, COLLIDER_FLAGS_UPPER_MASK)
        Call(DisablePlayerPhysics, true)
        Call(SetPlayerSpeed, 3.0 / DT)
        Call(PlayerMoveTo, 120, 145, 0)
        Call(InterpPlayerYaw, 90, 0)
        Call(DisablePlayerPhysics, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o166, COLLIDER_FLAGS_UPPER_MASK)
    EndThread
    Thread
        Call(DisablePartnerAI, false)
        Call(SetNpcSpeed, NPC_PARTNER, 3.5 * DT)
        Call(InterpNpcYaw, NPC_PARTNER, 90, 0)
        Call(NpcMoveTo, NPC_PARTNER, 80, 145, 0)
        Call(EnablePartnerAI)
    EndThread
    Call(SpeakToPlayer, NPC_SELF, ANIM_ShyGuy_Black_Idle, ANIM_ShyGuy_Black_Idle, 0, MSG_CH8_003F)
    Label(40)
    Call(EnablePartnerAI)
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    Set(GB_KPA82_BowserDoorState, 1)
    Call(DisablePlayerInput, false)
    BindTrigger(EVS_ExitDoors_kpa_61_0, TRIGGER_WALL_PRESS_A, COLLIDER_o166, 1, 0)
    Return
    End
};

EvtScript EVS_NpcDefeat_Door = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetNpcPos, NPC_AntiGuy_01, NPC_DISPOSE_LOCATION)
            Call(SetNpcPos, NPC_AntiGuy_02, NPC_DISPOSE_LOCATION)
            Call(SetNpcPos, NPC_AntiGuy_03, NPC_DISPOSE_LOCATION)
            Call(SetPlayerPos, 120, 0, 145)
            Call(SetNpcPos, NPC_PARTNER, 80, 0, 145)
            Call(InterpPlayerYaw, 90, 0)
            Call(InterpNpcYaw, NPC_PARTNER, 90, 0)
            Call(TranslateModel, MODEL_o100, 0, 0, 0)
            Call(TranslateModel, MODEL_o101, 0, 0, 0)
            Call(TranslateModel, MODEL_o145, 0, 0, 0)
            Call(TranslateModel, MODEL_o146, 0, 0, 0)
            Call(TranslateModel, MODEL_o102, 0, 0, 0)
            Call(TranslateModel, MODEL_o103, 0, 0, 0)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Door = {
    IfEq(GB_KPA82_BowserDoorState, 0)
        Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Door)
    EndIf
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_Door)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_USE_INSPECT_ICON, true)
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetNpcPos, NPC_SELF, 184, 20, 150)
    Return
    End
};

EvtScript EVS_NpcInit_Goomba = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Goomba)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, false)
    Return
    End
};

EvtScript EVS_NpcInit_ShyGuy = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_ShyGuy)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, false)
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_KoopaTroopa)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, false)
    Return
    End
};

EvtScript EVS_NpcInit_Bobomb = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Bobomb)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, false)
    Return
    End
};

EvtScript EVS_NpcInit_AntiGuy = {
    Return
    End
};

#define QUIZ_DOOR_ENEMY_FLAGS \
    ( ENEMY_FLAG_DO_NOT_KILL \
    | ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_HAS_NO_SPRITE \
    | ENEMY_FLAG_NO_DELAY_AFTER_FLEE \
    | ENEMY_FLAG_SKIP_BATTLE \
    | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN \
    | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER \
    | ENEMY_FLAG_NO_DROPS \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    )

#define QUIZ_ANTI_GUY_ENEMY_FLAGS \
    ( ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_NO_DELAY_AFTER_FLEE \
    | ENEMY_FLAG_SKIP_BATTLE \
    | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER \
    | ENEMY_FLAG_NO_DROPS \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    )

NpcData NpcData_AntiGuys[] = {
    {
        .id = NPC_Dummy,
        .pos = $Dummy.pos,
        .yaw = $Dummy.yaw,
        .init = &EVS_NpcInit_Door,
        .settings = &NpcSettings_ShyGuy,
        .flags = QUIZ_DOOR_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = ANTI_GUY_ANIMS,
    },
    {
        .id = NPC_AntiGuy_01,
        .pos = $AntiGuy_01.pos,
        .yaw = $AntiGuy_01.yaw,
        .init = &EVS_NpcInit_AntiGuy,
        .settings = &NpcSettings_ShyGuy,
        .flags = QUIZ_ANTI_GUY_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = ANTI_GUY_ANIMS,
    },
    {
        .id = NPC_AntiGuy_02,
        .pos = $AntiGuy_02.pos,
        .yaw = $AntiGuy_02.yaw,
        .init = &EVS_NpcInit_AntiGuy,
        .settings = &NpcSettings_ShyGuy,
        .flags = QUIZ_ANTI_GUY_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = ANTI_GUY_ANIMS,
    },
    {
        .id = NPC_AntiGuy_03,
        .pos = $AntiGuy_03.pos,
        .yaw = $AntiGuy_03.yaw,
        .init = &EVS_NpcInit_AntiGuy,
        .settings = &NpcSettings_ShyGuy,
        .flags = QUIZ_ANTI_GUY_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = ANTI_GUY_ANIMS,
    },
};

#define QUIZ_GAME_ENEMY_FLAGS \
    ( ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_NO_DELAY_AFTER_FLEE \
    | ENEMY_FLAG_SKIP_BATTLE \
    | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN \
    | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER \
    | ENEMY_FLAG_NO_DROPS \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    )

NpcData NpcData_Goombas[] = {
    {
        .id = NPC_Goomba_01,
        .pos = $Goomba_01.pos,
        .yaw = $Goomba_01.yaw,
        .territory = $Goomba_01.territory,
        .init = &EVS_NpcInit_Goomba,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = GOOMBA_DROPS,
        .animations = GOOMBA_ANIMS,
    },
    {
        .id = NPC_Goomba_02,
        .pos = $Goomba_02.pos,
        .yaw = $Goomba_02.yaw,
        .territory = $Goomba_02.territory,
        .init = &EVS_NpcInit_Goomba,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = GOOMBA_DROPS,
        .animations = GOOMBA_ANIMS,
    },
    {
        .id = NPC_Goomba_03,
        .pos = $Goomba_03.pos,
        .yaw = $Goomba_03.yaw,
        .territory = $Goomba_03.territory,
        .init = &EVS_NpcInit_Goomba,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = GOOMBA_DROPS,
        .animations = GOOMBA_ANIMS,
    },
    {
        .id = NPC_Goomba_04,
        .pos = $Goomba_04.pos,
        .yaw = $Goomba_04.yaw,
        .territory = $Goomba_04.territory,
        .init = &EVS_NpcInit_Goomba,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = GOOMBA_DROPS,
        .animations = GOOMBA_ANIMS,
    },
    {
        .id = NPC_Goomba_05,
        .pos = $Goomba_05.pos,
        .yaw = $Goomba_05.yaw,
        .territory = $Goomba_05.territory,
        .init = &EVS_NpcInit_Goomba,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = GOOMBA_DROPS,
        .animations = GOOMBA_ANIMS,
    },
};

NpcData NpcData_RedShyGuys[] = {
    {
        .id = NPC_RedShyGuy_01,
        .pos = $RedShyGuy_01.pos,
        .yaw = $RedShyGuy_01.yaw,
        .territory = $RedShyGuy_01.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_RedShyGuy_02,
        .pos = $RedShyGuy_02.pos,
        .yaw = $RedShyGuy_02.yaw,
        .territory = $RedShyGuy_02.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_RedShyGuy_03,
        .pos = $RedShyGuy_03.pos,
        .yaw = $RedShyGuy_03.yaw,
        .territory = $RedShyGuy_03.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_RedShyGuy_04,
        .pos = $RedShyGuy_04.pos,
        .yaw = $RedShyGuy_04.yaw,
        .territory = $RedShyGuy_04.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_RedShyGuy_05,
        .pos = $RedShyGuy_05.pos,
        .yaw = $RedShyGuy_05.yaw,
        .territory = $RedShyGuy_05.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
};

NpcData NpcData_BlueShyGuys[] = {
    {
        .id = NPC_BlueShyGuy_01,
        .pos = $BlueShyGuy_01.pos,
        .yaw = $BlueShyGuy_01.yaw,
        .territory = $BlueShyGuy_01.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = BLUE_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_BlueShyGuy_02,
        .pos = $BlueShyGuy_02.pos,
        .yaw = $BlueShyGuy_02.yaw,
        .territory = $BlueShyGuy_02.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = BLUE_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_BlueShyGuy_03,
        .pos = $BlueShyGuy_03.pos,
        .yaw = $BlueShyGuy_03.yaw,
        .territory = $BlueShyGuy_03.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = BLUE_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_BlueShyGuy_04,
        .pos = $BlueShyGuy_04.pos,
        .yaw = $BlueShyGuy_04.yaw,
        .territory = $BlueShyGuy_04.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = BLUE_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_BlueShyGuy_05,
        .pos = $BlueShyGuy_05.pos,
        .yaw = $BlueShyGuy_05.yaw,
        .territory = $BlueShyGuy_05.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = BLUE_SHY_GUY_ANIMS,
    },
};

NpcData NpcData_GreenShyGuys[] = {
    {
        .id = NPC_GreenShyGuy_01,
        .pos = $GreenShyGuy_01.pos,
        .yaw = $GreenShyGuy_01.yaw,
        .territory = $GreenShyGuy_01.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = GREEN_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_GreenShyGuy_02,
        .pos = $GreenShyGuy_02.pos,
        .yaw = $GreenShyGuy_02.yaw,
        .territory = $GreenShyGuy_02.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = GREEN_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_GreenShyGuy_03,
        .pos = $GreenShyGuy_03.pos,
        .yaw = $GreenShyGuy_03.yaw,
        .territory = $GreenShyGuy_03.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = GREEN_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_GreenShyGuy_04,
        .pos = $GreenShyGuy_04.pos,
        .yaw = $GreenShyGuy_04.yaw,
        .territory = $GreenShyGuy_04.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = GREEN_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_GreenShyGuy_05,
        .pos = $GreenShyGuy_05.pos,
        .yaw = $GreenShyGuy_05.yaw,
        .territory = $GreenShyGuy_05.territory,
        .init = &EVS_NpcInit_ShyGuy,
        .settings = &NpcSettings_ShyGuy_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = SHY_GUY_DROPS,
        .animations = GREEN_SHY_GUY_ANIMS,
    },
};

NpcData NpcData_DarkTroopas[] = {
    {
        .id = NPC_DarkTroopa_01,
        .pos = $DarkTroopa_01.pos,
        .yaw = $DarkTroopa_01.yaw,
        .territory = $DarkTroopa_01.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = DARK_TROOPA_ANIMS,
    },
    {
        .id = NPC_DarkTroopa_02,
        .pos = $DarkTroopa_02.pos,
        .yaw = $DarkTroopa_02.yaw,
        .territory = $DarkTroopa_02.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = DARK_TROOPA_ANIMS,
    },
    {
        .id = NPC_DarkTroopa_03,
        .pos = $DarkTroopa_03.pos,
        .yaw = $DarkTroopa_03.yaw,
        .territory = $DarkTroopa_03.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = DARK_TROOPA_ANIMS,
    },
    {
        .id = NPC_DarkTroopa_04,
        .pos = $DarkTroopa_04.pos,
        .yaw = $DarkTroopa_04.yaw,
        .territory = $DarkTroopa_04.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = DARK_TROOPA_ANIMS,
    },
    {
        .id = NPC_DarkTroopa_05,
        .pos = $DarkTroopa_05.pos,
        .yaw = $DarkTroopa_05.yaw,
        .territory = $DarkTroopa_05.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = DARK_TROOPA_ANIMS,
    },
};

NpcData NpcData_KoopaTroopas[] = {
    {
        .id = NPC_KoopaTroopa_01,
        .pos = $KoopaTroopa_01.pos,
        .yaw = $KoopaTroopa_01.yaw,
        .territory = $KoopaTroopa_01.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = KOOPA_TROOPA_ANIMS,
    },
    {
        .id = NPC_KoopaTroopa_02,
        .pos = $KoopaTroopa_02.pos,
        .yaw = $KoopaTroopa_02.yaw,
        .territory = $KoopaTroopa_02.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = KOOPA_TROOPA_ANIMS,
    },
    {
        .id = NPC_KoopaTroopa_03,
        .pos = $KoopaTroopa_03.pos,
        .yaw = $KoopaTroopa_03.yaw,
        .territory = $KoopaTroopa_03.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = KOOPA_TROOPA_ANIMS,
    },
    {
        .id = NPC_KoopaTroopa_04,
        .pos = $KoopaTroopa_04.pos,
        .yaw = $KoopaTroopa_04.yaw,
        .territory = $KoopaTroopa_04.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = KOOPA_TROOPA_ANIMS,
    },
    {
        .id = NPC_KoopaTroopa_05,
        .pos = $KoopaTroopa_05.pos,
        .yaw = $KoopaTroopa_05.yaw,
        .territory = $KoopaTroopa_05.territory,
        .init = &EVS_NpcInit_KoopaTroopa,
        .settings = &NpcSettings_KoopaTroopa_Wander,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = KOOPA_TROOPA_NOK_DROPS,
        .animations = KOOPA_TROOPA_ANIMS,
    },
};

NpcData NpcData_Bobombs[] = {
    {
        .id = NPC_Bobomb_01,
        .pos = $Bobomb_01.pos,
        .yaw = $Bobomb_01.yaw,
        .territory = $Bobomb_01.territory,
        .init = &EVS_NpcInit_Bobomb,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = BOBOMB_GREEN_ANIMS,
    },
    {
        .id = NPC_Bobomb_02,
        .pos = $Bobomb_02.pos,
        .yaw = $Bobomb_02.yaw,
        .territory = $Bobomb_02.territory,
        .init = &EVS_NpcInit_Bobomb,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = BOBOMB_GREEN_ANIMS,
    },
    {
        .id = NPC_Bobomb_03,
        .pos = $Bobomb_03.pos,
        .yaw = $Bobomb_03.yaw,
        .territory = $Bobomb_03.territory,
        .init = &EVS_NpcInit_Bobomb,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = BOBOMB_GREEN_ANIMS,
    },
    {
        .id = NPC_Bobomb_04,
        .pos = $Bobomb_04.pos,
        .yaw = $Bobomb_04.yaw,
        .territory = $Bobomb_04.territory,
        .init = &EVS_NpcInit_Bobomb,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = BOBOMB_GREEN_ANIMS,
    },
    {
        .id = NPC_Bobomb_05,
        .pos = $Bobomb_05.pos,
        .yaw = $Bobomb_05.yaw,
        .territory = $Bobomb_05.territory,
        .init = &EVS_NpcInit_Bobomb,
        .settings = &NpcSettings_Short,
        .flags = QUIZ_GAME_ENEMY_FLAGS,
        .drops = NO_DROPS,
        .animations = BOBOMB_GREEN_ANIMS,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_AntiGuys, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_Goombas, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_RedShyGuys, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_BlueShyGuys, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_GreenShyGuys, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_DarkTroopas, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_KoopaTroopas, "kpa3:anti_guy_3", "kpa_01"),
    NPC_GROUP(NpcData_Bobombs, "kpa3:anti_guy_3", "kpa_01"),
    {}
};
