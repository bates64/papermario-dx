#include "obk_04.h"
#include "world/area/obk/obk_03.h"

API_CALLABLE(AwaitPlayerEnterHole) {
    if (gPlayerStatus.pos.y < -50.0f) {
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_ManageHole = {
    Call(AwaitPlayerEnterHole)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, $obk_03.SuperBootsRoomHole)
    Wait(100)
    Return
    End
};
