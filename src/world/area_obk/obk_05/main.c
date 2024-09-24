#include "obk_05.h"

#include "world/common/atomic/TexturePan.inc.c"

s32 N(adjust_cam_on_landing)(void) {
    return LANDING_CAM_NEVER_ADJUST;
}

API_CALLABLE(N(SetupLandingCamAdjust)) {
    phys_set_landing_adjust_cam_check(N(adjust_cam_on_landing));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_EnterDoor_obk_05_0) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(obk_05_ENTRY_0)
            Set(LVar2, MODEL_door1)
            Set(LVar4, MODEL_door1b)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSplitSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_ExitDoor_obk_01_2) = EVT_EXIT_SPLIT_SINGLE_DOOR(obk_05_ENTRY_0, "obk_01", obk_01_ENTRY_2,
    COLLIDER_tt1, MODEL_door1, MODEL_door1b, DOOR_SWING_OUT);

API_CALLABLE(N(RetroJar_AwaitPlayerEntry)) {
    if (gCollisionStatus.curFloor == COLLIDER_o420) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript N(EVS_ManageRetroJar) = {
    Loop(0)
        Call(N(RetroJar_AwaitPlayerEntry))
        Call(DisablePlayerInput, TRUE)
        Wait(1)
        IfEq(MF_IsRetroMario, FALSE)
            Call(PlaySoundAtPlayer, SOUND_JUMP_8BIT_MARIO, SOUND_SPACE_DEFAULT)
            Call(Disable8bitMario, FALSE)
            Call(SetMusicTrack, 0, SONG_CHAPTER_START, 1, 8)
            Set(MF_IsRetroMario, TRUE)
        Else
            Call(PlaySoundAtPlayer, SOUND_QUICK_PLAYER_JUMP, SOUND_SPACE_DEFAULT)
            Call(Disable8bitMario, TRUE)
            Exec(N(EVS_SetupMusic))
            Set(MF_IsRetroMario, FALSE)
        EndIf
        Call(DisableCameraFollowPlayerY)
        Call(SetPlayerJumpscale, Float(1.0))
        Call(PlayerJump, -105, 30, -55, 30)
        Wait(1)
        Call(EnableCameraFollowPlayerY)
        Call(DisablePlayerInput, FALSE)
    EndLoop
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    Call(N(SetupLandingCamAdjust))
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupRockingChairs))
    Exec(N(EVS_ManageHole))
    BindTrigger(Ref(N(EVS_ExitDoor_obk_01_2)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    Exec(N(EVS_EnterDoor_obk_05_0))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_hip1, COLLIDER_FLAGS_UPPER_MASK)
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_ManageRetroJar))
    Call(SetTexPanner, MODEL_m1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
