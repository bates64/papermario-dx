#include "tst_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $InertYellowBlock_1)
    Call(MakeMarkerEntity, $InertYellowBlock_2)
    Call(MakeMarkerEntity, $InertYellowBlock_3)
    Call(MakeMarkerEntity, $InertYellowBlock_4)
    Call(MakeMarkerEntity, $InertYellowBlock_5)
    Call(MakeMarkerEntity, $GiantChest)
    Call(MakeMarkerEntity, $Chest)
    Return
    End
};
