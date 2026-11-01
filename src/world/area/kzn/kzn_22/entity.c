#include "kzn_22.h"
#include "entity.h"

EvtScript EVS_OpenChest = {
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest)
    Return
    End
};
