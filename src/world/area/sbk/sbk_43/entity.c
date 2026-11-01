#include "sbk_43.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Return
    End
};
