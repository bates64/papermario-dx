#include "kzn_18.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
