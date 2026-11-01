#include "jan_10.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Return
    End
};
