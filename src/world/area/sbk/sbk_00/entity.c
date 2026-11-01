#include "sbk_00.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_FrightJar_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Return
    End
};
