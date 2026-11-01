#include "sbk_52.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Return
    End
};
