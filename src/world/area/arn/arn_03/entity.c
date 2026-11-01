#include "arn_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
