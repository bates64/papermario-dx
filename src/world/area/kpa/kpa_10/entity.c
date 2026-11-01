#include "kpa_10.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $YellowBlock_LifeShroom_1)
    Return
    End
};
