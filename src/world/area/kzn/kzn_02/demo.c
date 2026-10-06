#include "kzn_02.h"
#include "world/partners.h"

EvtScript EVS_ProvideDemoInputs = {
    Call(DemoJoystickXY, 87, 0)
    Wait(17)
    Call(DemoSetButtons, BUTTON_A)
    Wait(5)
    Call(DemoSetButtons, 0)
    Wait(20)
    Call(DemoSetButtons, BUTTON_A)
    Wait(7)
    Call(DemoSetButtons, 0)
    Wait(26)
    Call(DemoSetButtons, BUTTON_A)
    Wait(6)
    Call(DemoSetButtons, 0)
    Wait(20)
    Call(DemoSetButtons, BUTTON_A)
    Wait(5)
    Call(DemoSetButtons, 0)
    Wait(20)
    IfEq(GF_DemoSceneDone, true)
        Return
    EndIf
    Set(GF_DemoSceneDone, true)
    Call(GotoMapSpecial, Ref("kzn_02"), kzn_02_ENTRY_2, TRANSITION_END_DEMO_SCENE_BLACK)
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
    Call(GotoMapSpecial, Ref("kzn_02"), kzn_02_ENTRY_2, TRANSITION_END_DEMO_SCENE_WHITE)
    Wait(10)
    Return
    End
};

s32 DemoInitState = 0;

API_CALLABLE(SetupDemoScene) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    switch (DemoInitState) {
        case 0:
            DemoInitState = 1;
            break;
        case 1:
        case 2:
            DemoInitState++;
            break;
        case 3:
            partner_clear_player_tracking(gPartnerNpc);
            partner_set_goal_pos(playerStatus->pos.x, playerStatus->pos.z);
            partner_set_forced_follow_mode(0);
            set_npc_yaw(gPartnerNpc, 90.0f);
            playerStatus->targetYaw = 90.0f;
            playerStatus->curYaw = 90.0f;
            playerStatus->spriteFacingAngle = 0.0f;
            return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_PlayDemoScene = {
    Call(SetupDemoScene)
    Set(GF_DemoSceneDone, false)
    Exec(EVS_MonitorDemoState)
    Exec(EVS_ProvideDemoInputs)
    Return
    End
};
