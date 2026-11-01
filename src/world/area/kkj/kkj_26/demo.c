#include "kkj_26.h"
#include "sprite/player.h"

EvtScript EVS_ProvideDemoInputs = {
    Call(EnableWorldStatusBar, false)
    Call(UseSettingsFrom, CAM_DEFAULT, 550, 30, -20)
    Call(SetCamDistance, CAM_DEFAULT, 200.0)
    Call(SetCamPitch, CAM_DEFAULT, 17.5, -10.0)
    Call(SetCamPosB, CAM_DEFAULT, 570.0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Wait(60)
    Call(DemoJoystickXY, 10, 0)
    Wait(40)
    Call(DemoJoystickXY, 0, 0)
    Wait(10)
    Call(SetPlayerAnimation, ANIM_Peach2_RaiseArms)
    Wait(10)
    Call(SetPlayerAnimation, ANIM_Peach2_TalkIdle)
    Wait(20)
    Call(ResetCam, CAM_DEFAULT, 1.0)
    IfEq(GF_DemoSceneDone, true)
        Return
    EndIf
    Set(GF_DemoSceneDone, true)
    Call(GotoMapSpecial, $WhereIsMario, TRANSITION_SLOW_FADE_TO_WHITE)
    Wait(110)
    Return
    End
};

EvtScript EVS_MonitorDemoState = {
    Wait(10)
    Loop(0)
        Call(GetDemoState, LVar0)
        IfEq(LVar0, DEMO_STATE_CHANGE_MAP)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    IfEq(GF_DemoSceneDone, true)
        Return
    EndIf
    Set(GF_DemoSceneDone, true)
    Call(GotoMapSpecial, $WhereIsMario, TRANSITION_SLOW_FADE_TO_WHITE)
    Wait(100)
    Return
    End
};

EvtScript EVS_PlayDemoScene = {
    Call(RotateModel, MODEL_o85, 80, 0, -1, 0)
    Call(RotateModel, MODEL_o83, 80, 0, 1, 0)
    Call(RotateModel, MODEL_o86, 80, 0, -1, 0)
    Call(RotateModel, MODEL_o84, 80, 0, 1, 0)
    Set(GF_DemoSceneDone, false)
    Exec(EVS_MonitorDemoState)
    Exec(EVS_ProvideDemoInputs)
    Return
    End
};
