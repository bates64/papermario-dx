#include "dgb_10.h"
#include "entity.h"

EvtScript EVS_BreakFloor1 = {
    Set(GF_DGB10_BoardedFloor1, true)
    Return
    End
};

EvtScript EVS_BreakFloor2 = {
    Set(GF_DGB10_BoardedFloor2, true)
    Return
    End
};

EvtScript EVS_BreakFloor3 = {
    Set(GF_DGB10_BoardedFloor3, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_DGB10_BoardedFloor1, false)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    EndIf
    IfEq(GF_DGB10_BoardedFloor2, false)
        Call(MakeMarkerEntity, $BoardedFloor_2)
    EndIf
    IfEq(GF_DGB10_BoardedFloor3, false)
        Call(MakeMarkerEntity, $BoardedFloor_3)
    EndIf
    Return
    End
};
