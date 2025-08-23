#include "kzn_10.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_09_1) = EVT_EXIT_WALK(60, kzn_10_ENTRY_0, "kzn_09", kzn_09_ENTRY_1);
EvtScript N(EVS_ExitWalk_kzn_11_0) = EVT_EXIT_WALK(60, kzn_10_ENTRY_1, "kzn_11", kzn_11_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(N(EVS_ExitWalk_kzn_09_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(N(EVS_ExitWalk_kzn_11_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

API_CALLABLE(N(func_8024030C_C7E48C)) {
    if (gPlayerStatus.flags & PS_FLAG_CAMERA_DOESNT_FOLLOW) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

EvtScript N(EVS_StartTexPanners) = {
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_10)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Thread
        Call(GetEntryID, LVar0)
        IfEq(LVar0, kzn_10_ENTRY_0)
            Call(UseSettingsFrom, CAM_DEFAULT, -445, -13, 0)
            Call(SetPanTarget, CAM_DEFAULT, -445, -13, 0)
        Else
            Call(UseSettingsFrom, CAM_DEFAULT, 425, -246, 0)
            Call(SetPanTarget, CAM_DEFAULT, 425, -246, 0)
        EndIf
        Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Wait(2)
        Call(N(func_8024030C_C7E48C))
        Call(PanToTarget, CAM_DEFAULT, 0, false)
    EndThread
    Set(LVar0, N(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Exec(N(EVS_SetupSpinyTromp))
    Exec(N(EVS_StartTexPanners))
    Return
    End
};
