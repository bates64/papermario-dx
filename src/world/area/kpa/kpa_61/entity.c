#include "kpa_61.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_SuperShroom_1)
    Call(MakeMarkerEntity, $YellowBlock_MapleSyrup_1)
    Call(MakeMarkerEntity, $YellowBlock_SuperShroom_2)
    Call(MakeMarkerEntity, $Item_JamminJelly_1)
    Return
    End
};
