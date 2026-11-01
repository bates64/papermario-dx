#include "tik_21.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_2)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_3)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_4)
    Return
    End
};
