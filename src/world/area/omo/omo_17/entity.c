#include "omo_17.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $YellowBlock_Coin_3)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Return
    End
};
