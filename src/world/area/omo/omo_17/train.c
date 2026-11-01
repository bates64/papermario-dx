#include "omo_17.h"
#include "world/area/omo/omo_05.h"
#include "world/area/omo/omo_06.h"

#include "../common/ToyTrain.inc.c"

EvtScript EVS_UpdateCameraDuringTrainTransition = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLt(LVar0, -600)
            Set(LVar0, -600)
        EndIf
        IfGt(LVar0, 600)
            Set(LVar0, 600)
        EndIf
        Call(SetCamTarget, CAM_DEFAULT, LVar0, 50.0, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

TrainPath TrainPath_LeftToRight[] = {
    TRAIN_PATH_BEGIN(-720.0, 0.0, 90.0),
    TRAIN_PATH_POINT(720.0, 0.0),
    TRAIN_PATH_END,
};

TrainPath TrainPath_RightToLeft[] = {
    TRAIN_PATH_BEGIN(720.0, 0.0, 270.0),
    TRAIN_PATH_POINT(-720.0, 0.0),
    TRAIN_PATH_END,
};

EvtScript EVS_EnterTrain = {
    Call(ParentColliderToModel, COLLIDER_p1, MODEL_o1)
    Call(ParentColliderToModel, COLLIDER_pp1, MODEL_o1)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(DisablePartnerAI, false)
    Exec(EVS_UpdateCameraDuringTrainTransition)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($TrainLeft.index)
            Set(MV_TrainRideState, TRAIN_STATE_INIT)
            Set(MV_TrainPath, TrainPath_LeftToRight)
            Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
            Exec(EVS_UpdateTrain)
            Set(MF_TrainRideActive, true)
            Thread
                Label(10)
                IfLt(MV_TrainPosX, 600)
                    Wait(1)
                    Goto(10)
                EndIf
                Call(GotoMap, $omo_06.Omo17South)
                Wait(100)
            EndThread
        CaseEq($TrainRight.index)
            Set(MV_TrainRideState, TRAIN_STATE_INIT)
            Set(MV_TrainPath, TrainPath_RightToLeft)
            Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
            Exec(EVS_UpdateTrain)
            Set(MF_TrainRideActive, true)
            Thread
                Label(20)
                IfGt(MV_TrainPosX, -600)
                    Wait(1)
                    Goto(20)
                EndIf
                Call(GotoMap, $omo_05.Omo17North)
                Wait(100)
            EndThread
    EndSwitch
    Return
    End
};
