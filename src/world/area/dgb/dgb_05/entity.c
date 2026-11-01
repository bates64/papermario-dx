#include "dgb_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_DGB05_BoardedFloor, false)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    EndIf
    Return
    End
};
