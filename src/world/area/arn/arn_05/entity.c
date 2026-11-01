#include "arn_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
