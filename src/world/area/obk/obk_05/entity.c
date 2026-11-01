#include "obk_05.h"
#include "entity.h"

EvtScript EVS_OnSmashFloor = {
    Set(GF_OBK05_BoardedFloor, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_OBK05_BoardedFloor, false)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    EndIf
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Call(MakeMarkerEntity, $WoodenCrate_3)
    Call(MakeMarkerEntity, $WoodenCrate_4)
    Return
    End
};
