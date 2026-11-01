#include "arn_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_DizzyDial_1)
    Call(MakeMarkerEntity, $Item_LetterToFiceT_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $YellowBlock_RepelGel_1)
    Return
    End
};
