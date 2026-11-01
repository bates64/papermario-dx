#include "isk_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
