
#include "sbk_45.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $Item_StopWatch_1)
    Call(MakeMarkerEntity, $Item_SpinAttack_1)
    Return
    End
};
