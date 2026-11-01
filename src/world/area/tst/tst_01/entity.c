#include "tst_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_FlowerPoint_1)
    Call(MakeMarkerEntity, $YellowBlock_None_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Heart_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Heart_2)
    Call(MakeMarkerEntity, $HiddenRedBlock_FlowerPoint_1)
    Call(MakeMarkerEntity, $RedBlock_FlowerPoint_1)
    Return
    End
};
