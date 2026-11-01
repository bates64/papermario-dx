#include "kmr_07.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SimpleSpring_1)
    Set(MV_EntityID_Spring, LVar0)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
