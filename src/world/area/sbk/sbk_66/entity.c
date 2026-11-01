#include "sbk_66.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $MulticoinBlock_2)
    Call(MakeMarkerEntity, $MulticoinBlock_3)
    Call(MakeMarkerEntity, $MulticoinBlock_4)
    Call(MakeMarkerEntity, $MulticoinBlock_5)
    Call(MakeMarkerEntity, $MulticoinBlock_6)
    Return
    End
};
