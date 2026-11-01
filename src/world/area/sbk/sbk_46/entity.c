
#include "sbk_46.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_LifeShroom_1)
    Return
    End
};
