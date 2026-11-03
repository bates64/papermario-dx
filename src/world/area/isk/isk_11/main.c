#include "isk_11.h"
#include "world/area/isk/isk_08.h"
#include "world/area/isk/isk_12.h"
#include "world/area/isk/isk_19.h"

b32 CamAdjustReady = false;

s32 adjust_cam_on_landing(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (!CamAdjustReady) {
        if (!(gPlayerStatus.pos.y > -520.0f)) {
            CamAdjustReady = true;
        } else {
            return LANDING_CAM_ALWAYS_ADJUST;
        }
    }

    if (gPlayerStatus.pos.y > -520.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    }

    return ret;
}

API_CALLABLE(SetupLandingCamAdjust) {
    phys_set_landing_adjust_cam_check(adjust_cam_on_landing);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_isk_08_3 = EVT_EXIT_WALK(40, $DescendingStairs2, $isk_08.StonePuzzleRoom);
EvtScript EVS_ExitWalk_isk_12_0 = EVT_EXIT_WALK(40, $SandDrainage3Upper, $isk_12.StonePuzzleRoomUpper);
EvtScript EVS_ExitWalk_isk_12_1 = EVT_EXIT_WALK(40, $SandDrainage3Lower, $isk_12.StonePuzzleRoomLower);
EvtScript EVS_ExitWalk_isk_19_0 = EVT_EXIT_WALK(40, $BossAntechamber, $isk_19.StonePuzzleRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_isk_08_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_12_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_19_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, $SpriteShading)
    Call(SetupLandingCamAdjust)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 2.8)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupPuzzle)
    ExecWait(EVS_SetupLock)
    IfLt(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Exec(EVS_ManageSecretPassage)
        Call(EnableGroup, MODEL_15, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2222, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2223, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2224, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2225, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2226, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2226, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2227, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(EnableGroup, MODEL_g377, false)
        Call(EnableModel, MODEL_o2205, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2087, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2088, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2089, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2090, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2091, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2092, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2186, COLLIDER_FLAGS_UPPER_MASK)
        Call(TranslateModel, MODEL_o2155, 0, -30, 0)
        Call(TranslateModel, MODEL_o2156, 0, -30, 0)
        Call(TranslateModel, MODEL_o2198, 0, -55, 0)
        Call(TranslateModel, MODEL_o2199, 0, -55, 0)
        Call(TranslateModel, MODEL_o2200, 0, -80, 0)
        Call(TranslateModel, MODEL_o2201, 0, -80, 0)
        Call(TranslateModel, MODEL_o2202, 0, -105, 0)
        Call(TranslateModel, MODEL_o2203, 0, -105, 0)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
