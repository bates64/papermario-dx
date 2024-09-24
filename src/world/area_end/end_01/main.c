#include "end_01.h"

API_CALLABLE(N(WidenCameraFOV)) {
    gCameras[CAM_DEFAULT].vfov = 35.0f;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_Main) = {
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetCamViewport, CAM_DEFAULT, 15, 28, 290, 128)
    Call(N(WidenCameraFOV))
    Call(EnableWorldStatusBar, FALSE)
    Exec(N(EVS_ManageParade))
    Wait(1)
    Return
    End
};
