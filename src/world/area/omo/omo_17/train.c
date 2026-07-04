#include "omo_17.h"

#include "../common/ToyTrain.inc.c"

EvtScript N(EVS_UpdateCameraDuringTrainTransition) = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLt(LVar0, -600)
            Set(LVar0, -600)
        EndIf
        IfGt(LVar0, 600)
            Set(LVar0, 600)
        EndIf
        Call(SetCamTarget, CAM_DEFAULT, LVar0, Float(50.0), LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

TrainPath N(TrainPath_LeftToRight)[] = {
    TRAIN_PATH_BEGIN(-720.0, 0.0, 90.0),
    TRAIN_PATH_POINT(720.0, 0.0),
    TRAIN_PATH_END,
};

TrainPath N(TrainPath_RightToLeft)[] = {
    TRAIN_PATH_BEGIN(720.0, 0.0, 270.0),
    TRAIN_PATH_POINT(-720.0, 0.0),
    TRAIN_PATH_END,
};

EvtScript N(EVS_EnterTrain) = {
    Call(ParentColliderToModel, COLLIDER_p1, MODEL_o1)
    Call(ParentColliderToModel, COLLIDER_pp1, MODEL_o1)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(DisablePartnerAI, false)
    Exec(N(EVS_UpdateCameraDuringTrainTransition))
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(omo_17_ENTRY_4)
            Set(MV_TrainRideState, TRAIN_STATE_INIT)
            Set(MV_TrainPath, Ref(N(TrainPath_LeftToRight)))
            Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
            Exec(N(EVS_UpdateTrain))
            Set(MF_TrainRideActive, true)
            Thread
                Label(10)
                IfLt(MV_TrainPosX, 600)
                    Wait(1)
                    Goto(10)
                EndIf
                Call(GotoMap, Ref("omo_06"), omo_06_ENTRY_0)
                Wait(100)
            EndThread
        CaseEq(omo_17_ENTRY_5)
            Set(MV_TrainRideState, TRAIN_STATE_INIT)
            Set(MV_TrainPath, Ref(N(TrainPath_RightToLeft)))
            Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
            Exec(N(EVS_UpdateTrain))
            Set(MF_TrainRideActive, true)
            Thread
                Label(20)
                IfGt(MV_TrainPosX, -600)
                    Wait(1)
                    Goto(20)
                EndIf
                Call(GotoMap, Ref("omo_05"), omo_05_ENTRY_1)
                Wait(100)
            EndThread
    EndSwitch
    Return
    End
};
