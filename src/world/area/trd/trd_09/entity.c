#include "trd_09.h"
#include "entity.h"

EvtScript EVS_BombRock = {
    Set(GF_TRD09_BombedRock, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TRD09_BombedRock, false)
        Call(MakeMarkerEntity, $BombableRockWide_1)
    EndIf
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $YellowBlock_MapleSyrup_1)
    Return
    End
};
