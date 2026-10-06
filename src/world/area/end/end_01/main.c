#include "end_01.h"

API_CALLABLE(WidenCameraFOV) {
    gCameras[CAM_DEFAULT].vfov = 35.0f;
    return ApiStatus_DONE2;
}

EvtScript EVS_Main = {
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetCamViewport, CAM_DEFAULT, 15, 28, 290, 128)
    Call(WidenCameraFOV)
    Call(EnableWorldStatusBar, false)
    Exec(EVS_ManageParade)
    Wait(1)
    Return
    End
};
