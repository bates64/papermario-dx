#include "jan_19.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $PinkFlower_1)
    Call(MakeMarkerEntity, $PinkFlower_2)
    Return
    End
};
