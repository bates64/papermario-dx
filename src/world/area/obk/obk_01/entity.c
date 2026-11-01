#include "obk_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
