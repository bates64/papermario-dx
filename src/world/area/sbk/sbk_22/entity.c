#include "sbk_22.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $YellowBlock_Coin_3)
    Call(MakeMarkerEntity, $YellowBlock_Coin_4)
    Call(MakeMarkerEntity, $YellowBlock_FireFlower_1)
    Return
    End
};
