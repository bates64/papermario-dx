#include "obk_04.h"

API_CALLABLE(AwaitPlayerEnterHole) {
    if (gPlayerStatus.pos.y < -50.0f) {
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_ManageHole = {
    Call(AwaitPlayerEnterHole)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, Ref("obk_03"), obk_03_ENTRY_2)
    Wait(100)
    Return
    End
};
