#include "kzn_10.h"
#include "world/area/kzn/kzn_09.h"
#include "world/area/kzn/kzn_11.h"

EvtScript EVS_ExitWalk_kzn_09_1 = EVT_EXIT_WALK(60, $Kzn09, $kzn_09.Kzn10);
EvtScript EVS_ExitWalk_kzn_11_0 = EVT_EXIT_WALK(60, $Kzn11, $kzn_11.Kzn10);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_09_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_11_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

API_CALLABLE(AwaitCameraFollowEnabled) {
    if (gPlayerStatus.flags & PS_FLAG_CAMERA_DOESNT_FOLLOW) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

EvtScript EVS_StartTexPanners = {
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Thread
        Call(GetEntryID, LVar0)
        IfEq(LVar0, $Kzn09.index)
            Call(UseSettingsFrom, CAM_DEFAULT, -445, -13, 0)
            Call(SetPanTarget, CAM_DEFAULT, -445, -13, 0)
        Else
            Call(UseSettingsFrom, CAM_DEFAULT, 425, -246, 0)
            Call(SetPanTarget, CAM_DEFAULT, 425, -246, 0)
        EndIf
        Call(SetCamSpeed, CAM_DEFAULT, 90.0)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Wait(2)
        Call(AwaitCameraFollowEnabled)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
    EndThread
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Exec(EVS_SetupSpinyTromp)
    Exec(EVS_StartTexPanners)
    Return
    End
};
