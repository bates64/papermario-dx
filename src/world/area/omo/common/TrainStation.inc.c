#include "common.h"

extern Vec2i N(ConductorPos);
extern TrainPath N(TrainPath_DepartRight)[];
extern TrainPath N(TrainPath_DepartLeft)[];
extern TrainPath N(TrainPath_ArriveRight)[];
extern TrainPath N(TrainPath_PassthroughRight)[];
extern TrainPath N(TrainPath_ArriveLeft)[];
extern TrainPath N(TrainPath_PassthroughLeft)[];
extern TrainPath N(TrainPath_Idle)[];

#ifndef TRAIN_STATION_ID
#error TRAIN_STATION_ID is not defined!
#endif
#ifndef TRAIN_ROUTE_LEFT
#error TRAIN_ROUTE_LEFT is not defined!
#endif
#ifndef TRAIN_ROUTE_RIGHT
#error TRAIN_ROUTE_RIGHT is not defined!
#endif
#ifndef TRAIN_COLLIDER
#error TRAIN_COLLIDER is not defined!
#endif
#ifndef TRAIN_ARRIVAL_MESSAGE
#error TRAIN_ARRIVAL_MESSAGE is not defined!
#endif
#ifndef TRAIN_LEFT_THRESHOLD
#error TRAIN_LEFT_THRESHOLD is not defined!
#endif
#ifndef TRAIN_RIGHT_THRESHOLD
#error TRAIN_RIGHT_THRESHOLD is not defined!
#endif
#ifndef TRAIN_LEFT_ENTRY
#error TRAIN_LEFT_ENTRY is not defined!
#endif
#ifndef TRAIN_RIGHT_ENTRY
#error TRAIN_RIGHT_ENTRY is not defined!
#endif


EvtScript N(EVS_Train_DepartRight) = {
    Call(FadeOutMusic, 0, 3000)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, false)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Wait(10)
    Call(DisablePlayerPhysics, true)
    Exec(N(EVS_LowerCameraBeforeTrainRide))
    Set(AB_OMO_TrainOrigin, TRAIN_STATION_ID)
    Set(LVar0, Ref(N(TrainPath_DepartRight)))
    ExecWait(N(EVS_BoardTrain))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
    Set(MV_TrainRideState, TRAIN_STATE_INIT)
    Set(MV_TrainPath, Ref(N(TrainPath_DepartRight)))
    Set(MV_TrainSpeedMode, TRAIN_SPEED_ACCELERATE)
    Set(MF_TrainRideActive, true)
    Label(10)
        IfLt(MV_TrainPosX, TRAIN_RIGHT_THRESHOLD)
            Wait(1)
            Goto(10)
        EndIf
    Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_0)
    Set(GB_OMO_TrainRoute, TRAIN_ROUTE_RIGHT)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_Train_DepartLeft) = {
    Call(FadeOutMusic, 0, 3000)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, false)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Wait(10)
    Call(DisablePlayerPhysics, true)
    Exec(N(EVS_LowerCameraBeforeTrainRide))
    Set(AB_OMO_TrainOrigin, TRAIN_STATION_ID)
    Set(LVar0, Ref(N(TrainPath_DepartLeft)))
    ExecWait(N(EVS_BoardTrain))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
    Set(MV_TrainRideState, TRAIN_STATE_INIT)
    Set(MV_TrainPath, Ref(N(TrainPath_DepartLeft)))
    Set(MV_TrainSpeedMode, TRAIN_SPEED_ACCELERATE)
    Set(MF_TrainRideActive, true)
    Label(10)
        IfGt(MV_TrainPosX, TRAIN_LEFT_THRESHOLD)
            Wait(1)
            Goto(10)
        EndIf
    Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_1)
    Set(GB_OMO_TrainRoute, TRAIN_ROUTE_LEFT)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_Train_ArriveFromRight) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePartnerAI, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(AB_OMO_TrainDest, TRAIN_STATION_ID)
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_ArriveRight)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_DECELERATE)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        ExecGetTID(N(EVS_UpdateCameraDuringTrainRide), LVarB)
        Label(10)
            IfEq(MF_TrainRideActive, true)
                Wait(1)
                Goto(10)
            EndIf
        Wait(20)
        KillThread(LVarB)
        Exec(N(EVS_RestoreCameraAfterTrainRide))
        Call(EnableCameraFollowPlayerY)
        Set(LVar9, Ref(N(ConductorPos)))
        ExecWait(N(EVS_DisembarkTrain))
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, TRAIN_ARRIVAL_MESSAGE)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
        Call(DisablePlayerPhysics, false)
        Call(EnablePartnerAI)
        Call(DisablePlayerInput, false)
    Else
        Exec(N(EVS_UpdateCameraDuringTrainRide))
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_PassthroughRight)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        Exec(N(EVS_AwaitTrainRideSkip))
        Label(20)
            IfGt(MV_TrainPosX, TRAIN_LEFT_THRESHOLD)
                Wait(1)
                Goto(20)
            EndIf
        Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_1)
        Set(GB_OMO_TrainRoute, TRAIN_ROUTE_LEFT)
        Wait(100)
    EndIf
    Return
    End
};

