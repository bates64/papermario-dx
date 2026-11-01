#include "iwa_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $ArrowSign_1)
    Call(MakeMarkerEntity, $ArrowSign_2)
    Call(MakeMarkerEntity, $Item_QuakeHammer_1)
    Call(MakeMarkerEntity, $Item_LetterToMerlon_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
