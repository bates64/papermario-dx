#include "trd_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Set(MV_PlatformsExtended, false)
    Call(MakeMarkerEntity, $RedSwitch_1)
    Call(MakeMarkerEntity, $RedSwitch_2)
    Call(MakeMarkerEntity, $Item_KoopaFortressKey_1)
    Call(MakeMarkerEntity, $Item_KoopaFortressKey_2)
    Call(MakeMarkerEntity, $Item_PowerBounce_1)
    Return
    End
};
