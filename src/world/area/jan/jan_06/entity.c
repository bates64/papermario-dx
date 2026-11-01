#include "jan_06.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $PinkFlower_1)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Return
    End
};
