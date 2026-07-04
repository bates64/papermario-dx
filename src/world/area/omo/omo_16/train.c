#include "omo_16.h"

#include "../common/ToyTrain.inc.c"

EvtScript N(EVS_Conductor_AnnounceArrival) = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, omo_16_ENTRY_0)
        Wait(140)
        Switch(GB_OMO_TrainRoute)
            CaseEq(TRAIN_ROUTE_BLUE_PINK)
                IfEq(AB_OMO_TrainDest, OMO_STATION_PINK)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000B)
                EndIf
            CaseEq(TRAIN_ROUTE_PINK_GREEN)
                IfEq(AB_OMO_TrainDest, OMO_STATION_GREEN)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000C)
                EndIf
            CaseEq(TRAIN_ROUTE_GREEN_RED)
                IfEq(AB_OMO_TrainDest, OMO_STATION_RED)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000D)
                EndIf
            CaseEq(TRAIN_ROUTE_RED_BLUE)
                IfEq(AB_OMO_TrainDest, OMO_STATION_BLUE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000A)
                EndIf
        EndSwitch
    Else
        Wait(140)
        Switch(GB_OMO_TrainRoute)
            CaseEq(TRAIN_ROUTE_BLUE_PINK)
                IfEq(AB_OMO_TrainDest, OMO_STATION_BLUE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000A)
                EndIf
            CaseEq(TRAIN_ROUTE_PINK_GREEN)
                IfEq(AB_OMO_TrainDest, OMO_STATION_PINK)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000B)
                EndIf
            CaseEq(TRAIN_ROUTE_GREEN_RED)
                IfEq(AB_OMO_TrainDest, OMO_STATION_GREEN)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000C)
                EndIf
            CaseEq(TRAIN_ROUTE_RED_BLUE)
                IfEq(AB_OMO_TrainDest, OMO_STATION_RED)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_000D)
                EndIf
        EndSwitch
    EndIf
    Return
    End
};

EvtScript N(EVS_UpdateCameraDuringLongTrainRide) = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLt(LVar0, -2000)
            Set(LVar0, -2000)
        EndIf
        IfGt(LVar0, 2000)
            Set(LVar0, 2000)
        EndIf
        Call(SetCamTarget, CAM_DEFAULT, LVar0, Float(50.0), LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

TrainPath N(TrainPath_LeftToRight)[] = {
    TRAIN_PATH_BEGIN(-1550.0, 0.0, 90.0),
    TRAIN_PATH_POINT(1550.0, 0.0),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_RightToLeft)[] = {
    TRAIN_PATH_BEGIN(1550.0, 0.0, 270.0),
    TRAIN_PATH_POINT(-1550.0, 0.0),
    TRAIN_PATH_END
};

API_CALLABLE(N(CheckForSceneSkip)) {
    f32 trainPos = evt_get_float_variable(script, MV_TrainPosX);

    script->varTable[0] = 0;
    if (fabsf(trainPos) < 2000.0f && (gGameStatusPtr->pressedButtons[0] & BUTTON_A)) {
        script->varTable[0] = 1;
    }

    if (fabsf(trainPos) < 2000.0f && (gGameStatusPtr->pressedButtons[0] & BUTTON_B)) {
        script->varTable[0] = 1;
    }
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Scene_TrainTraveling) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(DisablePartnerAI, false)
    Exec(N(EVS_UpdateCameraDuringLongTrainRide))
    Exec(N(EVS_Conductor_AnnounceArrival))
    Call(GetEntryID, LVar0)
    IfEq(LVar0, omo_16_ENTRY_0)
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_LeftToRight)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Thread
            Label(10)
            Call(N(CheckForSceneSkip))
            IfEq(LVar0, 1)
                Goto(11)
            EndIf
            Wait(1)
            IfLt(MV_TrainPosX, 1400)
                Goto(10)
            EndIf
            Switch(GB_OMO_TrainRoute)
                CaseEq(TRAIN_ROUTE_BLUE_PINK)
                    Call(GotoMap, Ref("omo_06"), omo_06_ENTRY_2)
                CaseEq(TRAIN_ROUTE_PINK_GREEN)
                    Call(GotoMap, Ref("omo_08"), omo_08_ENTRY_1)
                CaseEq(TRAIN_ROUTE_GREEN_RED)
                    Call(GotoMap, Ref("omo_10"), omo_10_ENTRY_2)
                CaseEq(TRAIN_ROUTE_RED_BLUE)
                    Call(GotoMap, Ref("omo_03"), omo_03_ENTRY_2)
            EndSwitch
            Wait(100)
            Return
            Label(11)
            ExecWait(N(EVS_SkipTrainRideToNextStation))
        EndThread
    Else
        Set(MV_TrainRideState, TRAIN_STATE_INIT)
        Set(MV_TrainPath, Ref(N(TrainPath_RightToLeft)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_UpdateTrain))
        Set(MF_TrainRideActive, true)
        Thread
            Label(30)
            Call(N(CheckForSceneSkip))
            IfEq(LVar0, 1)
                Goto(31)
            EndIf
            Wait(1)
            IfGt(MV_TrainPosX, -1400)
                Goto(30)
            EndIf
            Switch(GB_OMO_TrainRoute)
                CaseEq(TRAIN_ROUTE_BLUE_PINK)
                    Call(GotoMap, Ref("omo_03"), omo_03_ENTRY_3)
                CaseEq(TRAIN_ROUTE_PINK_GREEN)
                    Call(GotoMap, Ref("omo_06"), omo_06_ENTRY_3)
                CaseEq(TRAIN_ROUTE_GREEN_RED)
                    Call(GotoMap, Ref("omo_08"), omo_08_ENTRY_2)
                CaseEq(TRAIN_ROUTE_RED_BLUE)
                    Call(GotoMap, Ref("omo_10"), omo_10_ENTRY_3)
            EndSwitch
            Wait(100)
            Return
            Label(31)
            ExecWait(N(EVS_SkipTrainRideToDestination))
        EndThread
    EndIf
    Return
    End
};
