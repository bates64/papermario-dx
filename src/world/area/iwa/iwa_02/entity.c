#include "iwa_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $ArrowSign_1)
    Call(MakeMarkerEntity, $ArrowSign_2)
    Call(MakeMarkerEntity, $ArrowSign_3)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Return
    End
};
