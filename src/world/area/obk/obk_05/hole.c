#include "obk_05.h"
#include "world/area/obk/obk_06.h"

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
    Call(GotoMap, $obk_06.PotRoom)
    Wait(100)
    Return
    End
};
