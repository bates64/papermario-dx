#include "dgb_07.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Return
    End
};
