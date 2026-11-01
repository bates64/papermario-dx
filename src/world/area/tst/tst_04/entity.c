#include "tst_04.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $RedSwitch_1)
    Return
    End
};