EvtScript N(EVS_Train_ArriveFromLeft) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePartnerAI, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(AB_OMO_TrainDest, TRAIN_STATION_ID)
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_ArriveLeft)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_DECELERATE)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        ExecGetTID(N(EVS_UpdateCameraDuringTrainRide), LVarB)
        Label(10)
            IfEq(MF_TrainRideActive, true)
                Wait(1)
                Goto(10)
            EndIf
        Wait(20)
        KillThread(LVarB)
        Exec(N(EVS_RestoreCameraAfterTrainRide))
        Call(EnableCameraFollowPlayerY)
        Set(LVar9, Ref(N(ConductorPos)))
        ExecWait(N(EVS_DisembarkTrain))
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, TRAIN_ARRIVAL_MESSAGE)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, TRAIN_COLLIDER, COLLIDER_FLAGS_UPPER_MASK)
        Call(DisablePlayerPhysics, false)
        Call(EnablePartnerAI)
        Call(DisablePlayerInput, false)
    Else
        Exec(N(EVS_UpdateCameraDuringTrainRide))
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_PassthroughLeft)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        Exec(N(EVS_AwaitTrainRideSkip))
        Label(20)
            IfLt(MV_TrainPosX, TRAIN_RIGHT_THRESHOLD)
                Wait(1)
                Goto(20)
            EndIf
        Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_0)
        Set(GB_OMO_TrainRoute, TRAIN_ROUTE_RIGHT)
        Wait(100)
    EndIf
    Return
    End
};

EvtScript N(EVS_SetupTrain) = {
    ExecWait(N(EVS_SetupSwitches))
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_Idle)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
    Else
        Call(GetEntryID, LVar0)
        Switch(LVar0)
            CaseEq(TRAIN_LEFT_ENTRY)
                Exec(N(EVS_Train_ArriveFromLeft))
            CaseEq(TRAIN_RIGHT_ENTRY)
                Exec(N(EVS_Train_ArriveFromRight))
            CaseDefault
                Set(MV_TrainRideState, TRAIN_STATE_INIT)
                Set(MV_TrainPath, Ref(N(TrainPath_Idle)))
                Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
                Exec(N(EVS_UpdateTrain))
                Set(MF_TrainRideActive, true)
        EndSwitch
    EndIf
    Return
    End
};

#undef TRAIN_STATION_ID
#undef TRAIN_ROUTE_LEFT
#undef TRAIN_ROUTE_RIGHT
#undef TRAIN_COLLIDER
#undef TRAIN_ARRIVAL_MESSAGE
#undef TRAIN_LEFT_THRESHOLD
#undef TRAIN_RIGHT_THRESHOLD
#undef TRAIN_LEFT_ENTRY
#undef TRAIN_RIGHT_ENTRY
