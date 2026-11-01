#include "kmr_09.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Return
    End
};
