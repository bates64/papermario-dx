#include "hos_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(SetEntityCullMode, 3)
    Return
    End
};
