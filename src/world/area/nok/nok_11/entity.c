#include "nok_11.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $RedBlock_DizzyAttack_1)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Call(MakeMarkerEntity, $YellowBlock_FrightJar_1)
    Return
    End
};
