#include "jan_18.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_HappyHeartB_1)
    Return
    End
};
