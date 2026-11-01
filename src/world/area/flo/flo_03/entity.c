#include "flo_03.h"
#include "entity.h"

EvtScript EVS_EmptyEntityHandler = {
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
