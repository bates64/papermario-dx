#include "flo_23.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_ShootingStar_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_1)
    Call(MakeMarkerEntity, $SimpleSpring_1)
    Return
    End
};
