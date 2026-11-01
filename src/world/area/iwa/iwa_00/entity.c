#include "iwa_00.h"
#include "entity.h"

EvtScript EVS_OnSmashBlock = {
    Set(GF_IWA01_Hammer1Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_IWA01_Hammer1Block, false)
        Call(MakeMarkerEntity, $Hammer1BlockWideZ_1)
    EndIf
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $YellowBlock_SleepySheep_1)
    Call(MakeMarkerEntity, $ArrowSign_1)
    Call(MakeMarkerEntity, $ArrowSign_2)
    Return
    End
};
