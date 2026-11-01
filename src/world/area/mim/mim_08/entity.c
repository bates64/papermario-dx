#include "mim_08.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $RedBlock_HpPlusA_1)
    Return
    End
};
