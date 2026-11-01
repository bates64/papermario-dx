#include "jan_09.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SpinningFlower_1)
    Call(MakeMarkerEntity, $Munchlesia_1)
    Return
    End
};
