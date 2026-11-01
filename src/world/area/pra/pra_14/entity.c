#include "pra_14.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $MulticoinBlock_2)
    Return
    End
};
