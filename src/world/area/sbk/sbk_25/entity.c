#include "sbk_25.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $MulticoinBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Call(MakeMarkerEntity, $BrickBlock_5)
    Return
    End
};
