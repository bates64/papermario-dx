#include "omo_10.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenYellowBlock_SuperShroom_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
