#include "arn_08.h"
#include "sprite/player.h"

API_CALLABLE(AwaitPlayerFallDist) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 fallSpeed;
    s32 colliderID;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
        suggest_player_anim_allow_backward(ANIM_Mario1_Jump);
    }

    fallSpeed = player_fall_distance();
    playerStatus->pos.y = player_check_collision_below(fallSpeed, &colliderID);
    script->functionTemp[0] += fabsf(fallSpeed);

    if (script->functionTemp[0] > 50) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(AwaitPlayerJumpDown) {
    if (gPlayerStatus.pos.y < -10.0f) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_ExitWell = {
    Loop(0)
        IfNe(GB_StoryProgress, STORY_CH3_HEART_ESCAPED_WELL)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(AwaitPlayerJumpDown)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(AwaitPlayerFallDist)
    Set(AF_ARN_UsingWellSpring, true)
    IfLt(GB_StoryProgress, STORY_CH3_WENT_DOWN_THE_WELL)
        Set(GB_StoryProgress, STORY_CH3_WENT_DOWN_THE_WELL)
    EndIf
    Call(GotoMap, Ref("arn_09"), arn_09_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_SetupHole = {
    Call(SetCamProperties, CAM_DEFAULT, Float(90.0), 0, 0, 0, Float(470.0), Float(17.0), Float(-7.0))
    Exec(EVS_ExitWell)
    Return
    End
};
