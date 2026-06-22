#include "common.h"
#include "sprite/npc/Toad.h"

// to use this include, you must also define these
extern EvtScript N(EVS_ToadHouse_SetDialogue);
extern EvtScript N(EVS_ToadHouse_ReturnFromRest);
extern EvtScript N(EVS_ToadHouse_GetInBed);

// presumably, these are never really used
EvtScript N(EVS_ToadHouse_ResetBedCovers) = {
    Call(EnableModel, LVar4, false)
    Call(EnableModel, LVar5, true)
    Call(RotateModel, LVar6, 0, 0, 0, 1)
    Call(RotateModel, LVar7, 0, 0, 0, 1)
    Return
    End
};

// presumably, these are never really used
EvtScript N(EVS_ToadHouse_OpenBedCovers) = {
    Set(LVar9, LVar7)
    Set(LVar8, LVar6)
    Set(LVar7, LVar5)
    Set(LVar6, LVar4)
    Wait(70)
    Call(EnableModel, LVar6, false)
    Thread
        Wait(5)
        Call(EnableModel, LVar6, true)
    EndThread
    Call(MakeLerp, 0, 180, 20, EASING_CUBIC_IN)
    Label(1)
        Call(UpdateLerp)
        Call(RotateModel, LVar8, LVar0, 0, 0, -1)
        Call(RotateModel, LVar9, LVar0, 0, 0, -1)
        IfEq(LVar1, 1)
            Wait(1)
            Goto(1)
        EndIf
    Call(EnableModel, LVar7, false)
    Return
    End
};

// automatically use Shiver City toad if animations are present
#ifdef ANIM_ShiverToad_Red_Idle
#define TOAD_HOUSE_ANIM_IDLE ANIM_ShiverToad_Red_Idle
#define TOAD_HOUSE_ANIM_TALK ANIM_ShiverToad_Red_Talk
#else
#define TOAD_HOUSE_ANIM_IDLE ANIM_Toad_Red_Idle
#define TOAD_HOUSE_ANIM_TALK ANIM_Toad_Red_Talk
#endif

EvtScript N(EVS_NpcInteract_ToadHouseKeeper) = {
    Call(N(ToadHouse_InitScreenOverlay), 0, 0, 0)
    ExecWait(N(EVS_ToadHouse_SetDialogue))
    IfEq(LVar0, 0)
        Return
    EndIf
    Set(LVar9, LVar1)
    Set(LVarA, LVar2)
    Set(LVarB, LVar3)
    Call(N(ToadHouse_DoesPlayerNeedSleep))
    IfEq(LVar1, 0)
        Set(LVar8, LVar0)
    EndIf
    Call(SpeakToPlayer, NPC_SELF, TOAD_HOUSE_ANIM_TALK, TOAD_HOUSE_ANIM_IDLE, 0, LVar8)
    Call(ShowChoice, MSG_Choice_0006)
    Wait(3)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, NPC_SELF, TOAD_HOUSE_ANIM_TALK, TOAD_HOUSE_ANIM_IDLE, 0, LVar9)
        Return
    EndIf
    Call(ContinueSpeech, NPC_SELF, TOAD_HOUSE_ANIM_TALK, TOAD_HOUSE_ANIM_IDLE, 0, LVarA)
    Call(SetPlayerJumpscale, 1)
    Call(DisablePlayerPhysics, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(N(ToadHouse_SuspendStatusBar))
    IfNe(LVar4, 0)
        Exec(N(EVS_ToadHouse_OpenBedCovers))
    EndIf
    Call(N(ToadHouse_PutPartnerAway), LVarA)
    Wait(20)
    ExecWait(N(EVS_ToadHouse_GetInBed))
    Thread
        Call(MakeLerp, 0, 255, 60, EASING_LINEAR)
        Label(0)
        Call(UpdateLerp)
        Call(N(ToadHouse_UpdateScreenOverlay), 3, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
        Call(FullyRestoreHPandFP)
        Call(FullyRestoreSP)
        IfNe(LVar4, 0)
            Exec(N(EVS_ToadHouse_ResetBedCovers))
        EndIf
        Call(N(ToadHouse_GetPartnerOut), LVarA)
        Wait(45)
        Call(MakeLerp, 255, 0, 30, EASING_LINEAR)
        Label(1)
        Call(UpdateLerp)
        Call(N(ToadHouse_UpdateScreenOverlay), 0, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Wait(105)
    ExecWait(N(EVS_ToadHouse_ReturnFromRest))
    Call(DisablePlayerPhysics, false)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, false)
    Call(SpeakToPlayer, NPC_SELF, TOAD_HOUSE_ANIM_TALK, TOAD_HOUSE_ANIM_IDLE, 0, LVarB)
    Call(N(ToadHouse_ResumeStatusBar))
    Return
    End
};
