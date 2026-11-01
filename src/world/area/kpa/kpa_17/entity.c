#include "kpa_17.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Call(MakeMarkerEntity, $WoodenCrate_3)
    Return
    End
};
