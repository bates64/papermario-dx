#include "jan_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_LetterToIgor_1)
    Call(MakeMarkerEntity, $BellbellPlant_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_RepelGel_1)
    Call(MakeMarkerEntity, $BellbellPlant_2)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Mystery_1)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $SpinningFlower_1)
    Return
    End
};
