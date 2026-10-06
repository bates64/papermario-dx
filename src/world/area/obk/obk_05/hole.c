#include "obk_05.h"

API_CALLABLE(AwaitPlayerEnterHole) {
    if (gPlayerStatus.pos.y < -50.0f) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_ManageHole = {
    Call(AwaitPlayerEnterHole)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, Ref("obk_06"), obk_06_ENTRY_0)
    Wait(100)
    Return
    End
};
