#include "flo_15.h"
#include "entity.h"

EvtScript EVS_OnBlast_Rock = {
    Set(GF_FLO15_BombedRock, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_FLO15_BombedRock, false)
        Call(MakeMarkerEntity, $BombableRock_1)
    EndIf
    Return
    End
};
