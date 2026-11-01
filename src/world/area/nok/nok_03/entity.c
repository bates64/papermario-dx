#include "nok_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_HpPlusB_1)
    Return
    End
};
