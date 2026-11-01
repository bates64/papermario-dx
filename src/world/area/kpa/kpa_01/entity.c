#include "kpa_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_PowBlock_1)
    Return
    End
};
