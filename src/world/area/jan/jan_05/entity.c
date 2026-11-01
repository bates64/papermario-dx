#include "jan_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $RedBlock_PowerQuake_1)
    Call(MakeMarkerEntity, $CymbalPlant_1)
    Call(MakeMarkerEntity, $TrumpetPlant_1)
    Return
    End
};
