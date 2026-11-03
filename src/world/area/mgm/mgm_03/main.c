#include "mgm_03.h"

EvtScript EVS_Main = {
    Call(SetSpriteShading, $SpriteShading)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Return
    End
};
