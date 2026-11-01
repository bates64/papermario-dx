#include "jan_12.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $PinkFlower_1)
    Call(MakeMarkerEntity, $BellbellPlant_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_StoneCap_1)
    Return
    End
};
