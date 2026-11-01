#include "hos_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Return
    End
};
