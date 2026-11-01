#include "jan_15.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $PinkFlower_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
