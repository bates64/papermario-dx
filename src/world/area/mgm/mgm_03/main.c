#include "mgm_03.h"

EvtScript N(EVS_Main) = {
    Call(SetSpriteShading, SHADING_ARN_09)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Return
    End
};
