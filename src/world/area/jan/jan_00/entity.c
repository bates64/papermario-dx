#include "jan_00.h"
#include "entity.h"

EvtScript EVS_MakeFlowerCoins = {
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_StopWatch_1)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $ToadTown.index)
        Exec(EVS_MakeFlowerCoins)
    EndIf
    Call(MakeMarkerEntity, $SpinningFlower_1)
    Return
    End
};
