#include "tik_03.h"
#include "world/partners.h"

API_CALLABLE(N(ChangePartnerFollowState)) {
    partner_disable_ai_soon();
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ProvideDemoInputs) = {
    Call(DemoJoystickXY, -85, -1)
    Wait(32)
    Call(DemoSetButtons, BUTTON_A)
    Wait(7)
    Call(DemoSetButtons, 0)
    Wait(20)
    Call(DemoSetButtons, BUTTON_A)
    Wait(30)
    Call(DemoSetButtons, 0)
    Wait(15)
    Call(N(ChangePartnerFollowState))
    Wait(15)
    IfEq(GF_DemoSceneDone, true)
        Return
    EndIf
    Set(GF_DemoSceneDone, true)
    Call(GotoMapSpecial, Ref("tik_03"), tik_03_ENTRY_2, TRANSITION_END_DEMO_SCENE_BLACK)
    Wait(110)
    Return
    End
};

EvtScript N(EVS_MonitorDemoState) = {
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
    Call(GotoMapSpecial, Ref("tik_03"), tik_03_ENTRY_2, TRANSITION_END_DEMO_SCENE_WHITE)
    Wait(100)
    Return
    End
};

s32 N(DemoInitState) = {
    0
};

API_CALLABLE(N(SetupDemoScene)) {
    PlayerStatus* player = &gPlayerStatus;

    switch (N(DemoInitState)) {
        case 0:
            N(DemoInitState) = 1;
            break;
        case 1:
        case 2:
            N(DemoInitState)++;
            break;
        case 3:
            partner_clear_player_tracking(gPartnerNpc);
            partner_set_goal_pos(player->pos.x, player->pos.z);
            partner_set_forced_follow_mode(0);
            gPartnerNpc->yaw = 270.0f;
            gPlayerStatus.targetYaw = 270.0f;
            gPlayerStatus.curYaw = 270.0f;
            gPlayerStatus.spriteFacingAngle = 180.0f;
            return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

EvtScript N(EVS_PlayDemoScene) = {
    Call(N(SetupDemoScene))
    Set(GF_DemoSceneDone, false)
    Exec(N(EVS_MonitorDemoState))
    Exec(N(EVS_ProvideDemoInputs))
    Return
    End
};
