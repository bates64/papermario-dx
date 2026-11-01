#include "omo_08.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_FireFlower_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
