#include "dgb_05.h"

API_CALLABLE(AwaitFallInHole) {
    if (gPlayerStatus.pos.y >= -210.0f) {
        return ApiStatus_BLOCK;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(AwaitFallDownHole) {
    if (gPlayerStatus.pos.y > -270.0f) {
        return ApiStatus_BLOCK;
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_SetupHole = {
    Call(AwaitFallInHole)
    Call(GrabCamera, CAM_DEFAULT, LVar2, LVar3, LVar4, LVar5)
    Call(AwaitFallDownHole)
    Set(GF_DGB05_BoardedFloor, true)
    Call(GotoMap, Ref("dgb_06"), dgb_06_ENTRY_1)
    Wait(100)
    Return
    End
};
