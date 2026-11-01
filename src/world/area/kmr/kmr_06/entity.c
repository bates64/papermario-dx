#include "kmr_06.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $RedBlock_CloseCall_1)
    Return
    End
};
