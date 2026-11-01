#include "kmr_04.h"
#include "entity.h"

EvtScript EVS_OnSmashBlock = {
    Set(GF_KMR04_Hammer1Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_KMR04_Hammer1Block, false)
        Call(MakeMarkerEntity, $Hammer1Block_1)
    EndIf
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
