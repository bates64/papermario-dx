#include "jan_13.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $PinkFlower_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_VoltShroom_1)
    Call(UseDynamicShadow, true)
    Return
    End
};
